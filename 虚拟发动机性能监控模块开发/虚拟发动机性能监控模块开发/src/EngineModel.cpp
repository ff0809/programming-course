#include "EngineModel.h"
#include <algorithm>

EngineModel::EngineModel()
    : m_state(EngineState::STOPPED)
    , m_rpm(0.0)
    , m_temperature(AMBIENT_TEMP)
    , m_fuelFlow(0.0)
    , m_elapsedTime(0.0)
    , m_rng(std::random_device{}())
    , m_noiseDist(-0.03, 0.03)  // ±3% 波动
    , m_stableRPM(RATED_RPM * STABLE_THRESHOLD)
    , m_stableTemp(900.0)
    , m_stableFuelFlow(42.0)
{
}

void EngineModel::update(double deltaTimeMs) {
    double deltaTimeSec = deltaTimeMs / 1000.0;

    switch (m_state) {
        case EngineState::STOPPED:
            // 保持停止状态
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

    // 限制数值范围
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
        // 停车时燃油流速立即归零
        m_fuelFlow = 0.0;
        // 记录停车开始时的值用于衰减计算
        m_stableRPM = m_rpm;
        m_stableTemp = m_temperature;
    }
}

void EngineModel::updateStarting(double deltaTimeSec) {
    m_elapsedTime += deltaTimeSec;

    if (m_elapsedTime <= 2.0) {
        // 0 ~ 2秒：线性增长
        // 转速每秒增加 10400 转 (达到 20800 rpm at 2s)
        m_rpm = 10400.0 * m_elapsedTime;
        // 燃油流速每秒增加 5 单位
        m_fuelFlow = 5.0 * m_elapsedTime;
        // 温度保持环境温度附近
        m_temperature = AMBIENT_TEMP + 10.0 * m_elapsedTime;
    } else {
        // 2秒后：对数增长
        double t = m_elapsedTime - 1.0;  // t-1 in formula
        if (t > 0) {
            // V ≈ 42 * lg(t-1) + 10
            m_fuelFlow = 42.0 * std::log10(t) + 10.0;
            // N ≈ 23000 * lg(t-1) + 20000
            m_rpm = 23000.0 * std::log10(t) + 20000.0;
            // T ≈ 900 * lg(t-1) + T0
            m_temperature = 900.0 * std::log10(t) + AMBIENT_TEMP + 300.0;
        }
    }

    // 检查是否达到稳定状态阈值 (95% 额定转速)
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

    // 在基准值 ±3% 范围内随机波动
    double rpmNoise = 1.0 + m_noiseDist(m_rng);
    double tempNoise = 1.0 + m_noiseDist(m_rng);
    double flowNoise = 1.0 + m_noiseDist(m_rng);

    m_rpm = m_stableRPM * rpmNoise;
    m_temperature = m_stableTemp * tempNoise;
    m_fuelFlow = m_stableFuelFlow * flowNoise;
}

void EngineModel::updateStopping(double deltaTimeSec) {
    m_elapsedTime += deltaTimeSec;

    // 使用指数衰减模拟停车过程 (10秒内停止)
    // 使用指数函数: value = initial * exp(-k * t), k = ln(100)/10 使得10秒后衰减到1%
    double decayFactor = std::exp(-0.46 * m_elapsedTime);  // 约10秒衰减到1%
    
    m_rpm = m_stableRPM * decayFactor;
    m_temperature = AMBIENT_TEMP + (m_stableTemp - AMBIENT_TEMP) * decayFactor;
    m_fuelFlow = 0.0;  // 燃油流速保持为0

    // 当转速低于阈值时完全停止
    if (m_rpm < 100.0) {
        m_state = EngineState::STOPPED;
        m_rpm = 0.0;
        m_temperature = AMBIENT_TEMP;
        m_elapsedTime = 0.0;
    }
}
