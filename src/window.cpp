#include "window.h"

window::window() {
    init();
}

window::~window() = default;

void window::eprintf(int error, const char *description) {
    std::cout << "Error: " << error << " " << description << std::endl;
}


void window::init() {
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return;
    }

    glfwSetErrorCallback(eprintf);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    w = constants::WINDOW_WIDTH;
    h = constants::WINDOW_HEIGHT;

    win = glfwCreateWindow(w, h, "drinkKahvi", nullptr, nullptr);
    if (!win) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(win);
    glfwSwapInterval(1);

    ImGui::CreateContext();

    ImGuiIO &io = ImGui::GetIO();

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(this->win, true);
    ImGui_ImplOpenGL3_Init("#version 450");

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }
}

void window::update() {
    glfwPollEvents();
    new_frame();
    ImGui::ShowDemoWindow();
}

void window::render() {
    glfwGetFramebufferSize(win, &w, &h);
    glViewport(0, 0, w, h);
    ImGui::Render();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(win);
}

void window::destroy() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(win);
    glfwTerminate();
}

GLFWwindow *window::getWin() const {
    return win;
}

void window::new_frame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}