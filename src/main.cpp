#include <iostream>
#include <opencv2/opencv.hpp>
#include <map>
#include <string>
#include <vector>
#include <memory>

// ImGui and backends
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#define GL_SILENCE_DEPRECATION

#include <GLFW/glfw3.h>
#include <tinyfiledialogs.h>
#include "core/Graph.h" // Include Graph header

// UI components
#include "ui/Canvas.h"
#include "ui/PropertiesPanel.h"
#include "core/Pin.h" // Include Pin header
#include "nodes/ImageNode.h"

int main()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        return -1;
    }

    // Set OpenGL version (macOS compatible)
    const char *glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required on macOS

    // Create window
    GLFWwindow *window = glfwCreateWindow(1280, 720, "NodeBasedImageEditor", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Set context
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    if (!ImGui_ImplGlfw_InitForOpenGL(window, true))
    {
        std::cerr << "ImGui_ImplGlfw_InitForOpenGL failed!" << std::endl;
        return -1;
    }

    if (!ImGui_ImplOpenGL3_Init(glsl_version))
    {
        std::cerr << "ImGui_ImplOpenGL3_Init failed with GLSL version: " << glsl_version << std::endl;
        return -1;
    }

    std::cout << "NodeBasedImageEditor started successfully!" << std::endl;

    // UI state
    static std::vector<std::shared_ptr<Node>> nodes;
    static std::shared_ptr<Node> selectedNode = nullptr;
    static Graph graph; // Initialize graph
    static PropertiesPanel propertiesPanel;

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Start new ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Canvas - left side, fixed position
        ImGui::SetNextWindowPos(ImVec2(0, 20), ImGuiCond_Once);
        ImGui::SetNextWindowSize(ImVec2(950, 700), ImGuiCond_Once);
        ImGui::Begin("Canvas", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

        // Draw floating "+" button in the top-left corner of the canvas
        ImVec2 buttonPos = ImGui::GetCursorScreenPos();
        if (ImGui::Button("+", ImVec2(30, 30)))
        {
            const char *filters[] = {"*.jpg", "*.png", "*.bmp", "*.jpeg"};
            const char *filePath = tinyfd_openFileDialog("Select Image", "", 4, filters, NULL, 0);
            if (filePath)
            {
                cv::Mat img = cv::imread(filePath, cv::IMREAD_UNCHANGED);
                if (!img.empty())
                {
                    GLuint texID;
                    glGenTextures(1, &texID);
                    glBindTexture(GL_TEXTURE_2D, texID);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                    GLenum inputColorFormat = img.channels() == 4 ? GL_BGRA : GL_BGR;

                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.cols, img.rows, 0, inputColorFormat, GL_UNSIGNED_BYTE, img.ptr());
                    glBindTexture(GL_TEXTURE_2D, 0);
                    auto imageNode = std::make_shared<ImageNode>(nodes.size() + 1, filePath, texID);
                    imageNode->setPosition(ImVec2(50, 50)); // default placement
                    graph.addNode(imageNode);               // Use graph to add node
                }
            }
        }

        for (auto &node : graph.getNodes()) // Use graph to get nodes
        {
            ImGui::PushID(node->getId());
            ImGui::BeginGroup();
            node->draw();

            if (ImGui::IsItemClicked())
            {
                selectedNode = node;
            }

            ImGui::EndGroup();
            ImGui::PopID();
        }
        ImGui::End();

        // Collapsible Properties Panel - right side
        static bool showProperties = true;
        ImGui::SetNextWindowPos(ImVec2(950, 20), ImGuiCond_Once);
        ImGui::SetNextWindowSize(ImVec2(330, 700), ImGuiCond_Once);
        ImGui::Begin("Properties", &showProperties, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);
        if (showProperties)
        {
            propertiesPanel.draw(selectedNode);
        }
        ImGui::End();

        // Render Output
        ImGui::Begin("Output");

        cv::Mat resultImage = graph.render();
        if (!resultImage.empty())
        {
            GLuint resultTex;
            glGenTextures(1, &resultTex);
            glBindTexture(GL_TEXTURE_2D, resultTex);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            GLenum format = resultImage.channels() == 4 ? GL_BGRA : GL_BGR;
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, resultImage.cols, resultImage.rows, 0, format, GL_UNSIGNED_BYTE, resultImage.ptr());
            glBindTexture(GL_TEXTURE_2D, 0);

            ImGui::Image((ImTextureID)(intptr_t)resultTex, ImVec2(300, 300));
        }

        ImGui::End();

        // Render UI
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    std::cout << "NodeBasedImageEditor exited cleanly!" << std::endl;
    return 0;
}