#pragma once
#include "EngineData.h"
#include <chrono>

class EngineSimulator {
public:
    EngineSimulator();
    void start();
    void shutdown();
    void update();              // 5ms
    EngineData getData() const;

private:
    void updateState();
    void genN1();
    void genEGT();
    void genFuel();

    EngineData data;
    EngineState state;
    std::chrono::steady_clock::time_point stateTime;
};
