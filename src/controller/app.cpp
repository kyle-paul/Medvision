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
    // Buffer
    float l = 0.5f;
    float w = 0.5f;
    float h = 0.5f;

    std::vector<float> positions = {
        l, w, -h,
        l, -w, -h,
        -l, -w, -h,
        -l, w, -h,
        -l, -w, h,
        l, -w, h,
        l, w, h,
        -l, w, h};

    std::vector<float> normals = {
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f};

    std::vector<float> texCoords = {
        0.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 0.0f,

        0.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 0.0f};

    std::vector<unsigned int> faces = {
        0, 1, 3,
        1, 2, 3,
        4, 5, 7,
        5, 6, 7,
        3, 2, 7,
        2, 4, 7,
        0, 1, 6,
        0, 6, 5,
        1, 2, 5,
        2, 4, 5,
        0, 3, 7,
        0, 7, 6};

    VertexArray vao;
    VertexBuffer vbo(positions);
    VertexBuffer nbo(normals);
    VertexBuffer tbo(texCoords);
    IndexBuffer fbo(faces);

    VertexBufferLayout positions_layout;
    VertexBufferLayout normals_layout;
    VertexBufferLayout texCoord_layout;

    positions_layout.AddFloat(3);
    normals_layout.AddFloat(3);
    texCoord_layout.AddFloat(2);

    vao.receiveBuffer(0, vbo, positions_layout);
    vao.receiveBuffer(1, nbo, normals_layout);
    vao.receiveBuffer(2, tbo, texCoord_layout);

    // Projection Matrix
    glm::vec3 translation(0.0f, 0.0f, 0.0f);
    glm::vec3 eulers(45.0f, 45.0f, 45.0f);
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

        // Start rendering
        shader.Bind();
        display.Clear();
        display.Draw(vao, fbo, shader);

        // adjust mvp shader
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, translation);
        model = glm::rotate(model, glm::radians(eulers.x), {1.0f, 0.0f, 0.0f});
        model = glm::rotate(model, glm::radians(eulers.y), {0.0f, 1.0f, 0.0f});
        model = glm::rotate(model, glm::radians(eulers.z), {0.0f, 0.0f, 1.0f});
        glm::mat4 mvp = projection_matrix * view_matrix * model;
        shader.SetUniformMatrix4fv("mvp", mvp);

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

            ImGui::SliderFloat3("X Translation", &translation.x, 0.0f, 1.0f);
            ImGui::SliderFloat3("Rotation", &eulers.x, 0.0f, 360.f);
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