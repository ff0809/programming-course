#include "EngineSimulator.h"
#include <cmath>
#include <cstdlib>

using namespace std::chrono;

EngineSimulator::EngineSimulator() {
    state = EngineState::SHUTDOWN;
    stateTime = steady_clock::now();
}

void EngineSimulator::start() {
    state = EngineState::STARTING_PHASE1;
    stateTime = steady_clock::now();
}

void EngineSimulator::shutdown() {
    state = EngineState::SHUTTING_DOWN;
    stateTime = steady_clock::now();
}

void EngineSimulator::update() {
    updateState();
    genN1();
    genEGT();
    genFuel();
}

EngineData EngineSimulator::getData() const {
    return data;
}

void EngineSimulator::updateState() {
    double t = duration_cast<milliseconds>(
        steady_clock::now() - stateTime).count() / 1000.0;

    if (state == EngineState::STARTING_PHASE1 && t >= 2.0) {
        state = EngineState::STARTING_PHASE2;
        stateTime = steady_clock::now();
    }
    else if (state == EngineState::STARTING_PHASE2 && data.n1_avg >= 95.0) {
        state = EngineState::RUNNING;
    }

    data.state = state;
}

void EngineSimulator::genN1() {
    double t = duration_cast<milliseconds>(
        steady_clock::now() - stateTime).count() / 1000.0;

    double n1 = 0;

    if (state == EngineState::STARTING_PHASE1)
        n1 = 25.0 * t;
    else if (state == EngineState::STARTING_PHASE2) {
        double N = 23000 * log10(t + 1.0) + 20000;
        n1 = (N / 40000.0) * 100.0;
    }
    else if (state == EngineState::RUNNING)
        n1 = 95 + (rand() % 7 - 3);
    else if (state == EngineState::SHUTTING_DOWN)
        n1 = data.n1_avg * pow(0.1, t / 10.0);

    data.n1_1 = n1 + (rand() % 10 - 5) * 0.1;
    data.n1_2 = n1 + (rand() % 10 - 5) * 0.1;
    data.n1_avg = (data.n1_1 + data.n1_2) / 2;
}

void EngineSimulator::genEGT() {
    data.egt_1 = 300 + data.n1_avg * 4;
    data.egt_2 = data.egt_1 + (rand() % 5);
    data.egt_avg = (data.egt_1 + data.egt_2) / 2;
}

void EngineSimulator::genFuel() {
    if (state == EngineState::RUNNING) {
        data.fuelFlow = 0.8;
        data.fuelLevel -= data.fuelFlow * 0.005;
    }
    else data.fuelFlow = 0;
}
