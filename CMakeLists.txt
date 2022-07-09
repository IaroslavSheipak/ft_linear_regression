set(CMAKE_CXX_COMPILER /usr/bin/clang++)
cmake_minimum_required(VERSION 3.15)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
project(ft_linear_regression LANGUAGES CXX)
execute_process(COMMAND pip3 install numpy)
execute_process(COMMAND pip3 install matplotlib)
find_package(Python3 COMPONENTS Interpreter Development NumPy REQUIRED)
find_package(PythonLibs 3.0 REQUIRED)
include_directories(${PYTHON3_INCLUDE_DIRS} ${NumPy_INCLUDE_DIRS})

# populate matplotlib repository
include(FetchContent)
FetchContent_Declare(
    matplotlib
    GIT_REPOSITORY https://github.com/lava/matplotlib-cpp.git
    GIT_TAG        f23347fca25219d1c42cbb91608b5556814bf572
)
FetchContent_GetProperties(matplotlib)
if(NOT matplotlib_POPULATED)
    FetchContent_Populate(matplotlib)
endif()
add_executable(train  LinearRegression.cpp main_train.cpp)
target_link_libraries(train
    PRIVATE
        ${PYTHON_LIBRARIES}
        Python3::NumPy
)
add_executable(predict LinearRegression.cpp main_predict.cpp)

target_link_libraries(predict
    PRIVATE
        ${PYTHON_LIBRARIES}
        Python3::NumPy
)




find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

include_directories(SYSTEM ${matplotlib_SOURCE_DIR})
include_directories(SYSTEM ${matplotlib_SOURCE_DIR})
