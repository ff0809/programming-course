#include "IndicatorPanel.h"

IndicatorPanel::IndicatorPanel(sf::Vector2f position, const sf::Font& font)
    : m_position(position)
    , m_font(font)
    , m_startOn(false)
    , m_runOn(false)
    , m_runDim(false)
{
    const float lightRadius = 15.0f;
    const float spacing = 80.0f;

    // START light
    m_startLight.setRadius(lightRadius);
    m_startLight.setOrigin({lightRadius, lightRadius});
    m_startLight.setPosition({position.x, position.y});
    m_startLight.setFillColor(sf::Color(50, 50, 50));
    m_startLight.setOutlineColor(sf::Color(100, 100, 100));
    m_startLight.setOutlineThickness(2.0f);

    m_startLabel.emplace(font, "START", 14);
    m_startLabel->setFillColor(sf::Color::White);
    sf::FloatRect startBounds = m_startLabel->getLocalBounds();
    m_startLabel->setOrigin({startBounds.position.x + startBounds.size.x / 2.0f, 
                            startBounds.position.y + startBounds.size.y / 2.0f});
    m_startLabel->setPosition({position.x, position.y + 30.0f});

    // RUN light
    m_runLight.setRadius(lightRadius);
    m_runLight.setOrigin({lightRadius, lightRadius});
    m_runLight.setPosition({position.x + spacing, position.y});
    m_runLight.setFillColor(sf::Color(50, 50, 50));
    m_runLight.setOutlineColor(sf::Color(100, 100, 100));
    m_runLight.setOutlineThickness(2.0f);

    m_runLabel.emplace(font, "RUN", 14);
    m_runLabel->setFillColor(sf::Color::White);
    sf::FloatRect runBounds = m_runLabel->getLocalBounds();
    m_runLabel->setOrigin({runBounds.position.x + runBounds.size.x / 2.0f, 
                          runBounds.position.y + runBounds.size.y / 2.0f});
    m_runLabel->setPosition({position.x + spacing, position.y + 30.0f});
}

void IndicatorPanel::setStartLight(bool on) {
    m_startOn = on;
    if (on) {
        m_startLight.setFillColor(sf::Color(255, 200, 0));  // Yellow
    } else {
        m_startLight.setFillColor(sf::Color(50, 50, 50));   // Dark gray
    }
}

void IndicatorPanel::setRunLight(bool on, bool dim) {
    m_runOn = on;
    m_runDim = dim;
    
    if (on) {
        if (dim) {
            m_runLight.setFillColor(sf::Color(50, 100, 50));   // Dark green
        } else {
            m_runLight.setFillColor(sf::Color(0, 255, 100));   // Bright green
        }
    } else {
        m_runLight.setFillColor(sf::Color(50, 50, 50));        // Dark gray
    }
}

void IndicatorPanel::draw(sf::RenderWindow& window) {
    window.draw(m_startLight);
    if (m_startLabel) window.draw(*m_startLabel);
    window.draw(m_runLight);
    if (m_runLabel) window.draw(*m_runLabel);
}
