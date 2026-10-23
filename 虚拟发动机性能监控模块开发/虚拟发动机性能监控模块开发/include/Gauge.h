#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <optional>

/**
 * Gauge control for N1 and EGT display
 * Supports arc progress bar and digital display
 */
class Gauge {
public:
    /**
     * Constructor
     * @param position Gauge center position
     * @param radius Gauge radius
     * @param label Label text (e.g. "N1", "EGT")
     * @param unit Unit (e.g. "%", "C")
     * @param minValue Minimum value
     * @param maxValue Maximum value
     * @param font Font reference
     */
    Gauge(sf::Vector2f position, float radius, const std::string& label,
          const std::string& unit, float minValue, float maxValue, const sf::Font& font);

    /**
     * Set current value
     * @param value Current value
     */
    void setValue(float value);

    /**
     * Render gauge
     * @param window Render window
     */
    void draw(sf::RenderWindow& window);

private:
    void updateArc();

    sf::Vector2f m_position;
    float m_radius;
    float m_minValue;
    float m_maxValue;
    float m_currentValue;

    std::string m_label;
    std::string m_unit;

    // SFML graphics elements
    sf::CircleShape m_background;
    sf::VertexArray m_arc;
    std::optional<sf::Text> m_valueText;
    std::optional<sf::Text> m_labelText;
    const sf::Font& m_font;

    // Angle range: 0 to 210 degrees (clockwise from bottom left)
    static constexpr float START_ANGLE = 135.0f;
    static constexpr float SWEEP_ANGLE = 210.0f;
};
