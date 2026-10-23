#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <optional>

/**
 * Control panel with Start and Stop buttons
 */
class ControlPanel {
public:
    using ButtonCallback = std::function<void()>;

    ControlPanel(sf::Vector2f position, const sf::Font& font);

    /**
     * Set Start button callback
     */
    void setStartCallback(ButtonCallback callback);

    /**
     * Set Stop button callback
     */
    void setStopCallback(ButtonCallback callback);

    /**
     * Handle mouse click event
     * @param mousePos Mouse position
     * @return Whether a button was clicked
     */
    bool handleClick(sf::Vector2f mousePos);

    void draw(sf::RenderWindow& window);

private:
    sf::Vector2f m_position;
    const sf::Font& m_font;

    sf::RectangleShape m_startButton;
    sf::RectangleShape m_stopButton;
    std::optional<sf::Text> m_startText;
    std::optional<sf::Text> m_stopText;

    ButtonCallback m_startCallback;
    ButtonCallback m_stopCallback;
};
