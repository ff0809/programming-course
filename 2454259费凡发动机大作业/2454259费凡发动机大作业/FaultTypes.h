#pragma once

#include <string>
#include <chrono>
#include <map>

    enum class FaultType {
    NONE = 0,                        
    SINGLE_N1_SENSOR_FAULT = 1,        
    ENGINE_N1_SENSOR_FAULT = 2,      
    SINGLE_EGT_SENSOR_FAULT = 3,      
    ENGINE_EGT_SENSOR_FAULT = 4,      
    DUAL_SENSOR_FAULT = 5,            
    FUEL_LOW = 6,                     
    FUEL_SENSOR_FAULT = 7,          
    FUEL_FLOW_HIGH = 8,              
    N1_OVER_105 = 9,                   
    N1_OVER_120 = 10,                 
    EGT_START_OVER_850 = 11,           
    EGT_START_OVER_1000 = 12,         
    EGT_STABLE_OVER_950 = 13,          
    EGT_STABLE_OVER_1100 = 14       
};

enum class FaultLevel {
    NORMAL = 0,      
    CAUTION = 1,     
    WARNING = 2,     
    INVALID = 3     
};

struct AlertMessage {
    FaultType type;
    FaultLevel level;
    std::string text;
    std::chrono::steady_clock::time_point startTime;
    bool logged;

    AlertMessage() : type(FaultType::NONE), level(FaultLevel::NORMAL), logged(false) {}
    AlertMessage(FaultType t, FaultLevel l, const std::string& txt)
        : type(t), level(l), text(txt), startTime(std::chrono::steady_clock::now()), logged(false) {
    }
};

struct SensorFaultFlags {
    bool leftN1Fault = false;
    bool leftEGTFault = false;
    bool rightN1Fault = false;
    bool rightEGTFault = false;
    bool fuelSensorFault = false;

    bool anyN1Fault() const { return leftN1Fault || rightN1Fault; }
    bool anyEGTFault() const { return leftEGTFault || rightEGTFault; }
    bool dualFault() const {
        return (leftN1Fault && rightN1Fault) ||
            (leftEGTFault && rightEGTFault) ||
            (leftN1Fault && leftEGTFault) ||
            (rightN1Fault && rightEGTFault);
    }

    void clear() {
        leftN1Fault = false;
        leftEGTFault = false;
        rightN1Fault = false;
        rightEGTFault = false;
        fuelSensorFault = false;
    }
};