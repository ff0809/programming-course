#include "AlertSystem.h"

using namespace std::chrono;

AlertSystem::AlertSystem() {
    rules["N1_HIGH"] = { "N1_HIGH", [](auto& d) { return d.n1_avg > 105; } };
    rules["N1_OVERSPEED"] = { "N1_OVERSPEED", [](auto& d) { return d.n1_avg > 120; } };
    rules["EGT_HIGH"] = { "EGT_HIGH", [](auto& d) { return d.egt_avg > 900; } };
    rules["FUEL_LOW"] = { "FUEL_LOW", [](auto& d) { return d.fuelLevel < 500; } };
    // 其余告警同样方式扩展到 14 个
}

void AlertSystem::update(EngineData& data) {
    auto now = steady_clock::now();
    data.alerts.clear();

    for (auto& [id, rule] : rules) {
        if (rule.check(data)) {
            if (!active.count(id) ||
                duration_cast<seconds>(now - active[id]).count() >= 5) {
                active[id] = now;
            }
            data.alerts.push_back(id);
        }
    }
}
