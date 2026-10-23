#include "FuelSystem.h"

FuelSystem::FuelSystem()
    : m_fuelLevel(MAX_FUEL)
    , m_totalFuelFlow(0.0)
    , m_useTestValues(false)
    , m_fuelSensorFault(false)
    , m_testFuelLevel(MAX_FUEL)
    , m_testFuelFlow(0.0)
{
}

void FuelSystem::update(const EngineModel& leftEngine, const EngineModel& rightEngine, double deltaTimeMs) {
    if (m_useTestValues) {
        if (m_fuelSensorFault) {
            m_fuelLevel = -1.0;
        }
        else {
            m_fuelLevel = m_testFuelLevel;
        }
        m_totalFuelFlow = m_testFuelFlow;
        return;
    }

    m_totalFuelFlow = leftEngine.getFuelFlow() + rightEngine.getFuelFlow();

    double consumption = m_totalFuelFlow * (deltaTimeMs / 1000.0);
    m_fuelLevel -= consumption;

    if (m_fuelLevel < 0.0) {
        m_fuelLevel = 0.0;
    }

    if (m_fuelLevel <= 0.0) {
        m_totalFuelFlow = 0.0;
    }
}

void FuelSystem::resetTestMode() {
    m_useTestValues = false;
    m_fuelSensorFault = false;
    m_testFuelLevel = MAX_FUEL;
    m_testFuelFlow = 0.0;
}

void FuelSystem::reset() {
    m_fuelLevel = MAX_FUEL;
    m_totalFuelFlow = 0.0;
    m_useTestValues = false;
    m_fuelSensorFault = false;
}

void FuelSystem::setTestFuelLevel(double level) {
    m_testFuelLevel = level;
    m_useTestValues = true;
}

void FuelSystem::setTestFuelFlow(double flow) {
    m_testFuelFlow = flow;
    m_useTestValues = true;
}

void FuelSystem::enableFuelSensorFault(bool fault) {
    m_fuelSensorFault = fault;
    m_useTestValues = true;
}