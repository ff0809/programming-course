#pragma once

#include "EngineModel.h"
#include "FuelSystem.h"
#include "Gauge.h"
#include "IndicatorPanel.h"
#include "ControlPanel.h"
#include "DataLogger.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <optional>

/**
 * Application controller - coordinates model, view and data logging
 */
class AppController {
public:
    static constexpr int WINDOW_WIDTH = 1200;
    static constexpr int WINDOW_HEIGHT = 700;
    static constexpr double UPDATE_INTERVAL_MS = 5.0;  // 5ms update cycle

    AppController();

    /**
     * Run main loop
     */
    void run();

private:
    void handleEvents();
    void update();
    void render();

    void onStartPressed();
    void onStopPressed();

    // SFML window
    sf::RenderWindow m_window;
    sf::Font m_font;

    // Model
    EngineModel m_leftEngine;
    EngineModel m_rightEngine;
    FuelSystem m_fuelSystem;

    // View
    std::unique_ptr<Gauge> m_leftN1Gauge;
    std::unique_ptr<Gauge> m_leftEGTGauge;
    std::unique_ptr<Gauge> m_rightN1Gauge;
    std::unique_ptr<Gauge> m_rightEGTGauge;
    std::unique_ptr<IndicatorPanel> m_indicatorPanel;
    std::unique_ptr<ControlPanel> m_controlPanel;

    // Fuel flow text display
    std::optional<sf::Text> m_fuelFlowText;
    std::optional<sf::Text> m_fuelLevelText;

    // Data logging
    DataLogger m_logger;

    // Time management
    sf::Clock m_clock;
    double m_accumulatedTime;
    long long m_totalElapsedMs;
};
