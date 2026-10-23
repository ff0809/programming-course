#pragma once

#include "EngineModel.h"

/**
 * @brief 燃油系统类
 * 
 * 管理全局燃油量和计算总消耗
 */
class FuelSystem {
public:
    static constexpr double MAX_FUEL = 20000.0;  // 满油量

    FuelSystem();

    /**
     * @brief 更新燃油系统 (每5ms调用一次)
     * @param leftEngine 左发动机
     * @param rightEngine 右发动机
     * @param deltaTimeMs 时间步长 (毫秒)
     */
    void update(const EngineModel& leftEngine, const EngineModel& rightEngine, double deltaTimeMs);

    /**
     * @brief 重置燃油到满油状态
     */
    void reset();

    // Getters
    double getFuelLevel() const { return m_fuelLevel; }
    double getTotalFuelFlow() const { return m_totalFuelFlow; }

private:
    double m_fuelLevel;      // 当前燃油量
    double m_totalFuelFlow;  // 总燃油流速 (左+右)
};
