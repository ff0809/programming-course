#include "Gauge.h"
#include <cmath>
#include <sstream>
#include <iomanip>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Gauge::Gauge(sf::Vector2f position, float radius, const std::string& label,
             const std::string& unit, float minValue, float maxValue, const sf::Font& font)
    : m_position(position)
    , m_radius(radius)
    , m_minValue(minValue)
    , m_maxValue(maxValue)
    , m_currentValue(minValue)
    , m_label(label)
    , m_unit(unit)
    , m_arc(sf::PrimitiveType::TriangleFan)
    , m_font(font)
{
    // Setup background circle
    m_background.setRadius(radius);
    m_background.setOrigin({radius, radius});
    m_background.setPosition(position);
    m_background.setFillColor(sf::Color(30, 30, 40));
    m_background.setOutlineColor(sf::Color(80, 80, 100));
    m_background.setOutlineThickness(3.0f);

    // Setup label text
    m_labelText.emplace(m_font, label, static_cast<unsigned int>(radius * 0.25f));
    m_labelText->setFillColor(sf::Color::White);
    sf::FloatRect labelBounds = m_labelText->getLocalBounds();
    m_labelText->setOrigin({labelBounds.position.x + labelBounds.size.x / 2.0f, 
                           labelBounds.position.y + labelBounds.size.y / 2.0f});
    m_labelText->setPosition({position.x, position.y - radius * 0.3f});

    // Setup value text
    m_valueText.emplace(m_font, "0.0", static_cast<unsigned int>(radius * 0.35f));
    m_valueText->setFillColor(sf::Color::Cyan);
    m_valueText->setPosition({position.x, position.y + radius * 0.15f});

    updateArc();
}

void Gauge::setValue(float value) {
    m_currentValue = std::clamp(value, m_minValue, m_maxValue);
    updateArc();
}

void Gauge::updateArc() {
    m_arc.clear();

    // Calculate angle for current value
    float valueRatio = (m_currentValue - m_minValue) / (m_maxValue - m_minValue);
    float currentSweep = valueRatio * SWEEP_ANGLE;

    // Arc segments
    const int segments = 60;
    float innerRadius = m_radius * 0.7f;
    float outerRadius = m_radius * 0.95f;

    // Use TriangleStrip to draw arc
    m_arc = sf::VertexArray(sf::PrimitiveType::TriangleStrip);

    for (int i = 0; i <= segments; ++i) {
        float ratio = static_cast<float>(i) / segments;
        if (ratio > valueRatio) break;

        float angle = (START_ANGLE + ratio * SWEEP_ANGLE) * static_cast<float>(M_PI) / 180.0f;
        float cosA = std::cos(angle);
        float sinA = std::sin(angle);

        // Determine color (green -> yellow -> red)
        sf::Color color;
        if (ratio < 0.6f) {
            color = sf::Color(0, 255, 100);  // Green
        } else if (ratio < 0.85f) {
            color = sf::Color(255, 200, 0);  // Yellow
        } else {
            color = sf::Color(255, 50, 50);  // Red
        }

        // Inner vertex
        sf::Vertex innerVertex;
        innerVertex.position = {m_position.x + innerRadius * cosA, m_position.y + innerRadius * sinA};
        innerVertex.color = color;
        m_arc.append(innerVertex);

        // Outer vertex
        sf::Vertex outerVertex;
        outerVertex.position = {m_position.x + outerRadius * cosA, m_position.y + outerRadius * sinA};
        outerVertex.color = color;
        m_arc.append(outerVertex);
    }

    // Update value text
    if (m_valueText) {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(1) << m_currentValue << m_unit;
        m_valueText->setString(oss.str());
        sf::FloatRect valueBounds = m_valueText->getLocalBounds();
        m_valueText->setOrigin({valueBounds.position.x + valueBounds.size.x / 2.0f, 
                               valueBounds.position.y + valueBounds.size.y / 2.0f});
    }
}

void Gauge::draw(sf::RenderWindow& window) {
    window.draw(m_background);
    window.draw(m_arc);
    if (m_labelText) window.draw(*m_labelText);
    if (m_valueText) window.draw(*m_valueText);
}
