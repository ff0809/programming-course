#pragma once

#include <cmath>
#include <random>

/**
 * @brief 发动机运行状态枚举
 */
enum class EngineState {
    STOPPED,    // 停止
    STARTING,   // 启动中
    STABLE,     // 稳定运行
    STOPPING    // 停车中
};

/**
 * @brief 单台发动机模型类
 * 
 * 负责模拟发动机的物理行为，包括启动、稳定、停车三个阶段
 */
class EngineModel {
public:
    // 常量定义
    static constexpr double RATED_RPM = 40000.0;           // 额定转速 (rpm)
    static constexpr double STABLE_THRESHOLD = 0.95;       // 进入稳定状态的阈值 (95%)
    static constexpr double MAX_TEMP = 1200.0;             // 最高温度 (°C)
    static constexpr double MIN_TEMP = -5.0;               // 最低温度 (°C)
    static constexpr double AMBIENT_TEMP = 20.0;           // 环境温度 (°C)
    static constexpr double MAX_FUEL_FLOW = 50.0;          // 最大燃油流速

    EngineModel();

    /**
     * @brief 更新发动机状态 (每5ms调用一次)
     * @param deltaTimeMs 时间步长 (毫秒)
     */
    void update(double deltaTimeMs);

    /**
     * @brief 触发启动
     */
    void start();

    /**
     * @brief 触发停车
     */
    void stop();

    // Getters
    EngineState getState() const { return m_state; }
    double getRPM() const { return m_rpm; }
    double getN1Percent() const { return (m_rpm / RATED_RPM) * 100.0; }
    double getTemperature() const { return m_temperature; }
    double getFuelFlow() const { return m_fuelFlow; }
    double getElapsedTime() const { return m_elapsedTime; }

private:
    void updateStarting(double deltaTimeSec);
    void updateStable(double deltaTimeSec);
    void updateStopping(double deltaTimeSec);

    EngineState m_state;
    double m_rpm;           // 当前转速
    double m_temperature;   // 当前温度
    double m_fuelFlow;      // 当前燃油流速
    double m_elapsedTime;   // 当前阶段已过时间 (秒)

    // 随机数生成器 (用于稳定阶段的波动)
    std::mt19937 m_rng;
    std::uniform_real_distribution<double> m_noiseDist;

    // 稳态基准值
    double m_stableRPM;
    double m_stableTemp;
    double m_stableFuelFlow;
};
