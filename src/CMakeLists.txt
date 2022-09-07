add_executable(drinkKahvi drinkKahvi.cpp include/constants.h include/window.h constants.cpp window.cpp )

include_directories(${PROJECT_SOURCE_DIR}/src/include)

target_include_directories(drinkKahvi PUBLIC ${PROJECT_SOURCE_DIR}/src/include)

link_libraries(imgui::imgui glad::glad glfw)

find_package(imgui CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

if (imgui_FOUND AND glfw3_FOUND AND glad_FOUND)
    message(STATUS "imgui, glfw3 and glad found")
endif()

add_library(window STATIC window.cpp)
add_library(constants STATIC constants.cpp)

target_link_libraries(drinkKahvi PRIVATE window constants glad::glad glfw imgui::imgui)