#include "AppController.h"
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <iostream>

AppController::AppController()
    : m_window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "Virtual Engine Performance Monitor - EICAS")
    , m_accumulatedTime(0.0)
    , m_totalElapsedMs(0)
    , m_currentTestScenario(0)
    , m_testModeActive(false)
    , m_lastScenarioChangeTime(0)
{
    m_window.setFramerateLimit(60);

    if (!m_font.openFromFile("resources/arial.ttf")) {
        if (!m_font.openFromFile("C:/Windows/Fonts/arial.ttf")) {
            throw std::runtime_error("Failed to load font!");
        }
    }

    m_leftN1Gauge = std::make_unique<Gauge>(
        sf::Vector2f(200.0f, 200.0f), 120.0f, "L-N1", "%", 0.0f, 125.0f, m_font);
    m_leftEGTGauge = std::make_unique<Gauge>(
        sf::Vector2f(200.0f, 480.0f), 100.0f, "L-EGT", "C", 0.0f, 1200.0f, m_font);

    m_rightN1Gauge = std::make_unique<Gauge>(
        sf::Vector2f(1000.0f, 200.0f), 120.0f, "R-N1", "%", 0.0f, 125.0f, m_font);
    m_rightEGTGauge = std::make_unique<Gauge>(
        sf::Vector2f(1000.0f, 480.0f), 100.0f, "R-EGT", "C", 0.0f, 1200.0f, m_font);

    m_indicatorPanel = std::make_unique<IndicatorPanel>(
        sf::Vector2f(560.0f, 100.0f), m_font);

    m_controlPanel = std::make_unique<ControlPanel>(
        sf::Vector2f(520.0f, 610.0f), m_font);
    m_controlPanel->setStartCallback([this]() { onStartPressed(); });
    m_controlPanel->setStopCallback([this]() { onStopPressed(); });
    m_controlPanel->setIncreaseThrustCallback([this]() { onIncreaseThrustPressed(); });
    m_controlPanel->setDecreaseThrustCallback([this]() { onDecreaseThrustPressed(); });

    m_fuelFlowText.emplace(m_font, "Fuel Flow: 0.0 /s", 24);
    m_fuelFlowText->setFillColor(sf::Color::Cyan);
    m_fuelFlowText->setPosition({ 500.0f, 160.0f });

    m_fuelLevelText.emplace(m_font, "Fuel: 20000 / 20000", 24);
    m_fuelLevelText->setFillColor(sf::Color::Green);
    m_fuelLevelText->setPosition({ 500.0f, 200.0f });

    m_alertBackground.setSize({ 400.0f, 200.0f });
    m_alertBackground.setFillColor(sf::Color(20, 20, 30, 200));
    m_alertBackground.setOutlineColor(sf::Color::Red);
    m_alertBackground.setOutlineThickness(2.0f);
    m_alertBackground.setPosition({ 420.0f, 260.0f });

    m_testButton.setSize({ 180.0f, 40.0f });
    m_testButton.setPosition({ 480.0f, 500.0f });
    m_testButton.setFillColor(sf::Color(100, 100, 200));
    m_testButton.setOutlineColor(sf::Color(150, 150, 255));
    m_testButton.setOutlineThickness(2.0f);

    m_testButtonText.emplace(m_font, "", 18);
    m_testButtonText->setString("TEST SCENARIO");
    m_testButtonText->setCharacterSize(18);
    m_testButtonText->setFillColor(sf::Color::White);
    sf::FloatRect testBounds = m_testButtonText->getLocalBounds();
    m_testButtonText->setOrigin({ testBounds.position.x + testBounds.size.x / 2.0f,
                               testBounds.position.y + testBounds.size.y / 2.0f });
    m_testButtonText->setPosition({ 570.0f, 515.0f });

    m_resetButton.setSize({ 180.0f, 40.0f });
    m_resetButton.setPosition({ 660.0f, 500.0f });
    m_resetButton.setFillColor(sf::Color(200, 100, 100));
    m_resetButton.setOutlineColor(sf::Color(255, 150, 150));
    m_resetButton.setOutlineThickness(2.0f);

    m_resetButtonText.emplace(m_font, "RESET", 18);
    m_resetButtonText->setFillColor(sf::Color::White);
    sf::FloatRect resetBounds = m_resetButtonText->getLocalBounds();
    m_resetButtonText->setOrigin({ resetBounds.position.x + resetBounds.size.x / 2.0f,
                               resetBounds.position.y + resetBounds.size.y / 2.0f });
    m_resetButtonText->setPosition({ 750.0f, 515.0f });

    m_testInfoText.emplace(m_font, "Test Mode: Inactive", 20);
    m_testInfoText->setFillColor(sf::Color::Yellow);
    m_testInfoText->setPosition({ 500.0f, 560.0f });
}

void AppController::run() {
    m_logger.startLogging();
    m_clock.restart();

    while (m_window.isOpen()) {
        handleEvents();

        double frameTime = m_clock.restart().asSeconds() * 1000.0;
        m_accumulatedTime += frameTime;

        while (m_accumulatedTime >= UPDATE_INTERVAL_MS) {
            update();
            m_accumulatedTime -= UPDATE_INTERVAL_MS;
            m_totalElapsedMs += static_cast<long long>(UPDATE_INTERVAL_MS);
        }

        render();
    }

    m_logger.stopLogging();
}

void AppController::handleEvents() {
    while (auto event = m_window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            m_window.close();
        }

        if (auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mouseEvent->button == sf::Mouse::Button::Left) {
                sf::Vector2f mousePos(static_cast<float>(mouseEvent->position.x),
                    static_cast<float>(mouseEvent->position.y));

                if (m_controlPanel->handleClick(mousePos)) {
                    continue;
                }

                if (m_testButton.getGlobalBounds().contains(mousePos)) {
                    executeNextTestScenario();
                }

                if (m_resetButton.getGlobalBounds().contains(mousePos)) {
                    resetTestScenario();
                }
            }
        }
    }
}

void AppController::update() {
    // Update engine models
    m_leftEngine.update(UPDATE_INTERVAL_MS);
    m_rightEngine.update(UPDATE_INTERVAL_MS);

    // Update fuel system
    m_fuelSystem.update(m_leftEngine, m_rightEngine, UPDATE_INTERVAL_MS);

    // 如果燃油耗尽（且传感器没有故障导致返回无效值），强制发动机进入停车流程
    // 注意：FuelSystem::getFuelLevel() 在燃油传感器故障时返回 -1.0（无效），因此只在非负且接近 0 时触发
    double fuelLevel = m_fuelSystem.getFuelLevel();
    if (fuelLevel >= 0.0 && fuelLevel < 1e-3) {
        // 仅在发动机正在运行或启动时调用 stop()，以让它进入 STOPPING -> STOP 的过渡
        if (m_leftEngine.getState() == EngineState::STARTING || m_leftEngine.getState() == EngineState::STABLE) {
            m_leftEngine.stop();
        }
        if (m_rightEngine.getState() == EngineState::STARTING || m_rightEngine.getState() == EngineState::STABLE) {
            m_rightEngine.stop();
        }
    }

    // Update fault detection
    m_faultDetector.update(m_leftEngine, m_rightEngine, m_fuelSystem, m_totalElapsedMs);

    // Update gauge displays
    updateGaugeDisplay();

    // Update status indicators
    bool leftStarting = (m_leftEngine.getState() == EngineState::STARTING);
    bool rightStarting = (m_rightEngine.getState() == EngineState::STARTING);
    bool leftStable = (m_leftEngine.getState() == EngineState::STABLE);
    bool rightStable = (m_rightEngine.getState() == EngineState::STABLE);

    m_indicatorPanel->setStartLight(leftStarting || rightStarting);

    bool runOn = leftStable || rightStable;
    bool runDim = false;
    if (runOn) {
        if ((leftStable && m_leftEngine.getN1Percent() < 95.0) ||
            (rightStable && m_rightEngine.getN1Percent() < 95.0)) {
            runDim = true;
        }
    }
    m_indicatorPanel->setRunLight(runOn, runDim);

    if (m_fuelFlowText) {
        std::ostringstream flowSS;
        flowSS << "Fuel Flow: " << std::fixed << std::setprecision(1)
            << m_fuelSystem.getTotalFuelFlow() << " /s";
        m_fuelFlowText->setString(flowSS.str());
    }

    if (m_fuelLevelText) {
        std::ostringstream levelSS;
        levelSS << "Fuel: " << std::fixed << std::setprecision(0)
            << m_fuelSystem.getFuelLevel() << " / 20000";
        m_fuelLevelText->setString(levelSS.str());
    }

    m_logger.log(m_totalElapsedMs, m_leftEngine, m_rightEngine, m_fuelSystem);

    auto alertsToLog = m_faultDetector.getAlertsToLog();
    for (const auto& alert : alertsToLog) {
        m_logger.logAlert(m_totalElapsedMs, alert);
    }

    if (m_testModeActive && (m_totalElapsedMs - m_lastScenarioChangeTime > 10000)) {
        executeNextTestScenario();
    }
}

void AppController::updateGaugeDisplay() {
    const auto& sensorFaults = m_faultDetector.getSensorFaults();

    double leftN1 = m_leftEngine.getN1Percent();
    FaultLevel leftN1Level = m_faultDetector.getN1DisplayLevel(
        leftN1, sensorFaults.leftN1Fault, sensorFaults.anyN1Fault());
    m_leftN1Gauge->setValue(static_cast<float>(leftN1));
    m_leftN1Gauge->setFaultLevel(leftN1Level);

    double leftEGT = m_leftEngine.getTemperature();
    FaultLevel leftEGTLevel = m_faultDetector.getEGTDisplayLevel(
        leftEGT, m_leftEngine.getState(),
        sensorFaults.leftEGTFault, sensorFaults.anyEGTFault());
    m_leftEGTGauge->setValue(static_cast<float>(leftEGT));
    m_leftEGTGauge->setFaultLevel(leftEGTLevel);

    double rightN1 = m_rightEngine.getN1Percent();
    FaultLevel rightN1Level = m_faultDetector.getN1DisplayLevel(
        rightN1, sensorFaults.rightN1Fault, sensorFaults.anyN1Fault());
    m_rightN1Gauge->setValue(static_cast<float>(rightN1));
    m_rightN1Gauge->setFaultLevel(rightN1Level);

    double rightEGT = m_rightEngine.getTemperature();
    FaultLevel rightEGTLevel = m_faultDetector.getEGTDisplayLevel(
        rightEGT, m_rightEngine.getState(),
        sensorFaults.rightEGTFault, sensorFaults.anyEGTFault());
    m_rightEGTGauge->setValue(static_cast<float>(rightEGT));
    m_rightEGTGauge->setFaultLevel(rightEGTLevel);

    if (m_fuelFlowText) {
        FaultLevel flowLevel = m_faultDetector.getFuelFlowDisplayLevel(
            m_fuelSystem.getTotalFuelFlow());
        switch (flowLevel) {
        case FaultLevel::NORMAL:
            m_fuelFlowText->setFillColor(sf::Color::Cyan);
            break;
        case FaultLevel::CAUTION:
            m_fuelFlowText->setFillColor(sf::Color(255, 200, 0)); // Amber
            break;
        case FaultLevel::WARNING:
            m_fuelFlowText->setFillColor(sf::Color::Red);
            break;
        case FaultLevel::INVALID:
            m_fuelFlowText->setFillColor(sf::Color::White);
            m_fuelFlowText->setString("Fuel Flow: -- /s");
            break;
        }
    }

    if (m_fuelLevelText) {
        FaultLevel fuelLevel = m_faultDetector.getFuelDisplayLevel(
            m_fuelSystem.getFuelLevel(), sensorFaults.fuelSensorFault);
        switch (fuelLevel) {
        case FaultLevel::NORMAL:
            m_fuelLevelText->setFillColor(sf::Color::Green);
            break;
        case FaultLevel::CAUTION:
            m_fuelLevelText->setFillColor(sf::Color(255, 200, 0)); // Amber
            break;
        case FaultLevel::WARNING:
            m_fuelLevelText->setFillColor(sf::Color::Red);
            break;
        case FaultLevel::INVALID:
            m_fuelLevelText->setFillColor(sf::Color::White);
            m_fuelLevelText->setString("Fuel: -- / 20000");
            break;
        }
    }
}

void AppController::render() {
    m_window.clear(sf::Color(20, 20, 30));

    m_leftN1Gauge->draw(m_window);
    m_leftEGTGauge->draw(m_window);
    m_rightN1Gauge->draw(m_window);
    m_rightEGTGauge->draw(m_window);

    m_indicatorPanel->draw(m_window);

    m_controlPanel->draw(m_window);

    if (m_fuelFlowText) m_window.draw(*m_fuelFlowText);
    if (m_fuelLevelText) m_window.draw(*m_fuelLevelText);

    sf::Text titleText(m_font, "EICAS - Engine Indication (with Thrust Control & Fault Detection)", 28);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition({ 300.0f, 20.0f });
    m_window.draw(titleText);

    m_window.draw(m_testButton);
    if (m_testButtonText) m_window.draw(*m_testButtonText);
    m_window.draw(m_resetButton);
    if (m_resetButtonText) m_window.draw(*m_resetButtonText);

    if (m_testInfoText) m_window.draw(*m_testInfoText);

    drawAlerts();

    m_window.display();
}

void AppController::drawAlerts() {
    const auto& alerts = m_faultDetector.getActiveAlerts();
    if (alerts.empty()) {
        return;
    }

    m_window.draw(m_alertBackground);

    m_alertTexts.clear();
    float yOffset = 290.0f;

    for (const auto& alert : alerts) {
        sf::Text alertText(m_font, alert.text, 14);

        switch (alert.level) {
        case FaultLevel::NORMAL:
            alertText.setFillColor(sf::Color::White);
            break;
        case FaultLevel::CAUTION:
            alertText.setFillColor(sf::Color(255, 200, 0));
            break;
        case FaultLevel::WARNING:
            alertText.setFillColor(sf::Color::Red);
            break;
        case FaultLevel::INVALID:
            alertText.setFillColor(sf::Color::White);
            break;
        }

        alertText.setPosition({ 420.0f, yOffset });
        m_alertTexts.push_back(alertText);
        yOffset += 30.0f;
    }

    for (const auto& text : m_alertTexts) {
        m_window.draw(text);
    }
}

void AppController::executeNextTestScenario() {
    m_testModeActive = true;
    m_lastScenarioChangeTime = m_totalElapsedMs;

    if (m_testInfoText) {
        std::string testInfo = "Test Mode: Scenario " + std::to_string(m_currentTestScenario + 1) + "/14\n";
        testInfo += m_testGenerator.getTestCaseDescription(m_currentTestScenario);
        m_testInfoText->setString(testInfo);
    }

    if (m_currentTestScenario < m_testGenerator.getTestCaseCount()) {
        m_testGenerator.executeTest(m_currentTestScenario, m_leftEngine, m_rightEngine, m_fuelSystem);
    }

    m_currentTestScenario++;

    if (m_currentTestScenario >= m_testGenerator.getTestCaseCount()) {
        m_testModeActive = false;
        if (m_testInfoText) {
            std::string testInfo = "Test Mode: Scenario " + std::to_string(m_currentTestScenario) + "/14\n";
            testInfo += "14. EGT Overheat 4 (EGT > 1100C at stable)";
            m_testInfoText->setString(testInfo);
        }
        m_currentTestScenario = 0;
    }

    std::cout << "Executed test scenario " << (m_currentTestScenario > 0 ? m_currentTestScenario - 1 : 0)
        << " (next will be: " << m_currentTestScenario << ")" << std::endl;
}

void AppController::resetTestScenario() {
    m_testModeActive = false;
    m_currentTestScenario = 0;
    if (m_testInfoText) m_testInfoText->setString("Test Mode: Inactive");

    m_testGenerator.resetToNormal(m_leftEngine, m_rightEngine, m_fuelSystem);

    m_faultDetector = FaultDetector();

    std::cout << "Test scenarios reset" << std::endl;
}

void AppController::onStartPressed() {
    m_leftEngine.resetTestMode();
    m_rightEngine.resetTestMode();
    m_fuelSystem.resetTestMode();

    m_leftEngine.start();
    m_rightEngine.start();

    m_fuelSystem.reset();

    std::cout << "Engines started" << std::endl;
}

void AppController::onStopPressed() {
    m_leftEngine.stop();
    m_rightEngine.stop();

    std::cout << "Engines stopped" << std::endl;
}

void AppController::onIncreaseThrustPressed() {
    m_leftEngine.increaseThrust();
    m_rightEngine.increaseThrust();
}

void AppController::onDecreaseThrustPressed() {
    m_leftEngine.decreaseThrust();
    m_rightEngine.decreaseThrust();
}