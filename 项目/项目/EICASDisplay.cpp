#include "EICASDisplay.h"
#include <sstream>

EICASDisplay::EICASDisplay()
    : window(sf::VideoMode(1000, 600), "EICAS") {

    window.setFramerateLimit(60);
    font.loadFromFile("arial.ttf");

    n1GaugeL.setRadius(120);
    n1GaugeL.setOutlineThickness(3);
    n1GaugeL.setOutlineColor(sf::Color::White);
    n1GaugeL.setFillColor(sf::Color::Transparent);
    n1GaugeL.setPosition(100, 200);

    n1GaugeR = n1GaugeL;
    n1GaugeR.setPosition(350, 200);

    needleL.setSize({ 110, 3 });
    needleL.setOrigin(0, 1.5);
    needleL.setPosition(220, 320);
    needleL.setFillColor(sf::Color::Red);

    needleR = needleL;
    needleR.setPosition(470, 320);

    fuelBar.setSize({ 20, 200 });
    fuelBar.setPosition(750, 200);
    fuelBar.setFillColor(sf::Color::Green);

    fuelText.setFont(font);
    fuelText.setPosition(720, 420);

    egtText.setFont(font);
    egtText.setPosition(720, 150);

    alertText.setFont(font);
    alertText.setCharacterSize(18);
    alertText.setPosition(50, 20);

    stopBtn.setSize({ 120, 50 });
    stopBtn.setFillColor(sf::Color::Red);
    stopBtn.setPosition(820, 520);

    stopText.setFont(font);
    stopText.setString("STOP");
    stopText.setPosition(850, 530);
}

bool EICASDisplay::isOpen() const {
    return window.isOpen();
}

bool EICASDisplay::stopPressed() {
    bool v = stopClicked;
    stopClicked = false;
    return v;
}

void EICASDisplay::processEvents() {
    sf::Event e;
    while (window.pollEvent(e)) {
        if (e.type == sf::Event::Closed)
            window.close();
        if (e.type == sf::Event::MouseButtonPressed) {
            auto p = sf::Mouse::getPosition(window);
            if (stopBtn.getGlobalBounds().contains(p.x, p.y))
                stopClicked = true;
        }
    }
}

float EICASDisplay::mapAngle(float v) {
    return -105 + (v / 110.f) * 210.f;
}

void EICASDisplay::render(const EngineData& d) {
    window.clear(sf::Color::Black);

    needleL.setRotation(mapAngle(d.n1_1));
    needleR.setRotation(mapAngle(d.n1_2));

    fuelBar.setSize({ 20, (float)(200 * d.fuelLevel / 5000) });

    std::ostringstream ss;
    ss << "EGT: " << d.egt_avg;
    egtText.setString(ss.str());

    ss.str("");
    ss << "FUEL: " << d.fuelLevel;
    fuelText.setString(ss.str());

    ss.str("");
    for (auto& a : d.alerts) ss << a << "\n";
    alertText.setString(ss.str());

    window.draw(n1GaugeL);
    window.draw(n1GaugeR);
    window.draw(needleL);
    window.draw(needleR);
    window.draw(fuelBar);
    window.draw(fuelText);
    window.draw(egtText);
    window.draw(alertText);
    window.draw(stopBtn);
    window.draw(stopText);

    window.display();
}
