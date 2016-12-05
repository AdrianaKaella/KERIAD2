cmake_minimum_required(VERSION 3.3)
project(CVPong)
set(APP_NAME CVPong)

# ===================== oF Directory =====================
set(OF_DIRECTORY $ENV{OF_HOME})

# ===================== Compiler Flags =====================
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
set(CMAKE_MODULE_PATH ${OF_DIRECTORY}/cmake)

# =========== OF addons (from addons.make) ==============
include(addons)

# =========== OF ==============
include(linux64)

# ===================== Project Source Files =====================

set(SOURCE_FILES
        ${ADDON_SOURCE_FILES}
	src/main.cpp
	src/ofApp.cpp

        src/Ball.cpp src/Ball.h)

# ============ Compile and Link ==================

add_executable(${APP_NAME} ${SOURCE_FILES})
add_dependencies(${APP_NAME} of_shared)
target_link_libraries(${APP_NAME} $<TARGET_FILE:of_shared>)
target_link_libraries(${APP_NAME} ${OF_CORE_LIBS})


set_target_properties(${APP_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
