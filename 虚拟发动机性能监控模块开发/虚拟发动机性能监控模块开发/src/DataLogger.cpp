#include "DataLogger.h"
#include "EngineModel.h"
#include "FuelSystem.h"
#include <chrono>
#include <iomanip>
#include <sstream>

DataLogger::DataLogger()
    : m_isLogging(false)
{
}

DataLogger::~DataLogger() {
    stopLogging();
}

void DataLogger::startLogging() {
    if (m_isLogging) {
        return;
    }

    // 生成文件名: log_YYYYMMDD_HHMMSS.csv
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::tm tm_buf;
#ifdef _WIN32
    localtime_s(&tm_buf, &time);
#else
    localtime_r(&time, &tm_buf);
#endif

    std::ostringstream oss;
    oss << "log_" 
        << std::put_time(&tm_buf, "%Y%m%d_%H%M%S")
        << ".csv";
    m_filename = oss.str();

    m_file.open(m_filename);
    if (m_file.is_open()) {
        // 写入表头
        m_file << "Timestamp_ms,Left_N,Left_N1_Pct,Left_T,Left_V,"
               << "Right_N,Right_N1_Pct,Right_T,Right_V,"
               << "Fuel_Level,Total_Fuel_Flow\n";
        m_isLogging = true;
    }
}

void DataLogger::stopLogging() {
    if (m_file.is_open()) {
        m_file.close();
    }
    m_isLogging = false;
}

void DataLogger::log(long long timestampMs, const EngineModel& leftEngine,
                     const EngineModel& rightEngine, const FuelSystem& fuelSystem) {
    if (!m_isLogging || !m_file.is_open()) {
        return;
    }

    m_file << timestampMs << ","
           << leftEngine.getRPM() << ","
           << leftEngine.getN1Percent() << ","
           << leftEngine.getTemperature() << ","
           << leftEngine.getFuelFlow() << ","
           << rightEngine.getRPM() << ","
           << rightEngine.getN1Percent() << ","
           << rightEngine.getTemperature() << ","
           << rightEngine.getFuelFlow() << ","
           << fuelSystem.getFuelLevel() << ","
           << fuelSystem.getTotalFuelFlow() << "\n";
}
