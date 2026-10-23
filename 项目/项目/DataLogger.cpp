#include "DataLogger.h"
#include <chrono>

using namespace std::chrono;

DataLogger::DataLogger() {
    file.open("engine_data.csv");
    file << "Time,N1,EGT,Fuel,State,Alerts\n";
}

void DataLogger::log(const EngineData& d) {
    std::lock_guard<std::mutex> lock(mtx);
    file << duration_cast<milliseconds>(
        steady_clock::now().time_since_epoch()).count()
        << "," << d.n1_avg
        << "," << d.egt_avg
        << "," << d.fuelLevel
        << "," << (int)d.state
        << "," << d.alerts.size() << "\n";
}
