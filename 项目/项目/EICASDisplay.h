#pragma once
#include <SFML/Graphics.hpp>
#include "EngineData.h"

class EICASDisplay {
public:
    EICASDisplay();
    bool isOpen() const;
    bool stopPressed();
    void processEvents();
    void render(const EngineData& data);

private:
    sf::RenderWindow window;
    sf::Font font;

    sf::CircleShape n1GaugeL, n1GaugeR;
    sf::RectangleShape needleL, needleR;

    sf::RectangleShape fuelBar;
    sf::Text fuelText, egtText, alertText;

    sf::RectangleShape stopBtn;
    sf::Text stopText;

    bool stopClicked = false;
    float mapAngle(float v);
};
