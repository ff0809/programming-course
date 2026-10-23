#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <optional>

class ControlPanel {
public:
    using ButtonCallback = std::function<void()>;

    ControlPanel(sf::Vector2f position, const sf::Font& font);

    void setStartCallback(ButtonCallback callback);
    void setStopCallback(ButtonCallback callback);
    void setIncreaseThrustCallback(ButtonCallback callback);
    void setDecreaseThrustCallback(ButtonCallback callback);

    bool handleClick(sf::Vector2f mousePos);

    void draw(sf::RenderWindow& window);

private:
    sf::Vector2f m_position;
    const sf::Font& m_font;

    sf::RectangleShape m_startButton;
    sf::RectangleShape m_stopButton;
    sf::RectangleShape m_increaseThrustButton;
    sf::RectangleShape m_decreaseThrustButton;

    std::optional<sf::Text> m_startText;
    std::optional<sf::Text> m_stopText;
    std::optional<sf::Text> m_increaseThrustText;
    std::optional<sf::Text> m_decreaseThrustText;

    ButtonCallback m_startCallback;
    ButtonCallback m_stopCallback;
    ButtonCallback m_increaseThrustCallback;
    ButtonCallback m_decreaseThrustCallback;
};