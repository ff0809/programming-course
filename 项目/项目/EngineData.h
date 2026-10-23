#pragma once
#include <vector>
#include <string>

enum class EngineState {
    SHUTDOWN,
    STARTING_PHASE1,
    STARTING_PHASE2,
    RUNNING,
    SHUTTING_DOWN
};

enum class ValueStatus {
    NORMAL,
    CAUTION,
    WARNING,
    INVALID
};

struct EngineData {
    double n1_1 = 0, n1_2 = 0, n1_avg = 0;
    double egt_1 = 0, egt_2 = 0, egt_avg = 0;
    double fuelLevel = 5000;
    double fuelFlow = 0;

    EngineState state = EngineState::SHUTDOWN;
    std::vector<std::string> alerts;
};
