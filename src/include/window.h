#ifndef DRINKKAHVI_WINDOW_H
#define DRINKKAHVI_WINDOW_H

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iostream>

#include "constants.h"
#include "components.h"

class window {
private:
    int w{}, h{};

    GLFWwindow *win{};

    static void new_frame();

    void position_window_at_top() const;

    static void eprintf(int error, const char* description);
public:
    window();

    ~window();

    void init();

    virtual void update();

    void render();

    void destroy();

    [[nodiscard]] GLFWwindow *getWin() const;
};

#endif //DRINKKAHVI_WINDOW_H