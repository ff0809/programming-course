#include "AppController.h"
#include <sstream>
#include <iomanip>

AppController::AppController()
    : m_window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Virtual Engine Performance Monitor - EICAS")
    , m_accumulatedTime(0.0)
    , m_totalElapsedMs(0)
{
    m_window.setFramerateLimit(60);

    // Load font
    if (!m_font.openFromFile("resources/arial.ttf")) {
        // Try system font path
        if (!m_font.openFromFile("C:/Windows/Fonts/arial.ttf")) {
            throw std::runtime_error("Failed to load font!");
        }
    }

    // Create gauges (left engine)
    m_leftN1Gauge = std::make_unique<Gauge>(
        sf::Vector2f(200.0f, 200.0f), 120.0f, "L-N1", "%", 0.0f, 125.0f, m_font);
    m_leftEGTGauge = std::make_unique<Gauge>(
        sf::Vector2f(200.0f, 480.0f), 100.0f, "L-EGT", "C", 0.0f, 1200.0f, m_font);

    // Create gauges (right engine)
    m_rightN1Gauge = std::make_unique<Gauge>(
        sf::Vector2f(1000.0f, 200.0f), 120.0f, "R-N1", "%", 0.0f, 125.0f, m_font);
    m_rightEGTGauge = std::make_unique<Gauge>(
        sf::Vector2f(1000.0f, 480.0f), 100.0f, "R-EGT", "C", 0.0f, 1200.0f, m_font);

    // Create status indicator panel
    m_indicatorPanel = std::make_unique<IndicatorPanel>(
        sf::Vector2f(560.0f, 100.0f), m_font);

    // Create control panel
    m_controlPanel = std::make_unique<ControlPanel>(
        sf::Vector2f(490.0f, 600.0f), m_font);
    m_controlPanel->setStartCallback([this]() { onStartPressed(); });
    m_controlPanel->setStopCallback([this]() { onStopPressed(); });

    // Fuel flow display
    m_fuelFlowText.emplace(m_font, "Fuel Flow: 0.0 /s", 24);
    m_fuelFlowText->setFillColor(sf::Color::Cyan);
    m_fuelFlowText->setPosition({550.0f, 250.0f});

    // Fuel level display
    m_fuelLevelText.emplace(m_font, "Fuel: 20000 / 20000", 24);
    m_fuelLevelText->setFillColor(sf::Color::Green);
    m_fuelLevelText->setPosition({550.0f, 290.0f});
}

void AppController::run() {
    m_logger.startLogging();
    m_clock.restart();

    while (m_window.isOpen()) {
        handleEvents();
        
        // Accumulate time
        double frameTime = m_clock.restart().asSeconds() * 1000.0;  // Convert to ms
        m_accumulatedTime += frameTime;

        // Fixed time step update (5ms)
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
                m_controlPanel->handleClick(mousePos);
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

    // Update gauge displays
    m_leftN1Gauge->setValue(static_cast<float>(m_leftEngine.getN1Percent()));
    m_leftEGTGauge->setValue(static_cast<float>(m_leftEngine.getTemperature()));
    m_rightN1Gauge->setValue(static_cast<float>(m_rightEngine.getN1Percent()));
    m_rightEGTGauge->setValue(static_cast<float>(m_rightEngine.getTemperature()));

    // Update status indicators
    bool leftStarting = (m_leftEngine.getState() == EngineState::STARTING);
    bool rightStarting = (m_rightEngine.getState() == EngineState::STARTING);
    bool leftStable = (m_leftEngine.getState() == EngineState::STABLE);
    bool rightStable = (m_rightEngine.getState() == EngineState::STABLE);

    m_indicatorPanel->setStartLight(leftStarting || rightStarting);
    
    // RUN light logic: lit when stable, dimmed when N1 < 95%
    bool runOn = leftStable || rightStable;
    bool runDim = false;
    if (runOn) {
        if ((leftStable && m_leftEngine.getN1Percent() < 95.0) ||
            (rightStable && m_rightEngine.getN1Percent() < 95.0)) {
            runDim = true;
        }
    }
    m_indicatorPanel->setRunLight(runOn, runDim);

    // Update fuel display text
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

    // Log data
    m_logger.log(m_totalElapsedMs, m_leftEngine, m_rightEngine, m_fuelSystem);
}

void AppController::render() {
    m_window.clear(sf::Color(20, 20, 30));

    // Draw gauges
    m_leftN1Gauge->draw(m_window);
    m_leftEGTGauge->draw(m_window);
    m_rightN1Gauge->draw(m_window);
    m_rightEGTGauge->draw(m_window);

    // Draw status indicators
    m_indicatorPanel->draw(m_window);

    // Draw control panel
    m_controlPanel->draw(m_window);

    // Draw fuel info
    if (m_fuelFlowText) m_window.draw(*m_fuelFlowText);
    if (m_fuelLevelText) m_window.draw(*m_fuelLevelText);

    // Draw title
    sf::Text titleText(m_font, "EICAS - Engine Indication", 28);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition({450.0f, 20.0f});
    m_window.draw(titleText);

    m_window.display();
}

void AppController::onStartPressed() {
    // Start both engines
    m_leftEngine.start();
    m_rightEngine.start();
    // Reset fuel
    m_fuelSystem.reset();
}

void AppController::onStopPressed() {
    // Stop both engines (Stop has highest priority)
    m_leftEngine.stop();
    m_rightEngine.stop();
}
