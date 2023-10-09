#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include "backend.h"
#include <future>
#include "save&load.h"
#include <bitset>
#include "loadImage.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <glfw3.h> // Will drag system OpenGL headers
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

// This example can also compile and run with Emscripten! See 'Makefile.emscripten' for details.
#ifdef __EMSCRIPTEN__
#include "../libs/emscripten/emscripten_mainloop_stub.h"
#endif

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

// Main code
int main(int, char**)

    
{
    

    
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif


    GLFWwindow* window = glfwCreateWindow(1000, 300, "Shiny Tracker", nullptr, nullptr);

    if (window == nullptr)
        return 1;
    glfwMakeContextCurrent(window);
    int width, height ,channels;
    unsigned char* icon = stbi_load("icon.png", &width, &height, &channels, 4);
    GLFWimage images[1];
    images[0].width = width;
    images[0].height = height;
    images[0].pixels = icon;
    glfwSetWindowIcon(window, 1, images);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 3.5f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        
    }

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    io.Fonts->AddFontFromFileTTF("fonts\\Exo2.ttf", 15.0f);

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.22f, 0.22f, 0.37f, 1.00f);
    bool oldOdds = true;
    bool newOdds = false;
    bool shinyCharm = false;
    int pokemonSeen = 0;
    double odds = 0.00012207031;
    double binomialResult = 0;
    GLuint my_image_texture;
    
    bool ret = LoadTextureFromFile("icons//github.png", &my_image_texture, NULL, NULL);
    


    // Main loop
#ifdef __EMSCRIPTEN__
    io.IniFilename = nullptr;
    EMSCRIPTEN_MAINLOOP_BEGIN
#else


    
    while (!glfwWindowShouldClose(window))
#endif
    {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //My code
        
        ImGui::Begin("Counter");
        ImGui::SetCursorPos(ImVec2(405, 35));
        ImGui::Text("Pokemon Seen");
        ImGui::SetCursorPos(ImVec2(160, 55));
        if (ImGui::DragInt(" ", &pokemonSeen, 50)) {
            std::async(std::launch::async, binomialDistribution, pokemonSeen, odds, std::ref(binomialResult));
        }
        ImGui::SetCursorPos(ImVec2(413, 80));
        if (ImGui::Button(("+"),ImVec2(30,30))) {
            pokemonSeen++;            
            std::async(std::launch::async, binomialDistribution, pokemonSeen, odds, std::ref(binomialResult));
        }
        ImGui::SetCursorPos(ImVec2(453, 80));
        if (ImGui::Button(("-"), ImVec2(30, 30))) {
            pokemonSeen--;
            std::async(std::launch::async, binomialDistribution, pokemonSeen, odds, std::ref(binomialResult));
        }
        ImGui::SetCursorPos(ImVec2(800, 80));
        if (ImGui::ImageButton((void*)(intptr_t)my_image_texture, ImVec2(60, 35))) {
            system("start https://github.com/Denellyne");
        }
        ImGui::End();

        ImGui::Begin("Options");
        if (ImGui::Checkbox("Shiny Charm", &shinyCharm)) {
            std::async(std::launch::async, oddsCalculator, oldOdds, shinyCharm, std::ref(odds));
        }

        if (ImGui::Checkbox("Old Odds", &oldOdds)) {
            newOdds = false;
            std::async(std::launch::async, oddsCalculator, oldOdds, shinyCharm, std::ref(odds));
        }
        if (ImGui::Checkbox("New Odds", &newOdds))
        {
            oldOdds = false;
            std::async(std::launch::async, oddsCalculator, oldOdds, shinyCharm, std::ref(odds));
        }
        ImGui::End();
        ImGui::Begin("Info");
        ImGui::Text("Pokemon Seen: %d", pokemonSeen);
        ImGui::Text("Probability of already have found a shiny: %f%%", binomialResult);
        ImGui::Text("Press the Delete key to add 1 to the counter");
        ImGui::Text("Press the End key to subtract 1 from the counter");
        ImGui::End();
        if (ImGui::IsKeyPressed(ImGuiKey_Delete)) {
            pokemonSeen++;
            std::async(std::launch::async, binomialDistribution, pokemonSeen, odds, std::ref(binomialResult));
        }
        if (ImGui::IsKeyPressed(ImGuiKey_End)) {
            pokemonSeen--;
            std::async(std::launch::async, binomialDistribution, pokemonSeen, odds, std::ref(binomialResult));
        }

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        glfwSwapBuffers(window);
    }
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_MAINLOOP_END;
#endif

    //SaveLoad::saveData(oldOdds,shinyCharm,pokemonSeen,odds,binomialResult);

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
