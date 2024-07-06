#include "app.h"

App::App()
{
    setup_glfw();
    setup_opengl();
    setup_imgui();
}

void App::setup_glfw()
{
    if (!glfwInit())
    {
        std::cout << "Error initializing GLFW" << std::endl;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    window = glfwCreateWindow(2200, 1300, "Medical Vision 3D", NULL, NULL);
    if (!window)
    {
        std::cout << "Error creating GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Error initializing Glad" << std::endl;
        glfwTerminate();
    }
}

void App::setup_opengl()
{
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void App::setup_imgui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::StyleColorsDark();
}

void App::run()
{
    Factory factory;
    factory.create_cube();

    // Projection Matrix
    glm::vec3 translationA(0.0f, 0.0f, 0.0f);
    glm::vec3 eulersA(45.0f, 45.0f, 45.0f);
    glm::mat4 projection_matrix = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
    glm::mat4 view_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

    // Abstraction
    Shader shader("../resources/glsl/vertex.vert", "../resources/glsl/fragment.frag");
    shader.Bind();
    Texture texture("../resources/textures/red.jpg");
    texture.Bind();
    Display display;

    // Shader Uniform
    shader.SetUniform1i("ImageTexture", 0);

    // imgui config
    bool show_imgui = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Clear all
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    while (!glfwWindowShouldClose(window))
    {
        // Clear Screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        display.Clear();

        // Start rendering
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, translationA);
            model = glm::rotate(model, glm::radians(eulersA.x), {1.0f, 0.0f, 0.0f});
            model = glm::rotate(model, glm::radians(eulersA.y), {0.0f, 1.0f, 0.0f});
            model = glm::rotate(model, glm::radians(eulersA.z), {0.0f, 0.0f, 1.0f});
            shader.Bind();
            glm::mat4 mvp = projection_matrix * view_matrix * model;
            shader.SetUniformMatrix4fv("mvp", mvp);
            factory.draw();
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (show_imgui)
            ImGui::ShowDemoWindow(&show_imgui);
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Neuro 3D Vision");

            ImGui::Text("This is some useful text.");
            ImGui::Checkbox("Demo Window", &show_imgui);
            ImGui::Checkbox("Another Window", &show_imgui);

            ImGui::SliderFloat3("Translation A", &translationA.x, -1.0f, 1.0f);
            ImGui::SliderFloat3("Rotation A", &eulersA.x, 0.0f, 360.f);
            ImGui::ColorEdit3("clear color", (float *)&clear_color);

            if (ImGui::Button("Button"))
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

App::~App()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}