#include <iostream>

#include "window.h"

int main() {
    window mainWindow;
    while(!glfwWindowShouldClose(mainWindow.getWin())) {
        mainWindow.update();
        mainWindow.render();
    }
    mainWindow.destroy();
}
