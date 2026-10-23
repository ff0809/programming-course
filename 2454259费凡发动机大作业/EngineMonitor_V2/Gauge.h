#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <optional>
#include "FaultTypes.h"

class Gauge {
public:
    Gauge(sf::Vector2f position, float radius, const std::string& label,
        const std::string& unit, float minValue, float maxValue, const sf::Font& font);

    void setValue(float value);

    void setFaultLevel(FaultLevel level);

    void draw(sf::RenderWindow& window);

private:
    void updateArc();
    void updateDisplayColor();

    sf::Vector2f m_position;
    float m_radius;
    float m_minValue;
    float m_maxValue;
    float m_currentValue;
    FaultLevel m_faultLevel;

    std::string m_label;
    std::string m_unit;

    sf::CircleShape m_background;
    sf::VertexArray m_arc;
    std::optional<sf::Text> m_valueText;
    std::optional<sf::Text> m_labelText;
    const sf::Font& m_font;

    static constexpr float START_ANGLE = 135.0f;
    static constexpr float SWEEP_ANGLE = 210.0f;
};