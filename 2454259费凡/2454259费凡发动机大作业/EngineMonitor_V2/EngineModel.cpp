#include "EngineModel.h"
#include <algorithm>

EngineModel::EngineModel()
    : m_state(EngineState::STOPPED)
    , m_rpm(0.0)
    , m_temperature(AMBIENT_TEMP)
    , m_fuelFlow(0.0)
    , m_elapsedTime(0.0)
    , m_rng(std::random_device{}())
    , m_noiseDist(-0.03, 0.03) 
    , m_thrustChangeDist(0.03, 0.05) 
    , m_stableRPM(RATED_RPM* STABLE_THRESHOLD)
    , m_stableTemp(900.0)
    , m_stableFuelFlow(42.0)
    , m_testN1Percent(0.0)      
    , m_testEGT(0.0)            
    , m_useTestValues(false)    
    , m_n1SensorFault(false)    
    , m_egtSensorFault(false)   
{
}

void EngineModel::update(double deltaTimeMs) {
    double deltaTimeSec = deltaTimeMs / 1000.0;

    if (m_useTestValues) {
        if (m_n1SensorFault) {
            m_rpm = -1.0;
        }
        else if (m_testN1Percent > 0) {
            m_rpm = (m_testN1Percent / 100.0) * RATED_RPM;
        }

        if (m_egtSensorFault) {
            m_temperature = -1.0;
        }
        else if (m_testEGT > 0) {
            m_temperature = m_testEGT;
        }

        m_rpm = std::clamp(m_rpm, -1.0, RATED_RPM * 1.25);
        m_temperature = std::clamp(m_temperature, -1.0, MAX_TEMP);
        return;
    }

    switch (m_state) {
    case EngineState::STOPPED:
        break;
    case EngineState::STARTING:
        updateStarting(deltaTimeSec);
        break;
    case EngineState::STABLE:
        updateStable(deltaTimeSec);
        break;
    case EngineState::STOPPING:
        updateStopping(deltaTimeSec);
        break;
    }

    m_rpm = std::clamp(m_rpm, 0.0, RATED_RPM * 1.25);
    m_temperature = std::clamp(m_temperature, MIN_TEMP, MAX_TEMP);
    m_fuelFlow = std::clamp(m_fuelFlow, 0.0, MAX_FUEL_FLOW);
}

void EngineModel::start() {
    if (m_state == EngineState::STOPPED) {
        m_state = EngineState::STARTING;
        m_elapsedTime = 0.0;
        m_rpm = 0.0;
        m_temperature = AMBIENT_TEMP;
        m_fuelFlow = 0.0;
    }
}

void EngineModel::stop() {
    if (m_state == EngineState::STARTING || m_state == EngineState::STABLE) {
        m_state = EngineState::STOPPING;
        m_elapsedTime = 0.0;
        m_fuelFlow = 0.0;
        m_stableRPM = m_rpm;
        m_stableTemp = m_temperature;
    }
}

void EngineModel::increaseThrust() {
    if (m_state == EngineState::STABLE) {
        double changeFactor = 1.0 + m_thrustChangeDist(m_rng);

        m_stableRPM *= changeFactor;
        m_stableTemp *= changeFactor;
        m_stableFuelFlow += 1.0;

        m_stableFuelFlow = std::min(m_stableFuelFlow, MAX_FUEL_FLOW);
        m_stableRPM = std::min(m_stableRPM, RATED_RPM * 1.25);
        m_stableTemp = std::min(m_stableTemp, MAX_TEMP);

        double rpmNoise = 1.0 + m_noiseDist(m_rng);
        double tempNoise = 1.0 + m_noiseDist(m_rng);
        double flowNoise = 1.0 + m_noiseDist(m_rng);

        m_rpm = m_stableRPM * rpmNoise;
        m_temperature = m_stableTemp * tempNoise;
        m_fuelFlow = m_stableFuelFlow * flowNoise;
    }
}

void EngineModel::decreaseThrust() {
    if (m_state == EngineState::STABLE) {
        double changeFactor = 1.0 - m_thrustChangeDist(m_rng);

        m_stableRPM *= changeFactor;
        m_stableTemp *= changeFactor;
        m_stableFuelFlow -= 1.0;

        m_stableFuelFlow = std::max(m_stableFuelFlow, 0.0);
        m_stableRPM = std::max(m_stableRPM, 0.0);
        m_stableTemp = std::max(m_stableTemp, MIN_TEMP);

        double rpmNoise = 1.0 + m_noiseDist(m_rng);
        double tempNoise = 1.0 + m_noiseDist(m_rng);
        double flowNoise = 1.0 + m_noiseDist(m_rng);

        m_rpm = m_stableRPM * rpmNoise;
        m_temperature = m_stableTemp * tempNoise;
        m_fuelFlow = m_stableFuelFlow * flowNoise;
    }
}

void EngineModel::updateStarting(double deltaTimeSec) {
    m_elapsedTime += deltaTimeSec;

    if (m_elapsedTime <= 2.0) {
        m_rpm = 10400.0 * m_elapsedTime;
        m_fuelFlow = 5.0 * m_elapsedTime;
        m_temperature = AMBIENT_TEMP + 10.0 * m_elapsedTime;
    }
    else {
        double t = m_elapsedTime - 1.0;
        if (t > 0) {
            m_fuelFlow = 42.0 * std::log10(t) + 10.0;
            m_rpm = 23000.0 * std::log10(t) + 20000.0;
            m_temperature = 900.0 * std::log10(t) + AMBIENT_TEMP + 300.0;
        }
    }

    if (m_rpm >= RATED_RPM * STABLE_THRESHOLD) {
        m_state = EngineState::STABLE;
        m_stableRPM = m_rpm;
        m_stableTemp = m_temperature;
        m_stableFuelFlow = m_fuelFlow;
        m_elapsedTime = 0.0;
    }
}

void EngineModel::updateStable(double deltaTimeSec) {
    m_elapsedTime += deltaTimeSec;

    double rpmNoise = 1.0 + m_noiseDist(m_rng);
    double tempNoise = 1.0 + m_noiseDist(m_rng);
    double flowNoise = 1.0 + m_noiseDist(m_rng);

    m_rpm = m_stableRPM * rpmNoise;
    m_temperature = m_stableTemp * tempNoise;
    m_fuelFlow = m_stableFuelFlow * flowNoise;
}

void EngineModel::updateStopping(double deltaTimeSec) {
    m_elapsedTime += deltaTimeSec;

    double decayFactor = std::exp(-0.46 * m_elapsedTime);

    m_rpm = m_stableRPM * decayFactor;
    m_temperature = AMBIENT_TEMP + (m_stableTemp - AMBIENT_TEMP) * decayFactor;
    m_fuelFlow = 0.0;

    if (m_rpm < 100.0) {
        m_state = EngineState::STOPPED;
        m_rpm = 0.0;
        m_temperature = AMBIENT_TEMP;
        m_elapsedTime = 0.0;
    }
}

void EngineModel::resetTestMode() {
    m_useTestValues = false;
    m_n1SensorFault = false;
    m_egtSensorFault = false;
    m_testN1Percent = 0.0;
    m_testEGT = 0.0;

    m_state = EngineState::STOPPED;
    m_rpm = 0.0;
    m_temperature = AMBIENT_TEMP;
    m_fuelFlow = 0.0;
    m_elapsedTime = 0.0;
}

void EngineModel::setTestN1Percent(double percent) {
    m_testN1Percent = percent;
    m_useTestValues = true;
}

void EngineModel::setTestEGT(double egt) {
    m_testEGT = egt;
    m_useTestValues = true;
}

void EngineModel::setTestState(EngineState state) {
    m_state = state;
    m_useTestValues = true;
}

void EngineModel::enableSensorFault(bool n1Fault, bool egtFault) {
    m_n1SensorFault = n1Fault;
    m_egtSensorFault = egtFault;
    m_useTestValues = true;
}