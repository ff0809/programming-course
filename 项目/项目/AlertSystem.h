#pragma once
#include "EngineData.h"
#include <map>
#include <functional>
#include <chrono>

struct AlertRule {
    std::string id;
    std::function<bool(const EngineData&)> check;
};

class AlertSystem {
public:
    AlertSystem();
    void update(EngineData& data);

private:
    std::map<std::string, AlertRule> rules;
    std::map<std::string, std::chrono::steady_clock::time_point> active;
};
