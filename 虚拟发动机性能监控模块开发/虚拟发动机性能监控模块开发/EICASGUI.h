// EICASGUI.h
#ifndef EICASGUI_H
#define EICASGUI_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <utility>
#include <chrono>
#include <memory>

#include "EngineMonitor.h"
#include "DataLogger.h"

class EngineSimulator;
class DataLogger;

class EICASGUI {
private:
    sf::RenderWindow window;
    EngineSimulator& simulator;
    DataLogger& logger;

    // 字体
    sf::Font font;
    bool font_loaded = false;

    // 颜色
    sf::Color normal_color;
    sf::Color warning_color;
    sf::Color alarm_color;
    sf::Color invalid_color;

    // 按钮
    sf::RectangleShape start_button;
    sf::RectangleShape stop_button;
    sf::RectangleShape increase_thrust_button;
    sf::RectangleShape decrease_thrust_button;

    // 状态框
    sf::RectangleShape start_status_box;
    sf::RectangleShape run_status_box;

    // 表盘
    sf::CircleShape N1_gauge;
    sf::CircleShape EGT_gauge;

    // 警报列表
    std::vector<std::pair<AlertType, std::chrono::steady_clock::time_point>> active_alerts;

    // 调试用帧计数器
    int frame_count = 0;

    // SFML 3.0 文本对象（作为成员变量以避免重复构造）
    std::unique_ptr<sf::Text> N1_text;
    std::unique_ptr<sf::Text> EGT_text;
    std::unique_ptr<sf::Text> fuel_text;
    std::unique_ptr<sf::Text> start_text;
    std::unique_ptr<sf::Text> stop_text;
    std::unique_ptr<sf::Text> inc_text;
    std::unique_ptr<sf::Text> dec_text;
    std::unique_ptr<sf::Text> alert_text;

public:
    EICASGUI(EngineSimulator& sim, DataLogger& log);
    ~EICASGUI() = default;

    void run();

private:
    void setupUI();
    void initTextObjects();  // 新增：初始化文本对象
    void handleEvents();
    void update();
    void render();
    void updateStatusBoxes(EngineState state);
    void updateGauges(const EngineData& data);
    void drawText();
    void drawAlerts();
    sf::Color getStatusColor(SensorStatus status);
    void addAlert(AlertType alert, const std::string& message);
};

#endif // EICASGUI_H