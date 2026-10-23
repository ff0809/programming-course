// DataLogger.cpp
#define _CRT_SECURE_NO_WARNINGS
#include "Datalogger.h"
#include <iostream>
#include <iomanip>
#include <sstream>

DataLogger::DataLogger() {
    // 生成唯一文件名
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    // 使用 localtime_s 替代 localtime，避免 C4996 警告
    std::tm tm_buf;
    localtime_s(&tm_buf, &now_c);
    ss << "engine_data_" << std::put_time(&tm_buf, "%Y%m%d_%H%M%S");

    csv_filename = ss.str() + ".csv";
    log_filename = ss.str() + ".log";

    openFiles();
    writeCSVHeader();
}

DataLogger::~DataLogger() {
    if (csv_file.is_open()) csv_file.close();
    if (log_file.is_open()) log_file.close();
}

void DataLogger::recordData(const EngineData& data) {
    if (!csv_file.is_open()) return;

    csv_file << std::fixed << std::setprecision(3);
    csv_file << data.time_elapsed << ","
        << data.N1_percent << ","
        << data.EGT << ","
        << data.fuel_remaining.value << ","
        << data.fuel_flow.value << ","
        << data.N1_sensor1.value << ","
        << data.N1_sensor2.value << ","
        << data.EGT_sensor1.value << ","
        << data.EGT_sensor2.value << "\n";

    csv_file.flush();
}

void DataLogger::logAlert(AlertType alert, const std::string& message) {
    auto now = std::chrono::steady_clock::now();

    // 检查冷却时间
    auto it = last_alert_time.find(alert);
    if (it != last_alert_time.end()) {
        auto elapsed = std::chrono::duration<double>(now - it->second).count();
        if (elapsed < ALERT_COOLDOWN) {
            return;
        }
    }

    last_alert_time[alert] = now;

    if (log_file.is_open()) {
        auto now_c = std::chrono::system_clock::to_time_t(
            std::chrono::system_clock::now());

        log_file << std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S")
            << " - ALERT: " << alertToString(alert)
            << " - " << message << "\n";
        log_file.flush();
    }
}

void DataLogger::openFiles() {
    csv_file.open(csv_filename);
    log_file.open(log_filename);

    if (!csv_file.is_open()) {
        std::cerr << "Error: Could not open CSV file!" << std::endl;
    }

    if (!log_file.is_open()) {
        std::cerr << "Error: Could not open log file!" << std::endl;
    }
}

void DataLogger::writeCSVHeader() {
    if (csv_file.is_open()) {
        csv_file << "Time(s),N1(%),EGT(C),FuelRemaining,FuelFlow,"
            << "N1_Sensor1,N1_Sensor2,EGT_Sensor1,EGT_Sensor2\n";
    }
}

std::string DataLogger::alertToString(AlertType alert) {
    switch (alert) {
    case N1S1_FAIL: return "N1S1_FAIL";
    case N1S2_FAIL: return "N1S2_FAIL";
    case N1_S_FAIL: return "N1_S_FAIL";
    case EGT_S_FAIL: return "EGT_S_FAIL"; // 若未使用也保留通用项
    case EGTS1_FAIL: return "EGTS1_FAIL";
    case EGTS2_FAIL: return "EGTS2_FAIL";
    case EGTS_FAIL: return "EGTS_FAIL";
    case LOW_FUEL: return "LOW_FUEL";
    case FUEL_S_FAIL: return "FUEL_S_FAIL";
    case OVER_FUEL_FLOW: return "OVER_FUEL_FLOW";
    case OVER_SPEED1: return "OVER_SPEED1";
    case OVER_SPEED2: return "OVER_SPEED2";
    case OVER_TEMP1: return "OVER_TEMP1";
    case OVER_TEMP2: return "OVER_TEMP2";
    case OVER_TEMP3: return "OVER_TEMP3";
    case OVER_TEMP4: return "OVER_TEMP4";
    default: return "UNKNOWN_ALERT";
    }
}