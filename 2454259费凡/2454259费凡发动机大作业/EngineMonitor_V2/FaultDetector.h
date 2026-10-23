#pragma once

#include "FaultTypes.h"
#include "EngineModel.h"
#include "FuelSystem.h"
#include <vector>
#include <map>
#include <chrono>

class FaultDetector {
public:
    FaultDetector();

    void update(const EngineModel& leftEngine, const EngineModel& rightEngine,
        const FuelSystem& fuelSystem, long long timestampMs);

    const std::vector<AlertMessage>& getActiveAlerts() const { return m_activeAlerts; }

    const SensorFaultFlags& getSensorFaults() const { return m_sensorFaults; }

    std::vector<AlertMessage> getAlertsToLog();

    void clearLoggedFlags();

    FaultLevel getN1DisplayLevel(double n1Percent, bool sensorFault, bool isEngineFault) const;

    FaultLevel getEGTDisplayLevel(double egt, EngineState state, bool sensorFault, bool isEngineFault) const;

    FaultLevel getFuelDisplayLevel(double fuelLevel, bool sensorFault) const;

    FaultLevel getFuelFlowDisplayLevel(double flowRate) const;

private:
    void detectAllFaults(const EngineModel& leftEngine, const EngineModel& rightEngine,
        const FuelSystem& fuelSystem, long long timestampMs);

    void detectSensorFaults(const EngineModel& leftEngine, const EngineModel& rightEngine,
        const FuelSystem& fuelSystem, long long timestampMs);

    void detectFuelFaults(const FuelSystem& fuelSystem, long long timestampMs);

    void detectN1Faults(const EngineModel& leftEngine, const EngineModel& rightEngine,
        long long timestampMs);

    void detectEGTFaults(const EngineModel& leftEngine, const EngineModel& rightEngine,
        long long timestampMs);

    void addAlert(FaultType type, FaultLevel level, const std::string& text,
        long long timestampMs);

    bool hasAlert(FaultType type) const;

    void removeExpiredAlerts(long long timestampMs);

private:
    std::vector<AlertMessage> m_activeAlerts;
    SensorFaultFlags m_sensorFaults;
    std::map<FaultType, long long> m_lastAlertTime;

    static constexpr long long ALERT_DURATION_MS = 5000; 
    static constexpr long long LOG_COOLDOWN_MS = 5000;
};