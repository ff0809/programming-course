#include "TestScenarioGenerator.h"
#include <iostream>
#include <random>
#include <cmath>

TestScenarioGenerator::TestScenarioGenerator() {
    initializeTestCases();
}

void TestScenarioGenerator::initializeTestCases() {
    m_testCases.clear();

    m_testCases.push_back({
        FaultType::SINGLE_N1_SENSOR_FAULT,
        "1. Single N1 Sensor Fault (Left N1 sensor invalid)",
        [this](EngineModel& left, EngineModel& right, FuelSystem& fuel) { setupSingleN1SensorFault(left, right, fuel); }
        });

    m_testCases.push_back({
        FaultType::ENGINE_N1_SENSOR_FAULT,
        "2. Engine N1 Sensor Fault (Left engine N1 invalid)",
        [this](EngineModel& left, EngineModel& right, FuelSystem& fuel) { setupEngineN1SensorFault(left, right, fuel); }
        });

    m_testCases.push_back({
        FaultType::SINGLE_EGT_SENSOR_FAULT,
        "3. Single EGT Sensor Fault (Left EGT sensor invalid)",
        [this](EngineModel& left, EngineModel& right, FuelSystem& fuel) { setupSingleEGTSensorFault(left, right, fuel); }
        });

    m_testCases.push_back({
        FaultType::ENGINE_EGT_SENSOR_FAULT,
        "4. Engine EGT Sensor Fault (Left engine EGT invalid)",
        [this](EngineModel& left, EngineModel& right, FuelSystem& fuel) { setupEngineEGTSensorFault(left, right, fuel); }
        });

    m_testCases.push_back({
        FaultType::DUAL_SENSOR_FAULT,
        "5. Dual Sensor Fault (Both engines N1 sensors invalid)",
        [this](EngineModel& left, EngineModel& right, FuelSystem& fuel) { setupDualSensorFault(left, right, fuel); }
        });

    m_testCases.push_back({
        FaultType::FUEL_LOW,
        "6. Fuel Low (Fuel level below 1000)",
        [this](EngineModel& left, EngineModel& right, FuelSystem& fuel) { setupFuelLow(left, right, fuel); }
        });

    m_testCases.push_back({
        FaultType::FUEL_SENSOR_FAULT,
        "7. Fuel Sensor Fault (Fuel sensor invalid)",
        [this](EngineModel& left, EngineModel& right, FuelSystem& fuel) { setupFuelSensorFault(left, right, fuel); }
        });

    m_testCases.push_back({
        FaultType::FUEL_FLOW_HIGH,
        "8. Fuel Flow High (Total flow > 50 units/s)",
        [this](EngineModel& left, EngineModel& right, FuelSystem& fuel) { setupFuelFlowHigh(left, right, fuel); }
        });

    m_testCases.push_back({
        FaultType::N1_OVER_105,
        "9. N1 Overspeed 1 (N1 > 105%)",
        [this](EngineModel& left, EngineModel& right, FuelSystem& fuel) { setupN1Over105(left, right, fuel); }
        });

    m_testCases.push_back({
        FaultType::N1_OVER_120,
        "10. N1 Overspeed 2 (N1 > 120%)",
        [this](EngineModel& left, EngineModel& right, FuelSystem& fuel) { setupN1Over120(left, right, fuel); }
        });

    m_testCases.push_back({
        FaultType::EGT_START_OVER_850,
        "11. EGT Overheat 1 (EGT > 850C during start)",
        [this](EngineModel& left, EngineModel& right, FuelSystem& fuel) { setupEGTStartOver850(left, right, fuel); }
        });

    m_testCases.push_back({
        FaultType::EGT_START_OVER_1000,
        "12. EGT Overheat 2 (EGT > 1000C during start)",
        [this](EngineModel& left, EngineModel& right, FuelSystem& fuel) { setupEGTStartOver1000(left, right, fuel); }
        });

    m_testCases.push_back({
        FaultType::EGT_STABLE_OVER_950,
        "13. EGT Overheat 3 (EGT > 950C at stable)",
        [this](EngineModel& left, EngineModel& right, FuelSystem& fuel) { setupEGTStableOver950(left, right, fuel); }
        });

    m_testCases.push_back({
        FaultType::EGT_STABLE_OVER_1100,
        "14. EGT Overheat 4 (EGT > 1100C at stable)",
        [this](EngineModel& left, EngineModel& right, FuelSystem& fuel) { setupEGTStableOver1100(left, right, fuel); }
        });
}

void TestScenarioGenerator::executeTest(int testIndex, EngineModel& leftEngine, EngineModel& rightEngine, FuelSystem& fuelSystem) {
    if (testIndex >= 0 && testIndex < static_cast<int>(m_testCases.size())) {
        std::cout << "Executing test: " << m_testCases[testIndex].description << std::endl;
        m_testCases[testIndex].setupFunc(leftEngine, rightEngine, fuelSystem);
    }
}

std::string TestScenarioGenerator::getTestCaseDescription(int testIndex) const {
    if (testIndex >= 0 && testIndex < static_cast<int>(m_testCases.size())) {
        return m_testCases[testIndex].description;
    }
    return "Invalid test index";
}

void TestScenarioGenerator::resetToNormal(EngineModel& leftEngine, EngineModel& rightEngine, FuelSystem& fuelSystem) {
    leftEngine.stop();
    rightEngine.stop();

    leftEngine.enableSensorFault(false, false);
    rightEngine.enableSensorFault(false, false);

    fuelSystem.reset();

    std::cout << "Reset to normal state" << std::endl;
}

void TestScenarioGenerator::setupSingleN1SensorFault(EngineModel& leftEngine, EngineModel& rightEngine, FuelSystem& fuelSystem) {
    std::cout << "Setting up single N1 sensor fault scenario" << std::endl;
    leftEngine.enableSensorFault(true, false);
    rightEngine.enableSensorFault(false, false);

    leftEngine.setTestState(EngineState::STABLE);
    leftEngine.setTestN1Percent(95.0);
    leftEngine.setTestEGT(950.0);

    rightEngine.setTestState(EngineState::STABLE);
    rightEngine.setTestN1Percent(95.0);
    rightEngine.setTestEGT(950.0);

    fuelSystem.reset();
}

void TestScenarioGenerator::setupEngineN1SensorFault(EngineModel& leftEngine, EngineModel& rightEngine, FuelSystem& fuelSystem) {
    std::cout << "Setting up engine N1 sensor fault scenario" << std::endl;
    leftEngine.enableSensorFault(true, false);
    rightEngine.enableSensorFault(false, false);

    leftEngine.setTestState(EngineState::STABLE);
    leftEngine.setTestN1Percent(85.0);
    leftEngine.setTestEGT(920.0);

    rightEngine.setTestState(EngineState::STABLE);
    rightEngine.setTestN1Percent(85.0);
    rightEngine.setTestEGT(920.0);

    fuelSystem.reset();
}

void TestScenarioGenerator::setupSingleEGTSensorFault(EngineModel& leftEngine, EngineModel& rightEngine, FuelSystem& fuelSystem) {
    std::cout << "Setting up single EGT sensor fault scenario" << std::endl;
    leftEngine.enableSensorFault(false, true);
    rightEngine.enableSensorFault(false, false);

    leftEngine.setTestState(EngineState::STABLE);
    leftEngine.setTestN1Percent(90.0);
    leftEngine.setTestEGT(1000.0);

    rightEngine.setTestState(EngineState::STABLE);
    rightEngine.setTestN1Percent(90.0);
    rightEngine.setTestEGT(1000.0);

    fuelSystem.reset();
}

void TestScenarioGenerator::setupEngineEGTSensorFault(EngineModel& leftEngine, EngineModel& rightEngine, FuelSystem& fuelSystem) {
    std::cout << "Setting up engine EGT sensor fault scenario" << std::endl;
    leftEngine.enableSensorFault(false, true);
    rightEngine.enableSensorFault(false, false);

    leftEngine.setTestState(EngineState::STABLE);
    leftEngine.setTestN1Percent(88.0);
    leftEngine.setTestEGT(980.0);

    rightEngine.setTestState(EngineState::STABLE);
    rightEngine.setTestN1Percent(88.0);
    rightEngine.setTestEGT(980.0);

    fuelSystem.reset();
}

void TestScenarioGenerator::setupDualSensorFault(EngineModel& leftEngine, EngineModel& rightEngine, FuelSystem& fuelSystem) {
    std::cout << "Setting up dual sensor fault scenario" << std::endl;
    leftEngine.enableSensorFault(true, false);
    rightEngine.enableSensorFault(true, false);

    leftEngine.setTestState(EngineState::STABLE);
    leftEngine.setTestN1Percent(92.0);
    leftEngine.setTestEGT(960.0);

    rightEngine.setTestState(EngineState::STABLE);
    rightEngine.setTestN1Percent(92.0);
    rightEngine.setTestEGT(960.0);

    fuelSystem.reset();
}

void TestScenarioGenerator::setupFuelLow(EngineModel& leftEngine, EngineModel& rightEngine, FuelSystem& fuelSystem) {
    std::cout << "Setting up fuel low scenario" << std::endl;
    leftEngine.setTestState(EngineState::STABLE);
    leftEngine.setTestN1Percent(85.0);
    leftEngine.setTestEGT(920.0);

    rightEngine.setTestState(EngineState::STABLE);
    rightEngine.setTestN1Percent(85.0);
    rightEngine.setTestEGT(920.0);

    fuelSystem.setTestFuelLevel(800.0);
    fuelSystem.setTestFuelFlow(45.0);
}

void TestScenarioGenerator::setupFuelSensorFault(EngineModel& leftEngine, EngineModel& rightEngine, FuelSystem& fuelSystem) {
    std::cout << "Setting up fuel sensor fault scenario" << std::endl;
    leftEngine.setTestState(EngineState::STABLE);
    leftEngine.setTestN1Percent(87.0);
    leftEngine.setTestEGT(940.0);

    rightEngine.setTestState(EngineState::STABLE);
    rightEngine.setTestN1Percent(87.0);
    rightEngine.setTestEGT(940.0);

    fuelSystem.enableFuelSensorFault(true);
    fuelSystem.setTestFuelLevel(10000.0);
    fuelSystem.setTestFuelFlow(40.0);
}

void TestScenarioGenerator::setupFuelFlowHigh(EngineModel& leftEngine, EngineModel& rightEngine, FuelSystem& fuelSystem) {
    std::cout << "Setting up fuel flow high scenario" << std::endl;
    leftEngine.setTestState(EngineState::STABLE);
    leftEngine.setTestN1Percent(110.0);
    leftEngine.setTestEGT(1050.0);

    rightEngine.setTestState(EngineState::STABLE);
    rightEngine.setTestN1Percent(110.0);
    rightEngine.setTestEGT(1050.0);

    fuelSystem.setTestFuelLevel(15000.0);
    fuelSystem.setTestFuelFlow(55.0); 
}

void TestScenarioGenerator::setupN1Over105(EngineModel& leftEngine, EngineModel& rightEngine, FuelSystem& fuelSystem) {
    std::cout << "Setting up N1 over 105% scenario" << std::endl;
    leftEngine.setTestState(EngineState::STABLE);
    leftEngine.setTestN1Percent(107.0);
    leftEngine.setTestEGT(980.0);

    rightEngine.setTestState(EngineState::STABLE);
    rightEngine.setTestN1Percent(107.0);
    rightEngine.setTestEGT(980.0);

    fuelSystem.setTestFuelLevel(12000.0);
    fuelSystem.setTestFuelFlow(48.0);
}

void TestScenarioGenerator::setupN1Over120(EngineModel& leftEngine, EngineModel& rightEngine, FuelSystem& fuelSystem) {
    std::cout << "Setting up N1 over 120% scenario" << std::endl;
    leftEngine.setTestState(EngineState::STABLE);
    leftEngine.setTestN1Percent(122.0);
    leftEngine.setTestEGT(1100.0);

    rightEngine.setTestState(EngineState::STABLE);
    rightEngine.setTestN1Percent(122.0);
    rightEngine.setTestEGT(1100.0);

    fuelSystem.setTestFuelLevel(10000.0);
    fuelSystem.setTestFuelFlow(58.0);
}

void TestScenarioGenerator::setupEGTStartOver850(EngineModel& leftEngine, EngineModel& rightEngine, FuelSystem& fuelSystem) {
    std::cout << "Setting up EGT start over 850C scenario" << std::endl;
    leftEngine.setTestState(EngineState::STARTING);
    leftEngine.setTestN1Percent(65.0);
    leftEngine.setTestEGT(870.0);

    rightEngine.setTestState(EngineState::STARTING);
    rightEngine.setTestN1Percent(65.0);
    rightEngine.setTestEGT(870.0);

    fuelSystem.setTestFuelLevel(18000.0);
    fuelSystem.setTestFuelFlow(25.0);
}

void TestScenarioGenerator::setupEGTStartOver1000(EngineModel& leftEngine, EngineModel& rightEngine, FuelSystem& fuelSystem) {
    std::cout << "Setting up EGT start over 1000C scenario" << std::endl;
    leftEngine.setTestState(EngineState::STARTING);
    leftEngine.setTestN1Percent(70.0);
    leftEngine.setTestEGT(1020.0);

    rightEngine.setTestState(EngineState::STARTING);
    rightEngine.setTestN1Percent(70.0);
    rightEngine.setTestEGT(1020.0);

    fuelSystem.setTestFuelLevel(17000.0);
    fuelSystem.setTestFuelFlow(28.0);
}

void TestScenarioGenerator::setupEGTStableOver950(EngineModel& leftEngine, EngineModel& rightEngine, FuelSystem& fuelSystem) {
    std::cout << "Setting up EGT stable over 950C scenario" << std::endl;
    leftEngine.setTestState(EngineState::STABLE);
    leftEngine.setTestN1Percent(98.0);
    leftEngine.setTestEGT(970.0);

    rightEngine.setTestState(EngineState::STABLE);
    rightEngine.setTestN1Percent(98.0);
    rightEngine.setTestEGT(970.0);

    fuelSystem.setTestFuelLevel(14000.0);
    fuelSystem.setTestFuelFlow(46.0);
}

void TestScenarioGenerator::setupEGTStableOver1100(EngineModel& leftEngine, EngineModel& rightEngine, FuelSystem& fuelSystem) {
    std::cout << "Setting up EGT stable over 1100C scenario" << std::endl;
    leftEngine.setTestState(EngineState::STABLE);
    leftEngine.setTestN1Percent(115.0);
    leftEngine.setTestEGT(1120.0);

    rightEngine.setTestState(EngineState::STABLE);
    rightEngine.setTestN1Percent(115.0);
    rightEngine.setTestEGT(1120.0);

    fuelSystem.setTestFuelLevel(11000.0);
    fuelSystem.setTestFuelFlow(52.0);
}