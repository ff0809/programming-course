#include "FaultDetector.h"
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <iostream>

FaultDetector::FaultDetector() {
    m_lastAlertTime.clear();
}

void FaultDetector::update(const EngineModel& leftEngine, const EngineModel& rightEngine,
    const FuelSystem& fuelSystem, long long timestampMs) {

    removeExpiredAlerts(timestampMs);

    m_sensorFaults.clear();

    detectAllFaults(leftEngine, rightEngine, fuelSystem, timestampMs);
}

void FaultDetector::detectAllFaults(const EngineModel& leftEngine, const EngineModel& rightEngine,
    const FuelSystem& fuelSystem, long long timestampMs) {

    detectSensorFaults(leftEngine, rightEngine, fuelSystem, timestampMs);

    if (!m_sensorFaults.leftN1Fault && !m_sensorFaults.rightN1Fault) {
        detectN1Faults(leftEngine, rightEngine, timestampMs);
    }

    if (!m_sensorFaults.leftEGTFault && !m_sensorFaults.rightEGTFault) {
        detectEGTFaults(leftEngine, rightEngine, timestampMs);
    }

    if (!m_sensorFaults.fuelSensorFault) {
        detectFuelFaults(fuelSystem, timestampMs);
    }
}

void FaultDetector::detectSensorFaults(const EngineModel& leftEngine, const EngineModel& rightEngine,
    const FuelSystem& fuelSystem, long long timestampMs) {

    if (leftEngine.hasN1SensorFault()) {
        m_sensorFaults.leftN1Fault = true;

        if (!m_sensorFaults.rightN1Fault) {
            if (!hasAlert(FaultType::SINGLE_N1_SENSOR_FAULT)) {
                addAlert(FaultType::SINGLE_N1_SENSOR_FAULT, FaultLevel::NORMAL,
                    "SINGLE N1 SENSOR FAULT - LEFT ENGINE", timestampMs);
            }

            if (!leftEngine.hasEGTSensorFault()) {
                if (!hasAlert(FaultType::ENGINE_N1_SENSOR_FAULT)) {
                    addAlert(FaultType::ENGINE_N1_SENSOR_FAULT, FaultLevel::CAUTION,
                        "ENGINE N1 SENSOR FAULT - LEFT ENGINE", timestampMs);
                }
            }
        }
    }

    if (rightEngine.hasN1SensorFault()) {
        m_sensorFaults.rightN1Fault = true;

        if (!m_sensorFaults.leftN1Fault) {
            if (!hasAlert(FaultType::SINGLE_N1_SENSOR_FAULT)) {
                addAlert(FaultType::SINGLE_N1_SENSOR_FAULT, FaultLevel::NORMAL,
                    "SINGLE N1 SENSOR FAULT - RIGHT ENGINE", timestampMs);
            }

            if (!rightEngine.hasEGTSensorFault()) {
                if (!hasAlert(FaultType::ENGINE_N1_SENSOR_FAULT)) {
                    addAlert(FaultType::ENGINE_N1_SENSOR_FAULT, FaultLevel::CAUTION,
                        "ENGINE N1 SENSOR FAULT - RIGHT ENGINE", timestampMs);
                }
            }
        }
    }

    if (leftEngine.hasEGTSensorFault()) {
        m_sensorFaults.leftEGTFault = true;

        if (!m_sensorFaults.rightEGTFault) {
            if (!hasAlert(FaultType::SINGLE_EGT_SENSOR_FAULT)) {
                addAlert(FaultType::SINGLE_EGT_SENSOR_FAULT, FaultLevel::NORMAL,
                    "SINGLE EGT SENSOR FAULT - LEFT ENGINE", timestampMs);
            }

            if (!leftEngine.hasN1SensorFault()) {
                if (!hasAlert(FaultType::ENGINE_EGT_SENSOR_FAULT)) {
                    addAlert(FaultType::ENGINE_EGT_SENSOR_FAULT, FaultLevel::CAUTION,
                        "ENGINE EGT SENSOR FAULT - LEFT ENGINE", timestampMs);
                }
            }
        }
    }

    if (rightEngine.hasEGTSensorFault()) {
        m_sensorFaults.rightEGTFault = true;

        if (!m_sensorFaults.leftEGTFault) {
            if (!hasAlert(FaultType::SINGLE_EGT_SENSOR_FAULT)) {
                addAlert(FaultType::SINGLE_EGT_SENSOR_FAULT, FaultLevel::NORMAL,
                    "SINGLE EGT SENSOR FAULT - RIGHT ENGINE", timestampMs);
            }

            if (!rightEngine.hasN1SensorFault()) {
                if (!hasAlert(FaultType::ENGINE_EGT_SENSOR_FAULT)) {
                    addAlert(FaultType::ENGINE_EGT_SENSOR_FAULT, FaultLevel::CAUTION,
                        "ENGINE EGT SENSOR FAULT - RIGHT ENGINE", timestampMs);
                }
            }
        }
    }

    if ((m_sensorFaults.leftN1Fault && m_sensorFaults.rightN1Fault) ||
        (m_sensorFaults.leftEGTFault && m_sensorFaults.rightEGTFault) ||
        (m_sensorFaults.leftN1Fault && m_sensorFaults.leftEGTFault) ||
        (m_sensorFaults.rightN1Fault && m_sensorFaults.rightEGTFault)) {

        if (!hasAlert(FaultType::DUAL_SENSOR_FAULT)) {
            addAlert(FaultType::DUAL_SENSOR_FAULT, FaultLevel::WARNING,
                "DUAL SENSOR FAULT - CHECK BOTH ENGINES", timestampMs);
        }
    }

    if (fuelSystem.hasFuelSensorFault()) {
        m_sensorFaults.fuelSensorFault = true;

        if (!hasAlert(FaultType::FUEL_SENSOR_FAULT)) {
            addAlert(FaultType::FUEL_SENSOR_FAULT, FaultLevel::WARNING,
                "FUEL SENSOR FAULT - FUEL LEVEL INVALID", timestampMs);
        }
    }
}

void FaultDetector::detectFuelFaults(const FuelSystem& fuelSystem, long long timestampMs) {
    double fuelLevel = fuelSystem.getFuelLevel();
    double totalFlow = fuelSystem.getTotalFuelFlow();

    if (fuelLevel > 0 && fuelLevel < 1000.0) {
        if (!hasAlert(FaultType::FUEL_LOW)) {
            std::ostringstream oss;
            oss << std::fixed << std::setprecision(0) << fuelLevel;
            addAlert(FaultType::FUEL_LOW, FaultLevel::CAUTION,
                "FUEL LOW - REMAINING: " + oss.str() + " UNITS", timestampMs);
        }
    }

    if (totalFlow > 50.0) {
        if (!hasAlert(FaultType::FUEL_FLOW_HIGH)) {
            std::ostringstream oss;
            oss << std::fixed << std::setprecision(1) << totalFlow;
            addAlert(FaultType::FUEL_FLOW_HIGH, FaultLevel::CAUTION,
                "FUEL FLOW HIGH - CURRENT: " + oss.str() + " UNITS/S", timestampMs);
        }
    }
}

void FaultDetector::detectN1Faults(const EngineModel& leftEngine, const EngineModel& rightEngine,
    long long timestampMs) {

    double leftN1 = leftEngine.getN1Percent();
    double rightN1 = rightEngine.getN1Percent();

    if (leftN1 > 120.0) {
        if (!hasAlert(FaultType::N1_OVER_120)) {
            std::ostringstream oss;
            oss << std::fixed << std::setprecision(1) << leftN1;
            addAlert(FaultType::N1_OVER_120, FaultLevel::WARNING,
                "LEFT ENGINE OVERSPEED - N1: " + oss.str() + "%", timestampMs);
        }
    }
    else if (leftN1 > 105.0) {
        if (!hasAlert(FaultType::N1_OVER_105)) {
            std::ostringstream oss;
            oss << std::fixed << std::setprecision(1) << leftN1;
            addAlert(FaultType::N1_OVER_105, FaultLevel::CAUTION,
                "LEFT ENGINE HIGH SPEED - N1: " + oss.str() + "%", timestampMs);
        }
    }

    if (rightN1 > 120.0) {
        if (!hasAlert(FaultType::N1_OVER_120)) {
            std::ostringstream oss;
            oss << std::fixed << std::setprecision(1) << rightN1;
            addAlert(FaultType::N1_OVER_120, FaultLevel::WARNING,
                "RIGHT ENGINE OVERSPEED - N1: " + oss.str() + "%", timestampMs);
        }
    }
    else if (rightN1 > 105.0) {
        if (!hasAlert(FaultType::N1_OVER_105)) {
            std::ostringstream oss;
            oss << std::fixed << std::setprecision(1) << rightN1;
            addAlert(FaultType::N1_OVER_105, FaultLevel::CAUTION,
                "RIGHT ENGINE HIGH SPEED - N1: " + oss.str() + "%", timestampMs);
        }
    }
}

void FaultDetector::detectEGTFaults(const EngineModel& leftEngine, const EngineModel& rightEngine,
    long long timestampMs) {

    double leftEGT = leftEngine.getTemperature();
    double rightEGT = rightEngine.getTemperature();
    EngineState leftState = leftEngine.getState();
    EngineState rightState = rightEngine.getState();

    if (leftState == EngineState::STARTING) {
        if (leftEGT > 1000.0) {
            if (!hasAlert(FaultType::EGT_START_OVER_1000)) {
                std::ostringstream oss;
                oss << std::fixed << std::setprecision(0) << leftEGT;
                addAlert(FaultType::EGT_START_OVER_1000, FaultLevel::WARNING,
                    "LEFT ENGINE OVERHEAT DURING START - EGT: " + oss.str() + "C", timestampMs);
            }
        }
        else if (leftEGT > 850.0) {
            if (!hasAlert(FaultType::EGT_START_OVER_850)) {
                std::ostringstream oss;
                oss << std::fixed << std::setprecision(0) << leftEGT;
                addAlert(FaultType::EGT_START_OVER_850, FaultLevel::CAUTION,
                    "LEFT ENGINE HIGH TEMP DURING START - EGT: " + oss.str() + "C", timestampMs);
            }
        }
    }
    else if (leftState == EngineState::STABLE) {
        if (leftEGT > 1100.0) {
            if (!hasAlert(FaultType::EGT_STABLE_OVER_1100)) {
                std::ostringstream oss;
                oss << std::fixed << std::setprecision(0) << leftEGT;
                addAlert(FaultType::EGT_STABLE_OVER_1100, FaultLevel::WARNING,
                    "LEFT ENGINE OVERHEAT - EGT: " + oss.str() + "C", timestampMs);
            }
        }
        else if (leftEGT > 950.0) {
            if (!hasAlert(FaultType::EGT_STABLE_OVER_950)) {
                std::ostringstream oss;
                oss << std::fixed << std::setprecision(0) << leftEGT;
                addAlert(FaultType::EGT_STABLE_OVER_950, FaultLevel::CAUTION,
                    "LEFT ENGINE HIGH TEMP - EGT: " + oss.str() + "C", timestampMs);
            }
        }
    }

    if (rightState == EngineState::STARTING) {
        if (rightEGT > 1000.0) {
            if (!hasAlert(FaultType::EGT_START_OVER_1000)) {
                std::ostringstream oss;
                oss << std::fixed << std::setprecision(0) << rightEGT;
                addAlert(FaultType::EGT_START_OVER_1000, FaultLevel::WARNING,
                    "RIGHT ENGINE OVERHEAT DURING START - EGT: " + oss.str() + "C", timestampMs);
            }
        }
        else if (rightEGT > 850.0) {
            if (!hasAlert(FaultType::EGT_START_OVER_850)) {
                std::ostringstream oss;
                oss << std::fixed << std::setprecision(0) << rightEGT;
                addAlert(FaultType::EGT_START_OVER_850, FaultLevel::CAUTION,
                    "RIGHT ENGINE HIGH TEMP DURING START - EGT: " + oss.str() + "C", timestampMs);
            }
        }
    }
    else if (rightState == EngineState::STABLE) {
        if (rightEGT > 1100.0) {
            if (!hasAlert(FaultType::EGT_STABLE_OVER_1100)) {
                std::ostringstream oss;
                oss << std::fixed << std::setprecision(0) << rightEGT;
                addAlert(FaultType::EGT_STABLE_OVER_1100, FaultLevel::WARNING,
                    "RIGHT ENGINE OVERHEAT - EGT: " + oss.str() + "C", timestampMs);
            }
        }
        else if (rightEGT > 950.0) {
            if (!hasAlert(FaultType::EGT_STABLE_OVER_950)) {
                std::ostringstream oss;
                oss << std::fixed << std::setprecision(0) << rightEGT;
                addAlert(FaultType::EGT_STABLE_OVER_950, FaultLevel::CAUTION,
                    "RIGHT ENGINE HIGH TEMP - EGT: " + oss.str() + "C", timestampMs);
            }
        }
    }
}

void FaultDetector::addAlert(FaultType type, FaultLevel level, const std::string& text,
    long long timestampMs) {
    auto it = m_lastAlertTime.find(type);
    if (it != m_lastAlertTime.end()) {
        if (timestampMs - it->second < LOG_COOLDOWN_MS) {
            return; 
        }
    }

    AlertMessage alert;
    alert.type = type;
    alert.level = level;
    alert.text = text;
    alert.startTime = std::chrono::steady_clock::now();
    alert.logged = false;

    m_activeAlerts.push_back(alert);
    m_lastAlertTime[type] = timestampMs;

    std::cout << "Alert added: " << text << std::endl;
}

bool FaultDetector::hasAlert(FaultType type) const {
    for (const auto& alert : m_activeAlerts) {
        if (alert.type == type) {
            return true;
        }
    }
    return false;
}

void FaultDetector::removeExpiredAlerts(long long timestampMs) {
    auto now = std::chrono::steady_clock::now();
    m_activeAlerts.erase(
        std::remove_if(m_activeAlerts.begin(), m_activeAlerts.end(),
            [now](const AlertMessage& alert) {
                auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                    now - alert.startTime);
                return elapsed.count() > ALERT_DURATION_MS;
            }),
        m_activeAlerts.end());
}

std::vector<AlertMessage> FaultDetector::getAlertsToLog() {
    std::vector<AlertMessage> toLog;
    for (auto& alert : m_activeAlerts) {
        if (!alert.logged) {
            toLog.push_back(alert);
            alert.logged = true;
        }
    }
    return toLog;
}

FaultLevel FaultDetector::getN1DisplayLevel(double n1Percent, bool sensorFault, bool isEngineFault) const {
    if (sensorFault) {
        if (isEngineFault) {
            return FaultLevel::CAUTION; 
        }
        return FaultLevel::NORMAL;
    }

    if (n1Percent < 0) {
        return FaultLevel::INVALID;
    }

    if (n1Percent > 120.0) {
        return FaultLevel::WARNING;
    }
    else if (n1Percent > 105.0) {
        return FaultLevel::CAUTION;
    }

    return FaultLevel::NORMAL;
}

FaultLevel FaultDetector::getEGTDisplayLevel(double egt, EngineState state, bool sensorFault, bool isEngineFault) const {
    if (sensorFault) {
        if (isEngineFault) {
            return FaultLevel::CAUTION;
        }
        return FaultLevel::NORMAL;
    }

    if (egt < 0) {
        return FaultLevel::INVALID;
    }

    if (state == EngineState::STARTING) {
        if (egt > 1000.0) {
            return FaultLevel::WARNING;
        }
        else if (egt > 850.0) {
            return FaultLevel::CAUTION;
        }
    }
    else if (state == EngineState::STABLE) {
        if (egt > 1100.0) {
            return FaultLevel::WARNING;
        }
        else if (egt > 950.0) {
            return FaultLevel::CAUTION;
        }
    }

    return FaultLevel::NORMAL;
}

FaultLevel FaultDetector::getFuelDisplayLevel(double fuelLevel, bool sensorFault) const {
    if (sensorFault) {
        return FaultLevel::WARNING;
    }

    if (fuelLevel < 0) {
        return FaultLevel::INVALID;
    }

    if (fuelLevel < 1000.0) {
        return FaultLevel::CAUTION;
    }

    return FaultLevel::NORMAL;
}

FaultLevel FaultDetector::getFuelFlowDisplayLevel(double flowRate) const {
    if (flowRate > 50.0) {
        return FaultLevel::CAUTION;
    }

    return FaultLevel::NORMAL;
}

void FaultDetector::clearLoggedFlags() {
    for (auto& alert : m_activeAlerts) {
        alert.logged = false;
    }
}