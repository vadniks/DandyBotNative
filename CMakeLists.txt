
cmake_minimum_required(VERSION 3.20)
project(MultiDandyBotNative)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

file(GLOB sources CONFIGURE_DEPENDS "src/*.hpp" "src/*.cpp" "src/*/*.hpp" "src/*/*.cpp")
add_executable(${PROJECT_NAME} ${sources})

find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)
target_link_libraries(MultiDandyBotNative Qt::Core Qt::Gui Qt::Widgets)

find_package(Boost 1.40 COMPONENTS program_options REQUIRED)
target_link_libraries(${PROJECT_NAME} Boost::program_options)
