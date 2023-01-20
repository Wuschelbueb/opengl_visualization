/* ---------------------------------------------------------------------
 * I took some of this code from https://github.com/JoeyDeVries/LearnOpenGL and
 * adapted a lot for my needs.
 * ----------------------------------------------------------------------
 */
#define STB_IMAGE_IMPLEMENTATION

// ImGui Headers
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "openglVisualization.hpp"
#include <nfd.hpp>

int main()
{
    // Load GLFW and Create a Window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    auto mWindow = glfwCreateWindow(mWidth, mHeight, "OpenGL", nullptr, nullptr);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    // Check for Valid Context
    if (mWindow == nullptr)
    {
        fprintf(stderr, "Failed to Create OpenGL Context");
        return EXIT_FAILURE;
    }

    // Create Context and Load OpenGL Functions
    glfwMakeContextCurrent(mWindow);
    glfwSetFramebufferSizeCallback(mWindow, framebuffer_size_callback);
    glfwSetCursorPosCallback(mWindow, mouse_callback);
    glfwSetMouseButtonCallback(mWindow, mouse_button);
    glfwSetScrollCallback(mWindow, scroll_callback);
    gladLoadGL();

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    glEnable(GL_DEPTH_TEST);

    fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));

    float scale = 1.0f, minScale = 0, maxScale = 4;
    int nbQuads = 0, upperThreshold = 0, originalNumberQuads = 0;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(mWindow, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // initialize NFD
    NFD::Guard nfdGuard;
    // auto-freeing memory
    NFD::UniquePath outPath;
    nfdfilteritem_t filterItem[1] = {{"Object file", "obj"}};

    Model ourModel;

    Shader ourShader("shader.vert", "shader.frag");
    ourShader.use();
    ourShader.setFloat("scale", 1.0f);
    ourShader.setVec3("objectColor", 0.5f, 0.5f, 0.5f);

    while (!glfwWindowShouldClose(mWindow))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        processInput(mWindow);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGuiIO &io = ImGui::GetIO();
        io.FontGlobalScale = 1.3f;
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Open File"))
                {
                    // show the dialog
                    nfdresult_t result = NFD::OpenDialog(outPath, filterItem, 1);
                    if (result == NFD_OKAY)
                    {
                        ourModel.loadNewModel(outPath.get(), ".");
                        nbQuads = ourModel.getNbQuads();
                        upperThreshold = nbQuads;
                        originalNumberQuads = nbQuads;
                        origin = ourModel.GetObjCenter();
                        cameraStartPosition = origin + glm::vec3(0.0f, 0.0f, 4.0f);
                        camera.Position = (cameraStartPosition);
                        showObject = true;
                    }
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
        ImGui::Begin("Description", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("Number of Quads:");
        ImGui::SliderInt(" ", &nbQuads, 2, upperThreshold);
        ImGui::Text("Scale:");
        ImGui::SliderFloat("Scaling", &scale, minScale, maxScale);
        ImGui::Text("Controls:");
        ImGui::BulletText("W - Move up");
        ImGui::BulletText("A - Move left");
        ImGui::BulletText("S - Move down");
        ImGui::BulletText("D - Move right");
        ImGui::BulletText("Q - Move backward");
        ImGui::BulletText("E - Move forward");
        ImGui::BulletText("Mouse Wheel - Zoom");
        ImGui::BulletText("Left Mouse - Rotate");
        ImGui::End();
        if (showObject)
        {
            // be sure to activate shader when setting uniforms/drawing objects
            ourShader.use();
            ourShader.setVec3("viewPos", camera.Position);
            // light properties
            ourShader.setVec3("light.direction", -0.2f, -1.0f, -0.3f);
            ourShader.setVec3("light.ambient", 1.0f, 1.0f, 1.0f);
            ourShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
            ourShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
            // material properties
            ourShader.setFloat("scale", scale);
            ourShader.setInt("elements", nbQuads);
            ourShader.setFloat("material.shininess", 32.0f);
            // rotation and translation of object
            glm::mat4 model = glm::mat4(1.0f);
            glm::mat4 translation1 = glm::translate(glm::mat4(1.0f), -origin);
            glm::mat4 pitchRot = glm::rotate(glm::mat4(1.0f), glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f));
            glm::mat4 yawRot = glm::rotate(glm::mat4(1.0f), glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));
            glm::mat4 rotation = pitchRot * yawRot;
            glm::mat4 translation2 = glm::translate(glm::mat4(1.0f), origin);
            // dont change order, this matters
            model = translation2 * rotation * translation1 * model;

            // pass projection matrix to shader (note that in this case it could change every frame)
            projection = glm::perspective(glm::radians(camera.Zoom), (float)mWidth / (float)mHeight, 0.1f, 100.0f);
            // camera/view transformation
            glm::mat4 view = camera.GetViewMatrix();

            unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
            unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");
            // pass them to the shaders (3 different ways)
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

            ourShader.setMat4("projection", projection);
            ourShader.setMat4("view", view);
            ourShader.setMat4("model", model);
            ourModel.Draw(ourShader);
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime * 2);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(DOWN, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime * 2);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // update viewport
    glViewport(0, 0, width, height);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

void mouse_callback(GLFWwindow *window, double mouseX, double mouseY)
{
    // call io to check if mouse is on top of imgui
    ImGuiIO &io = ImGui::GetIO();
    // Calculate the change in mouse position since the last frame
    float deltaX = mouseX - lastMouseX;
    float deltaY = lastMouseY - mouseY;
    const float sensitivity = 0.1f;

    // Update the mouse position for the next frame
    lastMouseX = mouseX;
    lastMouseY = mouseY;

    deltaX *= sensitivity;
    deltaY *= sensitivity;

    // Check if the left mouse button is pressed
    if (leftButtonPressed && !io.WantCaptureMouse)
    {
        // Update the pitch and yaw angles
        yaw += deltaX;
        pitch += deltaY;

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }
}

void mouse_button(GLFWwindow *window, int button, int action, int mods)
{

    ImGuiIO &io = ImGui::GetIO();
    // Check if the left mouse button was pressed
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        // Update the left button pressed flag
        if (action == GLFW_PRESS)
        {
            leftButtonPressed = true;
            io.AddMouseButtonEvent(button, leftButtonPressed);
        }
        else if (action == GLFW_RELEASE)
        {
            leftButtonPressed = false;
            io.AddMouseButtonEvent(button, leftButtonPressed);
        }
    }
}