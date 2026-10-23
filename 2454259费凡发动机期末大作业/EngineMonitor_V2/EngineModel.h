#pragma once

#include <random>
#include "FaultTypes.h"

enum class EngineState {
    STOPPED,
    STARTING,
    STABLE,
    STOPPING
};

class EngineModel {
public:
    EngineModel();

    void update(double deltaTimeMs);
    void start();
    void stop();
    void increaseThrust();
    void decreaseThrust();

    EngineState getState() const { return m_state; }

    double getRPM() const {
        if (m_n1SensorFault) return -1.0;
        return m_rpm;
    }

    double getN1Percent() const {
        if (m_n1SensorFault) return -1.0;
        return (m_rpm / 40000.0) * 100.0;
    }

    double getTemperature() const {
        if (m_egtSensorFault) return -1.0;
        return m_temperature;
    }

    double getFuelFlow() const { return m_fuelFlow; }

    bool hasN1SensorFault() const { return m_n1SensorFault; }
    bool hasEGTSensorFault() const { return m_egtSensorFault; }

    void setTestN1Percent(double percent);
    void setTestEGT(double egt);
    void setTestState(EngineState state);
    void enableSensorFault(bool n1Fault, bool egtFault);

    void resetTestMode();

private:
    void updateStarting(double deltaTimeSec);
    void updateStable(double deltaTimeSec);
    void updateStopping(double deltaTimeSec);

    EngineState m_state;
    double m_rpm;
    double m_temperature;
    double m_fuelFlow;
    double m_elapsedTime;

    double m_stableRPM;
    double m_stableTemp;
    double m_stableFuelFlow;

    std::mt19937 m_rng;
    std::uniform_real_distribution<double> m_noiseDist;
    std::uniform_real_distribution<double> m_thrustChangeDist;

    bool m_useTestValues;
    bool m_n1SensorFault;
    bool m_egtSensorFault;
    double m_testN1Percent;
    double m_testEGT;

    static constexpr double RATED_RPM = 40000.0;
    static constexpr double STABLE_THRESHOLD = 0.95;
    static constexpr double MAX_TEMP = 1200.0;
    static constexpr double MIN_TEMP = -5.0;
    static constexpr double AMBIENT_TEMP = 20.0;
    static constexpr double MAX_FUEL_FLOW = 50.0;
};