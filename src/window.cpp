#include "window.h"

window::window() {
    init();
}

window::~window() = default;

void window::eprintf(int error, const char *description) {
    std::cout << "Error: " << error << " " << description << "\n";
}

void window::init() {
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << "\n";
        return;
    }

    glfwSetErrorCallback(eprintf);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

    w = constants::WINDOW_WIDTH;
    h = constants::WINDOW_HEIGHT;

    win = glfwCreateWindow(w, h, "drinkKahvi", nullptr, nullptr);
    if (!win) {
        std::cout << "Failed to create GLFW window" << "\n";
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(win);
    glfwSwapInterval(1);

    ImGui::CreateContext();

    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_DockingEnable;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(this->win, true);
    ImGui_ImplOpenGL3_Init("#version 450");

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << "\n";
        return;
    }
}

void window::update() {
    glfwPollEvents();
    new_frame();
    position_window_at_top();
    popup_flags popups{};
    ImGui::Begin("drinkKahvi", nullptr,
                 ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_MenuBar);
    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("Settings")) {
            if (ImGui::MenuItem("KahviBreak directory")) {
                popups.kahvi_dir_popup = true;
            }
            if (ImGui::BeginMenu("Theme")) {
                if (ImGui::MenuItem("Dark")) {
                    ImGui::StyleColorsDark();
                }
                if (ImGui::MenuItem("Light")) {
                    ImGui::StyleColorsLight();
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }
        if (ImGui::MenuItem("About")) {
            popups.about_popup = true;
        }
        if (ImGui::MenuItem("Exit")) {
            glfwSetWindowShouldClose(win, true);
        }
        ImGui::EndMenuBar();
    }
    ImGui::End();
    if (popups.about_popup) {
        ImGui::OpenPopup("About");
    }
    components::about_popup_handle();
    if (popups.kahvi_dir_popup) {
        ImGui::OpenPopup("KahviBreak directory");
    }
    components::directory_modal_handle();
    memset(&popups, 0, sizeof(popups));
    ImGui::ShowDemoWindow();
}

void window::render() {
    ImGui::Render();
    glfwGetFramebufferSize(win, &w, &h);
    glViewport(0, 0, w, h);
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

void window::position_window_at_top() const {
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(static_cast<float>(w), static_cast<float>(h)));
}
