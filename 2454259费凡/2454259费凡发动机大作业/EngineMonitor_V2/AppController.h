#pragma once

#include "EngineModel.h"
#include "FuelSystem.h"
#include "Gauge.h"
#include "IndicatorPanel.h"
#include "ControlPanel.h"
#include "DataLogger.h"
#include "FaultDetector.h"
#include "TestScenarioGenerator.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <optional>
#include <vector>

class AppController {
public:
    static constexpr int WINDOW_WIDTH = 1200;
    static constexpr int WINDOW_HEIGHT = 700;
    static constexpr double UPDATE_INTERVAL_MS = 5.0;

    AppController();
    void run();

private:
    void handleEvents();
    void update();
    void render();
    void updateGaugeDisplay();

    void onStartPressed();
    void onStopPressed();
    void onIncreaseThrustPressed();
    void onDecreaseThrustPressed();

    void drawAlerts();
    void executeNextTestScenario();
    void resetTestScenario();

    // SFML3.0 window
    sf::RenderWindow m_window;
    sf::Font m_font;

    EngineModel m_leftEngine;
    EngineModel m_rightEngine;
    FuelSystem m_fuelSystem;

    FaultDetector m_faultDetector;

    TestScenarioGenerator m_testGenerator;

    std::unique_ptr<Gauge> m_leftN1Gauge;
    std::unique_ptr<Gauge> m_leftEGTGauge;
    std::unique_ptr<Gauge> m_rightN1Gauge;
    std::unique_ptr<Gauge> m_rightEGTGauge;
    std::unique_ptr<IndicatorPanel> m_indicatorPanel;
    std::unique_ptr<ControlPanel> m_controlPanel;

    std::optional<sf::Text> m_fuelFlowText;
    std::optional<sf::Text> m_fuelLevelText;

    std::vector<sf::Text> m_alertTexts;
    sf::RectangleShape m_alertBackground;

    sf::RectangleShape m_testButton;
    std::optional<sf::Text> m_testButtonText;
    sf::RectangleShape m_resetButton;
    std::optional<sf::Text> m_resetButtonText;
    std::optional<sf::Text> m_testInfoText;

    int m_currentTestScenario;
    bool m_testModeActive;
    long long m_lastScenarioChangeTime;

    DataLogger m_logger;

    sf::Clock m_clock;
    double m_accumulatedTime;
    long long m_totalElapsedMs;
};