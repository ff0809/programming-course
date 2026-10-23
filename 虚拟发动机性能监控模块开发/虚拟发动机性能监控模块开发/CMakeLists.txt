cmake_minimum_required(VERSION 3.16)
project(VirtualEngineMonitor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SFML 3.0.2 路径配置 (手动配置，避免 find_package 崩溃问题)
set(SFML_ROOT "${CMAKE_SOURCE_DIR}/SFML-3.0.2")
set(SFML_INCLUDE_DIR "${SFML_ROOT}/include")
set(SFML_LIB_DIR "${SFML_ROOT}/lib")
set(SFML_BIN_DIR "${SFML_ROOT}/bin")

# 源文件
set(SOURCES
    src/main.cpp
    src/EngineModel.cpp
    src/FuelSystem.cpp
    src/Gauge.cpp
    src/IndicatorPanel.cpp
    src/ControlPanel.cpp
    src/DataLogger.cpp
    src/AppController.cpp
)

# 头文件
set(HEADERS
    include/EngineModel.h
    include/FuelSystem.h
    include/Gauge.h
    include/IndicatorPanel.h
    include/ControlPanel.h
    include/DataLogger.h
    include/AppController.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${SFML_INCLUDE_DIR}
)

# 根据构建类型选择库
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(SFML_SUFFIX "-d")
else()
    set(SFML_SUFFIX "")
endif()

# 手动链接 SFML 库
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${SFML_LIB_DIR}/sfml-graphics${SFML_SUFFIX}.lib
    ${SFML_LIB_DIR}/sfml-window${SFML_SUFFIX}.lib
    ${SFML_LIB_DIR}/sfml-system${SFML_SUFFIX}.lib
    opengl32
)

# 复制 SFML DLL 到输出目录 (Windows)
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${SFML_BIN_DIR}"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()

# 复制资源文件
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/resources"
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
)
