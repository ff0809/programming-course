#pragma once

#include <SFML/Graphics.hpp>
#include <optional>

/**
 * Status indicator panel with START and RUN lights
 */
class IndicatorPanel {
public:
    IndicatorPanel(sf::Vector2f position, const sf::Font& font);

    /**
     * Set START light state
     */
    void setStartLight(bool on);

    /**
     * Set RUN light state
     * @param on Whether lit
     * @param dim Whether dimmed (abnormal state)
     */
    void setRunLight(bool on, bool dim = false);

    void draw(sf::RenderWindow& window);

private:
    sf::Vector2f m_position;
    const sf::Font& m_font;

    sf::CircleShape m_startLight;
    sf::CircleShape m_runLight;
    std::optional<sf::Text> m_startLabel;
    std::optional<sf::Text> m_runLabel;

    bool m_startOn;
    bool m_runOn;
    bool m_runDim;
};
