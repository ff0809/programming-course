// main.cpp
#include "EngineSimulator.h"
#include "EICASGUI.h"
#include "DataLogger.h"
#include <iostream>
#include <exception>

int main() {
    try {
        std::cout << "Starting Virtual Engine EICAS System..." << std::endl;

        // 初始化组件
        EngineSimulator simulator;
        DataLogger logger;
        EICASGUI gui(simulator, logger);

        std::cout << "System initialized successfully." << std::endl;
        std::cout << "Press START to begin engine simulation." << std::endl;

        // 运行主循环
        gui.run();

        std::cout << "System shutdown completed." << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << "FATAL ERROR: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Unknown fatal error occurred!" << std::endl;
        return 1;
    }

    return 0;
}