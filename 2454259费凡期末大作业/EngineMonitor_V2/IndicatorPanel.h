#pragma once

#include <SFML/Graphics.hpp>
#include <optional>

class IndicatorPanel {
public:
    IndicatorPanel(sf::Vector2f position, const sf::Font& font);

    void setStartLight(bool on);

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