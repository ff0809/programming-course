#pragma once

#include <fstream>
#include <string>
#include <vector>
#include "FaultTypes.h"

class EngineModel;
class FuelSystem;

class DataLogger {
public:
    DataLogger();
    ~DataLogger();

    void startLogging();
    void stopLogging();

    void log(long long timestampMs, const EngineModel& leftEngine,
        const EngineModel& rightEngine, const FuelSystem& fuelSystem);

    void logAlert(long long timestampMs, const AlertMessage& alert);

    bool isLogging() const { return m_isLogging; }

private:
    std::ofstream m_file;
    bool m_isLogging;
    std::string m_filename;
};