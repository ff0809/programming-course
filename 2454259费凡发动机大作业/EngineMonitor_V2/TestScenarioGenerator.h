#pragma once

#include "EngineModel.h"
#include "FuelSystem.h"
#include "FaultTypes.h"
#include <functional>
#include <vector>
#include <string>

class TestScenarioGenerator {
public:
    struct TestCase {
        FaultType faultType;
        std::string description;
        std::function<void(EngineModel&, EngineModel&, FuelSystem&)> setupFunc;
    };

    TestScenarioGenerator();

    const std::vector<TestCase>& getTestCases() const { return m_testCases; }

    void executeTest(int testIndex, EngineModel& leftEngine, EngineModel& rightEngine, FuelSystem& fuelSystem);

    std::string getTestCaseDescription(int testIndex) const;

    int getTestCaseCount() const { return static_cast<int>(m_testCases.size()); }

    void resetToNormal(EngineModel& leftEngine, EngineModel& rightEngine, FuelSystem& fuelSystem);

private:
    void initializeTestCases();

    void setupSingleN1SensorFault(EngineModel& leftEngine, EngineModel& rightEngine, FuelSystem& fuelSystem);
    void setupEngineN1SensorFault(EngineModel& leftEngine, EngineModel& rightEngine, FuelSystem& fuelSystem);
    void setupSingleEGTSensorFault(EngineModel& leftEngine, EngineModel& rightEngine, FuelSystem& fuelSystem);
    void setupEngineEGTSensorFault(EngineModel& leftEngine, EngineModel& rightEngine, FuelSystem& fuelSystem);
    void setupDualSensorFault(EngineModel& leftEngine, EngineModel& rightEngine, FuelSystem& fuelSystem);
    void setupFuelLow(EngineModel& leftEngine, EngineModel& rightEngine, FuelSystem& fuelSystem);
    void setupFuelSensorFault(EngineModel& leftEngine, EngineModel& rightEngine, FuelSystem& fuelSystem);
    void setupFuelFlowHigh(EngineModel& leftEngine, EngineModel& rightEngine, FuelSystem& fuelSystem);
    void setupN1Over105(EngineModel& leftEngine, EngineModel& rightEngine, FuelSystem& fuelSystem);
    void setupN1Over120(EngineModel& leftEngine, EngineModel& rightEngine, FuelSystem& fuelSystem);
    void setupEGTStartOver850(EngineModel& leftEngine, EngineModel& rightEngine, FuelSystem& fuelSystem);
    void setupEGTStartOver1000(EngineModel& leftEngine, EngineModel& rightEngine, FuelSystem& fuelSystem);
    void setupEGTStableOver950(EngineModel& leftEngine, EngineModel& rightEngine, FuelSystem& fuelSystem);
    void setupEGTStableOver1100(EngineModel& leftEngine, EngineModel& rightEngine, FuelSystem& fuelSystem);

private:
    std::vector<TestCase> m_testCases;
};