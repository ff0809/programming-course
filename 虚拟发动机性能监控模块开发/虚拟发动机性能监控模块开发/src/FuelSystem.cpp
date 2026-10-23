#include "FuelSystem.h"

FuelSystem::FuelSystem()
    : m_fuelLevel(MAX_FUEL)
    , m_totalFuelFlow(0.0)
{
}

void FuelSystem::update(const EngineModel& leftEngine, const EngineModel& rightEngine, double deltaTimeMs) {
    // 计算总燃油流速
    m_totalFuelFlow = leftEngine.getFuelFlow() + rightEngine.getFuelFlow();

    // 消耗燃油 (流速单位: 单位/秒, deltaTime: 毫秒)
    double consumption = m_totalFuelFlow * (deltaTimeMs / 1000.0);
    m_fuelLevel -= consumption;

    // 确保燃油量不为负
    if (m_fuelLevel < 0.0) {
        m_fuelLevel = 0.0;
    }
}

void FuelSystem::reset() {
    m_fuelLevel = MAX_FUEL;
    m_totalFuelFlow = 0.0;
}
