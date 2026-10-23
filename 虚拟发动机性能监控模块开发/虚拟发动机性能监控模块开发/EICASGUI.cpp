// EICASGUI.cpp
#define _CRT_SECURE_NO_WARNINGS
#include "EICASGUI.h"
#include "EngineSimulator.h"
#include "DataLogger.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <chrono>
#include <vector>

// 局部 alert->string 映射（GUI 显示用）
static std::string alertToStringLocal(AlertType alert) {
    switch (alert) {
    case N1S1_FAIL: return "N1S1_FAIL";
    case N1S2_FAIL: return "N1S2_FAIL";
    case N1_S_FAIL: return "N1_S_FAIL";
    case EGT_S_FAIL: return "EGT_S_FAIL";
    case EGTS1_FAIL: return "EGTS1_FAIL";
    case EGTS2_FAIL: return "EGTS2_FAIL";
    case EGTS_FAIL: return "EGTS_FAIL";
    case LOW_FUEL: return "LOW_FUEL";
    case FUEL_S_FAIL: return "FUEL_S_FAIL";
    case OVER_FUEL_FLOW: return "OVER_FUEL_FLOW";
    case OVER_SPEED1: return "OVER_SPEED1";
    case OVER_SPEED2: return "OVER_SPEED2";
    case OVER_TEMP1: return "OVER_TEMP1";
    case OVER_TEMP2: return "OVER_TEMP2";
    case OVER_TEMP3: return "OVER_TEMP3";
    case OVER_TEMP4: return "OVER_TEMP4";
    default: return "Unknown Alert";
    }
}

EICASGUI::EICASGUI(EngineSimulator& sim, DataLogger& log)
    : window(sf::VideoMode({ 1200u, 800u }), "Virtual Engine EICAS"),
    simulator(sim), logger(log),
    normal_color(sf::Color::White),
    warning_color(sf::Color(255, 191, 0)),
    alarm_color(sf::Color::Red),
    invalid_color(sf::Color(128, 128, 128)) {

    window.setFramerateLimit(200); // 5ms 对应 200Hz

    // SFML 3.0 字体加载 - 使用 openFromFile
    bool font_ok = false;

    // 尝试加载字体文件的路径列表
    std::vector<std::string> fontPaths = {
        "ARIAL.TTF",        // 当前目录大写
        "arial.ttf",        // 当前目录小写
        "./ARIAL.TTF",      // 当前目录大写（带路径）
        "./arial.ttf",      // 当前目录小写（带路径）
        "../ARIAL.TTF",     // 上一级目录大写
        "../arial.ttf",     // 上一级目录小写
        "fonts/ARIAL.TTF",  // fonts子目录大写
        "fonts/arial.ttf"   // fonts子目录小写
    };

    // 添加Windows系统字体路径
#ifdef _WIN32
    fontPaths.push_back("C:/Windows/Fonts/arial.ttf");
    fontPaths.push_back("C:/Windows/Fonts/ARIAL.TTF");
    fontPaths.push_back("C:/Windows/Fonts/times.ttf");  // 备用字体
    fontPaths.push_back("C:/Windows/Fonts/tahoma.ttf"); // 备用字体
#endif

    for (const auto& path : fontPaths) {
        if (font.openFromFile(path)) {
            std::cout << "成功加载字体: " << path << std::endl;
            font_ok = true;
            break;
        }
    }

    if (!font_ok) {
        std::cerr << "警告: 无法加载任何字体文件，文本可能不显示。" << std::endl;
        std::cerr << "请确保ARIAL.TTF或arial.ttf位于以下位置之一:" << std::endl;
        for (const auto& path : fontPaths) {
            std::cerr << "  - " << path << std::endl;
        }
        // 即使字体加载失败，程序仍可继续运行
    }

    setupUI();
}

void EICASGUI::run() {
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
        sf::sleep(sf::milliseconds(5));
    }
}

void EICASGUI::setupUI() {
    // 按钮
    start_button.setSize(sf::Vector2f(100.f, 50.f));
    start_button.setPosition(sf::Vector2f(50.f, 700.f));
    start_button.setFillColor(sf::Color::Green);

    stop_button.setSize(sf::Vector2f(100.f, 50.f));
    stop_button.setPosition(sf::Vector2f(200.f, 700.f));
    stop_button.setFillColor(sf::Color::Red);

    increase_thrust_button.setSize(sf::Vector2f(80.f, 40.f));
    increase_thrust_button.setPosition(sf::Vector2f(400.f, 700.f));
    increase_thrust_button.setFillColor(sf::Color::Blue);

    decrease_thrust_button.setSize(sf::Vector2f(80.f, 40.f));
    decrease_thrust_button.setPosition(sf::Vector2f(500.f, 700.f));
    decrease_thrust_button.setFillColor(sf::Color::Blue);

    // 状态框
    start_status_box.setSize(sf::Vector2f(80.f, 30.f));
    start_status_box.setPosition(sf::Vector2f(350.f, 100.f));
    start_status_box.setFillColor(sf::Color::Transparent);
    start_status_box.setOutlineColor(sf::Color::White);
    start_status_box.setOutlineThickness(2.f);

    run_status_box.setSize(sf::Vector2f(80.f, 30.f));
    run_status_box.setPosition(sf::Vector2f(450.f, 100.f));
    run_status_box.setFillColor(sf::Color::Transparent);
    run_status_box.setOutlineColor(sf::Color::White);
    run_status_box.setOutlineThickness(2.f);

    // 表盘
    N1_gauge.setRadius(150.f);
    N1_gauge.setPosition(sf::Vector2f(100.f, 200.f));
    N1_gauge.setFillColor(sf::Color::Transparent);
    N1_gauge.setOutlineColor(sf::Color::White);
    N1_gauge.setOutlineThickness(3.f);

    EGT_gauge.setRadius(150.f);
    EGT_gauge.setPosition(sf::Vector2f(600.f, 200.f));
    EGT_gauge.setFillColor(sf::Color::Transparent);
    EGT_gauge.setOutlineColor(sf::Color::White);
    EGT_gauge.setOutlineThickness(3.f);
}

void EICASGUI::handleEvents() {
    // SFML 3.0 事件处理
    while (auto event = window.pollEvent()) {
        // 处理关闭事件
        if (event->is<sf::Event::Closed>()) {
            window.close();
            continue;
        }

        // 处理鼠标按下事件
        if (auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
            sf::Vector2f mouse_pos = window.mapPixelToCoords(mouseEvent->position);

            if (start_button.getGlobalBounds().contains(mouse_pos)) {
                simulator.start();
            }
            else if (stop_button.getGlobalBounds().contains(mouse_pos)) {
                simulator.stop();
            }
            else if (increase_thrust_button.getGlobalBounds().contains(mouse_pos)) {
                simulator.increaseThrust();
            }
            else if (decrease_thrust_button.getGlobalBounds().contains(mouse_pos)) {
                simulator.decreaseThrust();
            }
        }
    }
}

void EICASGUI::update() {
    EngineData data = simulator.getCurrentData();
    EngineState state = simulator.getCurrentState();

    updateStatusBoxes(state);
    updateGauges(data);

    // 记录数据
    logger.recordData(data);

    // 处理并显示警报
    auto alerts = simulator.getActiveAlerts();
    for (auto a : alerts) {
        logger.logAlert(a, "Alert generated");
        addAlert(a, "Alert generated");
    }
}

void EICASGUI::updateStatusBoxes(EngineState state) {
    if (state == STARTING) {
        start_status_box.setFillColor(sf::Color::Green);
        run_status_box.setFillColor(sf::Color::Transparent);
    }
    else if (state == RUNNING) {
        start_status_box.setFillColor(sf::Color::Transparent);
        run_status_box.setFillColor(sf::Color::Green);

        EngineData data = simulator.getCurrentData();
        if (data.N1_percent < 95) {
            run_status_box.setFillColor(sf::Color::Transparent);
        }
    }
    else {
        start_status_box.setFillColor(sf::Color::Transparent);
        run_status_box.setFillColor(sf::Color::Transparent);
    }
}

void EICASGUI::updateGauges(const EngineData& data) {
    double N1_angle = (data.N1_percent / 125.0) * 210.0;
    double normalized_EGT = (data.EGT + 5) / (1200 + 5);
    double EGT_angle = normalized_EGT * 210.0;

    (void)N1_angle;
    (void)EGT_angle;
}

void EICASGUI::render() {
    window.clear(sf::Color(20, 20, 40));

    window.draw(N1_gauge);
    window.draw(EGT_gauge);

    window.draw(start_button);
    window.draw(stop_button);
    window.draw(increase_thrust_button);
    window.draw(decrease_thrust_button);

    window.draw(start_status_box);
    window.draw(run_status_box);

    drawText();
    drawAlerts();

    window.display();
}

void EICASGUI::drawText() {
    EngineData data = simulator.getCurrentData();

    try {
        // 检查字体是否已成功加载
        // 如果字体没有字符数据，可能是加载失败
        if (font.getInfo().family.empty()) {
            static bool font_warning_shown = false;
            if (!font_warning_shown) {
                std::cerr << "字体未正确加载，跳过文本绘制" << std::endl;
                font_warning_shown = true;
            }
            return;
        }

        // N1 显示 - 使用字体构造 sf::Text
        sf::Text N1_text(font, "N1: " + std::to_string(static_cast<int>(data.N1_percent)) + "%");
        N1_text.setCharacterSize(24);
        N1_text.setFillColor(getStatusColor(data.N1_sensor1.status));
        N1_text.setPosition(sf::Vector2f(100.f, 160.f));
        window.draw(N1_text);

        // EGT 显示 - 使用字体构造 sf::Text
        sf::Text EGT_text(font, "EGT: " + std::to_string(static_cast<int>(data.EGT)) + "°C");
        EGT_text.setCharacterSize(24);
        EGT_text.setFillColor(getStatusColor(data.EGT_sensor1.status));
        EGT_text.setPosition(sf::Vector2f(600.f, 160.f));
        window.draw(EGT_text);

        // 燃油流速显示 - 使用字体构造 sf::Text
        sf::Text fuel_text(font, "Fuel Flow: " + std::to_string(static_cast<int>(data.fuel_flow.value)));
        fuel_text.setCharacterSize(24);
        fuel_text.setFillColor(getStatusColor(data.fuel_flow.status));
        fuel_text.setPosition(sf::Vector2f(400.f, 400.f));
        window.draw(fuel_text);

        // 按钮文字 - 使用字体构造 sf::Text
        sf::Text start_text(font, "START");
        start_text.setCharacterSize(20);
        start_text.setPosition(sf::Vector2f(70.f, 715.f));
        window.draw(start_text);

        sf::Text stop_text(font, "STOP");
        stop_text.setCharacterSize(20);
        stop_text.setPosition(sf::Vector2f(220.f, 715.f));
        window.draw(stop_text);

        sf::Text inc_text(font, "+");
        inc_text.setCharacterSize(30);
        inc_text.setPosition(sf::Vector2f(425.f, 705.f));
        window.draw(inc_text);

        sf::Text dec_text(font, "-");
        dec_text.setCharacterSize(30);
        dec_text.setPosition(sf::Vector2f(525.f, 705.f));
        window.draw(dec_text);
    }
    catch (const std::exception& e) {
        static bool error_shown = false;
        if (!error_shown) {
            std::cerr << "文本渲染错误: " << e.what() << std::endl;
            error_shown = true;
        }
    }
}

void EICASGUI::drawAlerts() {
    float y_pos = 450.0f;

    // 清理过期警报（显示超过5秒）
    auto current_time = std::chrono::steady_clock::now();
    auto it = active_alerts.begin();
    while (it != active_alerts.end()) {
        float elapsed = std::chrono::duration_cast<std::chrono::duration<float>>(
            current_time - it->second
        ).count();
        if (elapsed > 5.0f) {
            it = active_alerts.erase(it);
        }
        else {
            ++it;
        }
    }

    // 检查字体是否已成功加载
    if (font.getInfo().family.empty()) {
        return; // 字体未加载，跳过警报绘制
    }

    for (const auto& alert_pair : active_alerts) {
        // 使用字体构造 sf::Text
        sf::Text alert_text(font, alertToStringLocal(alert_pair.first));
        alert_text.setCharacterSize(18);
        alert_text.setFillColor(sf::Color::Red);
        alert_text.setPosition(sf::Vector2f(800.f, y_pos));
        window.draw(alert_text);
        y_pos += 25.0f;
    }
}

sf::Color EICASGUI::getStatusColor(SensorStatus status) {
    switch (status) {
    case NORMAL: return normal_color;
    case WARNING: return warning_color;
    case ALARM: return alarm_color;
    case INVALID: return invalid_color;
    default: return normal_color;
    }
}

void EICASGUI::addAlert(AlertType alert, const std::string& message) {
    logger.logAlert(alert, message);
    active_alerts.emplace_back(alert, std::chrono::steady_clock::now());
}