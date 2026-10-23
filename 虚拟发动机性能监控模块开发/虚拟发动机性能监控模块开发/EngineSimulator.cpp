// EngineSimulator.cpp
#include "EngineSimulator.h"
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <iostream>
#include <cmath>
#include <algorithm>

EngineSimulator::EngineSimulator()
    : running(false),
    current_state(OFF),
    thrust_adjustment(0),
    simulate_N1S1_fail(false),
    simulate_N1S2_fail(false),
    simulate_N1S_fail(false),
    simulate_EGTS1_fail(false),
    simulate_EGTS2_fail(false),
    simulate_EGTS_fail(false),
    simulate_fuel_s_fail(false) {

    rng.seed(std::random_device{}());
    random_dist = std::uniform_real_distribution<double>(-0.03, 0.03);
    initializeData();
}

EngineSimulator::~EngineSimulator() {
    stop();
    if (simulation_thread.joinable()) {
        simulation_thread.join();
    }
}

void EngineSimulator::initializeData() {
    std::lock_guard<std::mutex> lock(data_mutex);

    current_data.fuel_remaining.value = config.fuel_max;
    current_data.fuel_remaining.status = NORMAL;
    current_data.fuel_flow.value = 0;
    current_data.fuel_flow.status = NORMAL;

    current_data.N1_sensor1.value = 0;
    current_data.N1_sensor2.value = 0;
    current_data.EGT_sensor1.value = config.room_temp;
    current_data.EGT_sensor2.value = config.room_temp;

    current_data.N1_percent = 0;
    current_data.EGT = config.room_temp;
    current_data.time_elapsed = 0;
    current_data.active_alerts.clear();
}

void EngineSimulator::start() {
    if (current_state == OFF) {
        current_state = STARTING;
        start_time = std::chrono::steady_clock::now();
        phase_start_time = start_time;

        if (!running) {
            running = true;
            simulation_thread = std::thread(&EngineSimulator::simulationLoop, this);
        }
    }
}

void EngineSimulator::stop() {
    if (current_state != OFF && current_state != STOPPING) {
        current_state = STOPPING;
        phase_start_time = std::chrono::steady_clock::now();
    }
}

void EngineSimulator::increaseThrust() {
    thrust_adjustment++;
}

void EngineSimulator::decreaseThrust() {
    thrust_adjustment--;
}

void EngineSimulator::simulateSensorFailure(AlertType sensor, bool fail) {
    std::lock_guard<std::mutex> lock(data_mutex);

    switch (sensor) {
    case N1S1_FAIL:
        simulate_N1S1_fail = fail;
        break;
    case N1S2_FAIL:
        simulate_N1S2_fail = fail;
        break;
    case N1_S_FAIL:
        simulate_N1S_fail = fail;
        break;
    case EGTS1_FAIL:
        simulate_EGTS1_fail = fail;
        break;
    case EGTS2_FAIL:
        simulate_EGTS2_fail = fail;
        break;
    case EGTS_FAIL:
        simulate_EGTS_fail = fail;
        break;
    case FUEL_S_FAIL:
        simulate_fuel_s_fail = fail;
        break;
    default:
        break;
    }
}

EngineData EngineSimulator::getCurrentData() {
    std::lock_guard<std::mutex> lock(data_mutex);
    return current_data;
}

EngineState EngineSimulator::getCurrentState() {
    return current_state;
}

std::vector<AlertType> EngineSimulator::getActiveAlerts() {
    std::lock_guard<std::mutex> lock(data_mutex);
    return current_data.active_alerts;
}

void EngineSimulator::simulationLoop() {
    const int update_interval_ms = 5;

    while (running) {
        auto current_time = std::chrono::steady_clock::now();
        double elapsed = std::chrono::duration<double>(current_time - start_time).count();
        double phase_elapsed = std::chrono::duration<double>(current_time - phase_start_time).count();

        {
            std::lock_guard<std::mutex> lock(data_mutex);
            updateData(elapsed, phase_elapsed);
            checkAlerts();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(update_interval_ms));
    }
}

void EngineSimulator::updateData(double total_elapsed, double phase_elapsed) {
    current_data.time_elapsed = total_elapsed;

    switch (current_state) {
    case STARTING:
        updateStartingPhase(phase_elapsed);
        break;
    case RUNNING:
        updateRunningPhase(phase_elapsed);
        break;
    case STOPPING:
        updateStoppingPhase(phase_elapsed);
        break;
    default:
        break;
    }

    // 更新燃油余量（基于流速）
    double dt = 0.005; // 5ms
    current_data.fuel_remaining.value -= current_data.fuel_flow.value * dt;
    if (current_data.fuel_remaining.value < 0) {
        current_data.fuel_remaining.value = 0;
    }

    // 添加随机波动
    addRandomFluctuation();
}

void EngineSimulator::updateStartingPhase(double t) {
    if (t <= 2.0) {
        // 第一阶段：线性增长
        double N1_rpm = 10400 * t; // 每秒10400转
        current_data.N1_percent = (N1_rpm / config.N1_max) * 100;
        current_data.fuel_flow.value = 5 * t;
        current_data.EGT = config.room_temp + 10 * t; // 轻微线性增长
    }
    else {
        // 第二阶段：对数增长
        double log_t = log10(t - 1);
        double N1_rpm = 23000 * log_t + 20000;
        current_data.N1_percent = (N1_rpm / config.N1_max) * 100;
        current_data.fuel_flow.value = 42 * log_t + 10;
        current_data.EGT = 900 * log_t + config.room_temp;

        // 检查是否达到稳态
        if (current_data.N1_percent >= 95) {
            current_state = RUNNING;
            phase_start_time = std::chrono::steady_clock::now();

            // 记录稳态基准值
            steady_N1 = current_data.N1_percent;
            steady_EGT = current_data.EGT;
            steady_fuel_flow = current_data.fuel_flow.value;
        }
    }

    // 边界检查
    current_data.N1_percent = std::min(std::max(current_data.N1_percent, 0.0), config.N1_percent_max);
    current_data.EGT = std::min(std::max(current_data.EGT, config.EGT_min), config.EGT_max);
    current_data.fuel_flow.value = std::min(std::max(current_data.fuel_flow.value, 0.0), config.fuel_flow_max);

    updateSensorValues();
}

void EngineSimulator::updateRunningPhase(double t) {
    // 基础稳态值
    double base_fuel_flow = steady_fuel_flow + thrust_adjustment;

    // ±3%波动
    double fluctuation = random_dist(rng);
    current_data.fuel_flow.value = base_fuel_flow * (1 + fluctuation);

    // 根据推力调整N1和EGT
    if (thrust_adjustment != 0) {
        double adjustment_factor = 1 + (random_dist(rng) * 0.02 + 0.03) * thrust_adjustment;
        current_data.N1_percent = steady_N1 * adjustment_factor;
        current_data.EGT = steady_EGT * adjustment_factor;
    }
    else {
        current_data.N1_percent = steady_N1;
        current_data.EGT = steady_EGT;
    }

    // 边界检查
    current_data.fuel_flow.value = std::min(std::max(current_data.fuel_flow.value, 0.0), config.fuel_flow_max);
    current_data.N1_percent = std::min(std::max(current_data.N1_percent, 0.0), config.N1_percent_max);
    current_data.EGT = std::min(std::max(current_data.EGT, config.EGT_min), config.EGT_max);

    updateSensorValues();
}

void EngineSimulator::updateStoppingPhase(double t) {
    // 燃油流速归零
    current_data.fuel_flow.value = 0;

    // 对数下降 (10秒内停止)
    if (t <= 10.0) {
        double decay_factor = pow(0.5, t / 2.0); // 更平缓的衰减
        current_data.N1_percent = steady_N1 * decay_factor;
        current_data.EGT = steady_EGT * decay_factor;
    }
    else {
        current_state = OFF;
        current_data.N1_percent = 0;
        current_data.EGT = config.room_temp;
        thrust_adjustment = 0;
    }

    // 边界检查
    current_data.N1_percent = std::max(current_data.N1_percent, 0.0);
    current_data.EGT = std::max(current_data.EGT, config.room_temp);

    updateSensorValues();
}

void EngineSimulator::updateSensorValues() {
    // 模拟传感器故障
    if (simulate_N1S1_fail) {
        current_data.N1_sensor1.value = 0;
        current_data.N1_sensor1.status = INVALID;
        current_data.N1_sensor1.is_faulty = true;
    }
    else {
        current_data.N1_sensor1.value = (current_data.N1_percent / 100) * config.N1_max;
        current_data.N1_sensor1.status = NORMAL;
        current_data.N1_sensor1.is_faulty = false;
    }

    if (simulate_N1S2_fail) {
        current_data.N1_sensor2.value = 0;
        current_data.N1_sensor2.status = INVALID;
        current_data.N1_sensor2.is_faulty = true;
    }
    else {
        current_data.N1_sensor2.value = (current_data.N1_percent / 100) * config.N1_max;
        current_data.N1_sensor2.status = NORMAL;
        current_data.N1_sensor2.is_faulty = false;
    }

    if (simulate_EGTS1_fail) {
        current_data.EGT_sensor1.value = 0;
        current_data.EGT_sensor1.status = INVALID;
        current_data.EGT_sensor1.is_faulty = true;
    }
    else {
        current_data.EGT_sensor1.value = current_data.EGT;
        current_data.EGT_sensor1.status = NORMAL;
        current_data.EGT_sensor1.is_faulty = false;
    }

    if (simulate_EGTS2_fail) {
        current_data.EGT_sensor2.value = 0;
        current_data.EGT_sensor2.status = INVALID;
        current_data.EGT_sensor2.is_faulty = true;
    }
    else {
        current_data.EGT_sensor2.value = current_data.EGT;
        current_data.EGT_sensor2.status = NORMAL;
        current_data.EGT_sensor2.is_faulty = false;
    }

    if (simulate_fuel_s_fail) {
        current_data.fuel_remaining.status = INVALID;
        current_data.fuel_remaining.is_faulty = true;
    }
    else {
        current_data.fuel_remaining.status = NORMAL;
        current_data.fuel_remaining.is_faulty = false;
    }
}

void EngineSimulator::addRandomFluctuation() {
    // 为真实感添加微小随机波动
    std::normal_distribution<double> noise_dist(0.0, 0.001); // ±0.1%

    double noise = noise_dist(rng);

    if (current_state == RUNNING) {
        current_data.N1_percent *= (1 + noise);
        current_data.EGT *= (1 + noise);
        current_data.fuel_flow.value *= (1 + noise);
    }
}

void EngineSimulator::checkAlerts() {
    std::vector<AlertType> alerts;

    checkSensorAlerts(alerts);
    checkFuelAlerts(alerts);
    checkSpeedAlerts(alerts);
    checkTemperatureAlerts(alerts);

    current_data.active_alerts = alerts;
}

void EngineSimulator::checkSensorAlerts(std::vector<AlertType>& alerts) {
    // 检查单个传感器故障
    if (simulate_N1S1_fail && !simulate_N1S2_fail && !simulate_N1S_fail) {
        alerts.push_back(N1S1_FAIL);
    }

    if (simulate_N1S2_fail && !simulate_N1S1_fail && !simulate_N1S_fail) {
        alerts.push_back(N1S2_FAIL);
    }

    // 检查单发转速传感器故障
    if (simulate_N1S_fail) {
        alerts.push_back(N1_S_FAIL);
    }

    // 检查单个EGT传感器故障
    if (simulate_EGTS1_fail && !simulate_EGTS2_fail && !simulate_EGTS_fail) {
        alerts.push_back(EGTS1_FAIL);
    }

    if (simulate_EGTS2_fail && !simulate_EGTS1_fail && !simulate_EGTS_fail) {
        alerts.push_back(EGTS2_FAIL);
    }

    // 检查单发EGT传感器故障
    if (simulate_EGTS_fail) {
        alerts.push_back(EGTS_FAIL);
    }

    // 检查双发传感器故障
    if ((simulate_N1S1_fail && simulate_N1S2_fail) ||
        (simulate_EGTS1_fail && simulate_EGTS2_fail)) {
        // 触发发动机停车
        if (current_state != STOPPING && current_state != OFF) {
            current_state = STOPPING;
            phase_start_time = std::chrono::steady_clock::now();
        }
    }

    // 检查燃油传感器故障
    if (simulate_fuel_s_fail) {
        alerts.push_back(FUEL_S_FAIL);
    }
}

void EngineSimulator::checkFuelAlerts(std::vector<AlertType>& alerts) {
    // 燃油余量低警告
    if (current_data.fuel_remaining.value < 1000 &&
        current_state != OFF && current_state != STOPPING &&
        !simulate_fuel_s_fail) {
        alerts.push_back(LOW_FUEL);
    }

    // 燃油流速超限
    if (current_data.fuel_flow.value > config.fuel_flow_max) {
        alerts.push_back(OVER_FUEL_FLOW);
    }
}

void EngineSimulator::checkSpeedAlerts(std::vector<AlertType>& alerts) {
    if (current_data.N1_percent > 105) {
        alerts.push_back(OVER_SPEED1);
    }

    if (current_data.N1_percent > 120) {
        alerts.push_back(OVER_SPEED2);
        // 触发停车
        if (current_state != STOPPING && current_state != OFF) {
            current_state = STOPPING;
            phase_start_time = std::chrono::steady_clock::now();
        }
    }
}

void EngineSimulator::checkTemperatureAlerts(std::vector<AlertType>& alerts) {
    bool is_starting = (current_state == STARTING);

    if (is_starting) {
        if (current_data.EGT > 850) {
            alerts.push_back(OVER_TEMP1);
        }

        if (current_data.EGT > 1000) {
            alerts.push_back(OVER_TEMP2);
            // 触发停车
            if (current_state != STOPPING && current_state != OFF) {
                current_state = STOPPING;
                phase_start_time = std::chrono::steady_clock::now();
            }
        }
    }
    else if (current_state == RUNNING) {
        if (current_data.EGT > 950) {
            alerts.push_back(OVER_TEMP3);
        }

        if (current_data.EGT > 1100) {
            alerts.push_back(OVER_TEMP4);
            // 触发停车
            if (current_state != STOPPING && current_state != OFF) {
                current_state = STOPPING;
                phase_start_time = std::chrono::steady_clock::now();
            }
        }
    }
}