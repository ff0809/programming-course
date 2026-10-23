#pragma once
#include "EngineData.h"
#include <fstream>
#include <mutex>

class DataLogger {
public:
    DataLogger();
    void log(const EngineData& data);

private:
    std::ofstream file;
    std::mutex mtx;
};
