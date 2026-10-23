// DataLogger.h
#ifndef DATALOGGER_H
#define DATALOGGER_H

#include <string>
#include <fstream>
#include <map>
#include <chrono>
#include "EngineMonitor.h"

class DataLogger {
private:
    std::ofstream csv_file;
    std::ofstream log_file;
    std::string csv_filename;
    std::string log_filename;

    // 避免重复记录相同的警告
    std::map<AlertType, std::chrono::steady_clock::time_point> last_alert_time;
    const int ALERT_COOLDOWN = 5; // 5秒冷却

public:
    DataLogger();
    ~DataLogger();

    void recordData(const EngineData& data);
    void logAlert(AlertType alert, const std::string& message);

private:
    void openFiles();
    void writeCSVHeader();
    std::string alertToString(AlertType alert);
};

#endif // DATALOGGER_H