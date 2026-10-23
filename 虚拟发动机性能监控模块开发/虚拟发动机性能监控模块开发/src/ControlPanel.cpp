#include "ControlPanel.h"

ControlPanel::ControlPanel(sf::Vector2f position, const sf::Font& font)
    : m_position(position)
    , m_font(font)
{
    const sf::Vector2f buttonSize(100.0f, 40.0f);
    const float spacing = 20.0f;

    // Start button
    m_startButton.setSize(buttonSize);
    m_startButton.setPosition(position);
    m_startButton.setFillColor(sf::Color(0, 120, 60));
    m_startButton.setOutlineColor(sf::Color(0, 200, 100));
    m_startButton.setOutlineThickness(2.0f);

    m_startText.emplace(font, "START", 18);
    m_startText->setFillColor(sf::Color::White);
    sf::FloatRect startBounds = m_startText->getLocalBounds();
    m_startText->setOrigin({startBounds.position.x + startBounds.size.x / 2.0f, 
                           startBounds.position.y + startBounds.size.y / 2.0f});
    m_startText->setPosition({position.x + buttonSize.x / 2.0f, position.y + buttonSize.y / 2.0f});

    // Stop button
    m_stopButton.setSize(buttonSize);
    m_stopButton.setPosition({position.x + buttonSize.x + spacing, position.y});
    m_stopButton.setFillColor(sf::Color(150, 30, 30));
    m_stopButton.setOutlineColor(sf::Color(255, 50, 50));
    m_stopButton.setOutlineThickness(2.0f);

    m_stopText.emplace(font, "STOP", 18);
    m_stopText->setFillColor(sf::Color::White);
    sf::FloatRect stopBounds = m_stopText->getLocalBounds();
    m_stopText->setOrigin({stopBounds.position.x + stopBounds.size.x / 2.0f, 
                          stopBounds.position.y + stopBounds.size.y / 2.0f});
    m_stopText->setPosition({position.x + buttonSize.x + spacing + buttonSize.x / 2.0f, 
                            position.y + buttonSize.y / 2.0f});
}

void ControlPanel::setStartCallback(ButtonCallback callback) {
    m_startCallback = callback;
}

void ControlPanel::setStopCallback(ButtonCallback callback) {
    m_stopCallback = callback;
}

bool ControlPanel::handleClick(sf::Vector2f mousePos) {
    // Stop button has higher priority
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

    return false;
}

void ControlPanel::draw(sf::RenderWindow& window) {
    window.draw(m_startButton);
    if (m_startText) window.draw(*m_startText);
    window.draw(m_stopButton);
    if (m_stopText) window.draw(*m_stopText);
}
