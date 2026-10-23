// EngineSimulator.h
#ifndef ENGINESIMULATOR_H
#define ENGINESIMULATOR_H

#include "EngineMonitor.h"
#include <atomic>
#include <thread>
#include <mutex>
#include <random>

class EngineSimulator {
private:
    std::atomic<bool> running;
    std::thread simulation_thread;
    std::mutex data_mutex;

    EngineState current_state;
    EngineData current_data;
    Config config;

    // 时间相关
    std::chrono::steady_clock::time_point start_time;
    std::chrono::steady_clock::time_point phase_start_time;

    // 随机数生成
    std::mt19937 rng;
    std::uniform_real_distribution<double> random_dist;

    // 稳态基准值
    double steady_N1;
    double steady_EGT;
    double steady_fuel_flow;

    // 推力控制
    int thrust_adjustment;

    // 传感器故障模拟
    bool simulate_N1S1_fail;
    bool simulate_N1S2_fail;
    bool simulate_N1S_fail;
    bool simulate_EGTS1_fail;
    bool simulate_EGTS2_fail;
    bool simulate_EGTS_fail;
    bool simulate_fuel_s_fail;

public:
    EngineSimulator();
    ~EngineSimulator();

    void initializeData();
    void start();
    void stop();
    void increaseThrust();
    void decreaseThrust();

    // 传感器故障模拟方法
    void simulateSensorFailure(AlertType sensor, bool fail);

    EngineData getCurrentData();
    EngineState getCurrentState();

    // 获取当前警报
    std::vector<AlertType> getActiveAlerts();

private:
    void simulationLoop();
    void updateData(double total_elapsed, double phase_elapsed);
    void updateStartingPhase(double t);
    void updateRunningPhase(double t);
    void updateStoppingPhase(double t);
    void updateSensorValues();
    void addRandomFluctuation();
    void checkAlerts();
    void checkSensorAlerts(std::vector<AlertType>& alerts);
    void checkFuelAlerts(std::vector<AlertType>& alerts);
    void checkSpeedAlerts(std::vector<AlertType>& alerts);
    void checkTemperatureAlerts(std::vector<AlertType>& alerts);
};

#endif // ENGINESIMULATOR_H