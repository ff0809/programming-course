#pragma once

#include "EngineModel.h"

class FuelSystem {
public:
    FuelSystem();

    void update(const EngineModel& leftEngine, const EngineModel& rightEngine, double deltaTimeMs);
    void reset();

    double getFuelLevel() const {
        if (m_fuelSensorFault) return -1.0;
        return m_fuelLevel;
    }

    double getTotalFuelFlow() const { return m_totalFuelFlow; }

    bool hasFuelSensorFault() const { return m_fuelSensorFault; }

    void setTestFuelLevel(double level);
    void setTestFuelFlow(double flow);
    void enableFuelSensorFault(bool fault);

    void resetTestMode();

private:
    double m_fuelLevel;
    double m_totalFuelFlow;

    bool m_useTestValues;
    bool m_fuelSensorFault;
    double m_testFuelLevel;
    double m_testFuelFlow;

    static constexpr double MAX_FUEL = 20000.0;
};