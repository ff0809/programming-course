#pragma once

#include <fstream>
#include <string>

class EngineModel;
class FuelSystem;

/**
 * @brief 数据记录器类
 * 
 * 负责将传感器数据写入 CSV 文件
 */
class DataLogger {
public:
    DataLogger();
    ~DataLogger();

    /**
     * @brief 开始记录 (创建新文件)
     */
    void startLogging();

    /**
     * @brief 停止记录
     */
    void stopLogging();

    /**
     * @brief 记录一行数据
     * @param timestampMs 时间戳 (毫秒)
     * @param leftEngine 左发动机
     * @param rightEngine 右发动机
     * @param fuelSystem 燃油系统
     */
    void log(long long timestampMs, const EngineModel& leftEngine, 
             const EngineModel& rightEngine, const FuelSystem& fuelSystem);

    bool isLogging() const { return m_isLogging; }

private:
    std::ofstream m_file;
    bool m_isLogging;
    std::string m_filename;
};
