// EngineMonitor.h
#ifndef ENGINEMONITOR_H
#define ENGINEMONITOR_H

#include <vector>
#include <string>
#include <chrono>
#include <atomic>
#include <memory>

// 枚举定义
enum EngineState {
    OFF,
    STARTING,
    RUNNING,
    STOPPING
};

enum SensorStatus {
    NORMAL,
    WARNING,
    ALARM,
    INVALID
};

// 定义AlertType枚举，包含ALERT_NONE及其它警报类型
enum AlertType {
    ALERT_NONE = 0,
    ALERT_N1_LOW,
    ALERT_EGT_HIGH,
    ALERT_FUEL_LOW,
    // 传感器异常
    N1S1_FAIL,
    N1S2_FAIL,
    N1_S_FAIL,
    EGT_S_FAIL,
    EGTS1_FAIL,
    EGTS2_FAIL,
    EGTS_FAIL,

    // 燃油异常
    LOW_FUEL,
    FUEL_S_FAIL,
    OVER_FUEL_FLOW,

    // 转速异常
    OVER_SPEED1,
    OVER_SPEED2,

    // 温度异常
    OVER_TEMP1,
    OVER_TEMP2,
    OVER_TEMP3,
    OVER_TEMP4
};

// 传感器数据结构
struct SensorData {
    double value;
    SensorStatus status;
    bool is_faulty;

    SensorData() : value(0.0), status(NORMAL), is_faulty(false) {}
};

// 发动机数据
struct EngineData {
    SensorData N1_sensor1;    // 转速传感器1
    SensorData N1_sensor2;    // 转速传感器2
    SensorData EGT_sensor1;   // 温度传感器1
    SensorData EGT_sensor2;   // 温度传感器2
    SensorData fuel_remaining; // 燃油余量
    SensorData fuel_flow;      // 燃油流速

    double N1_percent;         // N1百分比
    double EGT;               // 排气温度
    double time_elapsed;      // 运行时间(秒)

    std::vector<AlertType> active_alerts; // 当前活跃警报

    EngineData() : N1_percent(0.0), EGT(0.0), time_elapsed(0.0) {}
};

// 配置参数
struct Config {
    double N1_max = 40000.0;    // 额定转速
    double N1_percent_max = 125.0; // 最大百分比
    double EGT_min = -5.0;      // 最低温度
    double EGT_max = 1200.0;    // 最高温度
    double fuel_max = 20000.0;  // 最大燃油量
    double fuel_flow_max = 50.0; // 最大燃油流速
    double room_temp = 20.0;    // 室温
};

#endif // ENGINEMONITOR_H
