#include "ControlPanel.h"

ControlPanel::ControlPanel(sf::Vector2f position, const sf::Font& font)
    : m_position(position)
    , m_font(font)
{
    const sf::Vector2f buttonSize(100.0f, 40.0f);
    const float horizontalSpacing = 20.0f;
    const float verticalSpacing = 60.0f;

    m_startButton.setSize(buttonSize);
    m_startButton.setPosition(position);
    m_startButton.setFillColor(sf::Color(0, 120, 60));
    m_startButton.setOutlineColor(sf::Color(0, 200, 100));
    m_startButton.setOutlineThickness(2.0f);

    m_startText.emplace(font, "START", 18);
    m_startText->setFillColor(sf::Color::White);
    sf::FloatRect startBounds = m_startText->getLocalBounds();
    m_startText->setOrigin({ startBounds.position.x + startBounds.size.x / 2.0f,
                           startBounds.position.y + startBounds.size.y / 2.0f });
    m_startText->setPosition({ position.x + buttonSize.x / 2.0f, position.y + buttonSize.y / 2.0f });

    m_stopButton.setSize(buttonSize);
    m_stopButton.setPosition({ position.x + buttonSize.x + horizontalSpacing, position.y });
    m_stopButton.setFillColor(sf::Color(150, 30, 30));
    m_stopButton.setOutlineColor(sf::Color(255, 50, 50));
    m_stopButton.setOutlineThickness(2.0f);

    m_stopText.emplace(font, "STOP", 18);
    m_stopText->setFillColor(sf::Color::White);
    sf::FloatRect stopBounds = m_stopText->getLocalBounds();
    m_stopText->setOrigin({ stopBounds.position.x + stopBounds.size.x / 2.0f,
                          stopBounds.position.y + stopBounds.size.y / 2.0f });
    m_stopText->setPosition({ position.x + buttonSize.x + horizontalSpacing + buttonSize.x / 2.0f,
                            position.y + buttonSize.y / 2.0f });

    m_increaseThrustButton.setSize(buttonSize);
    m_increaseThrustButton.setPosition({ position.x, position.y + verticalSpacing });
    m_increaseThrustButton.setFillColor(sf::Color(30, 60, 120));
    m_increaseThrustButton.setOutlineColor(sf::Color(50, 100, 200));
    m_increaseThrustButton.setOutlineThickness(2.0f);

    m_increaseThrustText.emplace(font, "+THRUST", 16);
    m_increaseThrustText->setFillColor(sf::Color::White);
    sf::FloatRect incBounds = m_increaseThrustText->getLocalBounds();
    m_increaseThrustText->setOrigin({ incBounds.position.x + incBounds.size.x / 2.0f,
                                    incBounds.position.y + incBounds.size.y / 2.0f });
    m_increaseThrustText->setPosition({ position.x + buttonSize.x / 2.0f,
                                      position.y + verticalSpacing + buttonSize.y / 2.0f });

    m_decreaseThrustButton.setSize(buttonSize);
    m_decreaseThrustButton.setPosition({ position.x + buttonSize.x + horizontalSpacing,
                                       position.y + verticalSpacing });
    m_decreaseThrustButton.setFillColor(sf::Color(120, 60, 30));
    m_decreaseThrustButton.setOutlineColor(sf::Color(200, 100, 50));
    m_decreaseThrustButton.setOutlineThickness(2.0f);

    m_decreaseThrustText.emplace(font, "-THRUST", 16);
    m_decreaseThrustText->setFillColor(sf::Color::White);
    sf::FloatRect decBounds = m_decreaseThrustText->getLocalBounds();
    m_decreaseThrustText->setOrigin({ decBounds.position.x + decBounds.size.x / 2.0f,
                                    decBounds.position.y + decBounds.size.y / 2.0f });
    m_decreaseThrustText->setPosition({ position.x + buttonSize.x + horizontalSpacing + buttonSize.x / 2.0f,
                                      position.y + verticalSpacing + buttonSize.y / 2.0f });
}

void ControlPanel::setStartCallback(ButtonCallback callback) {
    m_startCallback = callback;
}

void ControlPanel::setStopCallback(ButtonCallback callback) {
    m_stopCallback = callback;
}

void ControlPanel::setIncreaseThrustCallback(ButtonCallback callback) {
    m_increaseThrustCallback = callback;
}

void ControlPanel::setDecreaseThrustCallback(ButtonCallback callback) {
    m_decreaseThrustCallback = callback;
}

bool ControlPanel::handleClick(sf::Vector2f mousePos) {
    if (m_stopButton.getGlobalBounds().contains(mousePos)) {
        if (m_stopCallback) {
            m_stopCallback();
        }
        return true;
    }

    if (m_startButton.getGlobalBounds().contains(mousePos)) {
        if (m_startCallback) {
            m_startCallback();
        }
        return true;
    }

    if (m_increaseThrustButton.getGlobalBounds().contains(mousePos)) {
        if (m_increaseThrustCallback) {
            m_increaseThrustCallback();
        }
        return true;
    }

    if (m_decreaseThrustButton.getGlobalBounds().contains(mousePos)) {
        if (m_decreaseThrustCallback) {
            m_decreaseThrustCallback();
        }
        return true;
    }

    return false;
}

void ControlPanel::draw(sf::RenderWindow& window) {
    window.draw(m_startButton);
    if (m_startText) window.draw(*m_startText);
    window.draw(m_stopButton);
    if (m_stopText) window.draw(*m_stopText);
    window.draw(m_increaseThrustButton);
    if (m_increaseThrustText) window.draw(*m_increaseThrustText);
    window.draw(m_decreaseThrustButton);
    if (m_decreaseThrustText) window.draw(*m_decreaseThrustText);
}