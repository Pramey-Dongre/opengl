#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include <fstream>
#include<string>
#include<sstream>
#include"Renderer.h"
#include"VertexBuffer.h"
#include"VertexBufferLayout.h"
#include"VertexArray.h"
#include"IndexBuffer.h"
#include"Shader.h"
#include"Texture.h"

#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include"imgui/imgui_impl_glfw_gl3.h"

#include"tests/TestClearColor.h"
#include"tests/TestTexture2D.h"
#include"tests/TestTriangle.h"
#include"tests/Test.h"
//extern "C" {
//    __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
//}
//void APIENTRY GLDebugMessageCallback(GLenum source,
//    GLenum type,
//    GLuint id,
//    GLenum severity,
//    GLsizei length,
//    const GLchar* message,
//    const void* userParam)
//{
//    std::cerr << "OpenGL Debug Message:\n";
//    std::cerr << "Source: " << source << "\n";
//    std::cerr << "Type: " << type << "\n";
//    std::cerr << "Severity: " << severity << "\n";
//    std::cerr << "Message: " << message << "\n\n";
//}

//struct ShaderProgramSource
//{
//    std::string VertexSource;
//    std::string FragmentSource;
//};
//static ShaderProgramSource ParseShader(const std::string& filepath)
//{
//    std::ifstream stream(filepath);
//    enum class ShaderType
//    {
//        None = -1,
//        Vertex = 0,
//        Fragment = 1
//    };
//    std::string line;
//    std::stringstream ss[2];
//    ShaderType type = ShaderType::None;
//    while (getline(stream, line))
//    {
//        if (line.find("#shader") != std::string::npos)
//        {
//            if (line.find("vertex") != std::string::npos)
//                type = ShaderType::Vertex;
//            else if(line.find("fragment") != std::string::npos)
//                type = ShaderType::Fragment;
//        }
//        else
//        {
//            ss[(int)type] << line << '\n';
//        }
//    }
//    stream.close();
//    return { ss[0].str(),ss[1].str()};
//}
//
//static unsigned int CompileShader(unsigned int type,const std::string& source)
//{
//    unsigned int id = glCreateShader(type);
//    const char* src = source.c_str();
//    glShaderSource(id, 1, &src, nullptr);
//    glCompileShader(id);
//
//    int result;
//    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
//    if (result == GL_FALSE)
//    {
//        int length;
//        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
//        char *message = (char *)malloc(length*sizeof(char));
//        glGetShaderInfoLog(id, length, &length, message);
//        std::cout << "Shader compiling failed" << std::endl;
//        std::cout << message << std::endl;
//        glDeleteShader(id);
//        return 0;
//    }
//    return id;
//}
//static unsigned int CreateShader(const std::string& vertexShader,const std::string& fragmentShader)
//{
//    unsigned int program = glCreateProgram();
//    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
//    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
//
//    glAttachShader(program, vs);
//    glAttachShader(program, fs);
//    glLinkProgram(program);
//    glValidateProgram(program);
//
//    glDeleteShader(vs);
//    glDeleteShader(fs);
//    return program;
//}
int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    // Request OpenGL 3.3 core profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    if (glewInit() != GLEW_OK)
        std::cout << "some error\n";
    //std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    //std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    //std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
    //Loop until the user closes the window
    //float positions[] = {
    //    0.0f, 0.0f,
    //    0.75f, 0.0f,
    //    0.375f, 0.6495f,
     
    //    0.0f, 0.0f,
    //    0.375f, 0.6495f,
    //   -0.375f, 0.6495f,

    //   0.0f, 0.0f,
    //  -0.375f, 0.6495f,
    //  -0.75f, 0.0f,

    //  0.0f, 0.0f,
    // -0.75f, 0.0f,
    // -0.375f, -0.6495f,

    // 0.0f, 0.0f,
    //-0.375f, -0.6495f,
    // 0.375f, -0.6495f,

    // 0.0f, 0.0f,
    // 0.375f, -0.6495f,
    // 0.75f, 0.0f,
    //};
    //GLCall(glEnable(GL_BLEND));
    //GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    {
        //float positions[] = {
        //    //   X(px)    Y(px)    U     V
        //      0.0f,   0.0f,  0.0f, 0.0f,  // vertex 0 (bottom-left)
        //    384.0f,   0.0f,  1.0f, 0.0f,  // vertex 1
        //    384.0f, 216.0f,  1.0f, 1.0f,  // vertex 2
        //      0.0f, 216.0f,  0.0f, 1.0f,  // vertex 3
        //    192.0f, 324.0f,  0.5f, 1.2f,  // vertex 4 (top middle)
        //    192.0f, -108.0f, 0.5f,-0.2f   // vertex 5 (bottom middle)
        //};

        //We can calculate uv, values by using formula
        //u = (x-MINx)/(MAXx-MINx)
        //v = (y-MINy)/(MAXy-MINy)
        //unsigned int indices[] = {
        //    0 , 1 , 2,
        //    2 , 3 , 0,
        //    2 , 3 , 4,
        //    0 , 1 , 5
        //};

 
        //VAO
        /*unsigned int vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);*/
        //VBO
        //unsigned int buffer;
        //GLCall(glGenBuffers(1, &buffer));
        //GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
        //GLCall(glBufferData(GL_ARRAY_BUFFER, 2*6*sizeof(float),positions,GL_STATIC_DRAW));
        //Vertex attributes
        //VertexArray va;
        //VertexBuffer vbo(positions, 6 * 4 * sizeof(float));

        //VertexBufferLayout layout;
        //layout.Push<float>(2);
        //layout.Push<float>(2);
        //va.AddBuffer(vbo,layout);

        //GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float),0));
        //GLCall(glEnableVertexAttribArray(0));

        //IBO or EBO
        //unsigned int ibo;
        //GLCall(glGenBuffers(1, &ibo));
        //GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
        //GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 12 * sizeof(unsigned int), indices, GL_STATIC_DRAW));
        //IndexBuffer ibo(indices, 12);
        //Done recording
        /*glBindVertexArray(0);*/
        //glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Dark grey background
        //glEnable(GL_DEBUG_OUTPUT);
        //glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); // Makes callback synchronous
        //glDebugMessageCallback(GLDebugMessageCallback, nullptr);

        //glm::mat4 proj = glm::ortho(-2.0f,2.0f,-1.5f,1.5f,-1.0f,1.0f);
        //glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);

        //glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

        //
        //for (int row = 0; row < 4; ++row)
        //{
        //    for (int col = 0; col < 4; ++col)
        //    {
        //        std::cout << proj[col][row] << "\t"; // glm is column-major
        //    }
        //    std::cout << "\n";
        //}

        //Shader shader("res/Basic.shader");
        //shader.Bind();
        //ShaderProgramSource source = ParseShader("res/Basic.shader");
        //unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
        //GLCall(glUseProgram(shader));

        //shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
        
        //int location = glGetUniformLocation(shader, "u_Color");
        //ASSERT(location != -1);
        //GLCall(glUniform4f(location, 0.8f, 0.3f, 0.8f, 1.0f));

        //Texture texture("res/textures/porsche.png");
        //texture.Bind();
        //shader.SetUniform1i("u_Texture",0);
        //va.Unbind();
        //vbo.Unbind();
        //ibo.Unbind();
        //shader.Unbind();
        //GLCall(glUseProgram(0));
        //GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
        //GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

        Renderer renderer;

        ImGui::CreateContext();
        ImGui_ImplGlfwGL3_Init(window, true);
        ImGui::StyleColorsDark();

        test::Test* currentTest = nullptr;
        test::TestMenu* testMenu = new test::TestMenu(currentTest);
        currentTest = testMenu;

        testMenu->RegisterTest<test::TestClearColor>("Clear Color");
        testMenu->RegisterTest<test::TestTexture2D>("Texture 2D");
        testMenu->RegisterTest<test::TestTriangle>("Traingle");

        //test::TestClearColor test;


        //float r = 0.0f;
        //float increment = 0.05f;
        //glm::vec3 translationA = glm::vec3(100, 0, 0);
        //glm::vec3 translationB = glm::vec3(200, 0, 0);
        //glm::vec4 myColors = glm::vec4(0.0f, 0.0f, 0.0f,1.0f);

        while (!glfwWindowShouldClose(window))
        {
            GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
            /* Render here */
            renderer.Clear();
            //GLCall(glClear(GL_COLOR_BUFFER_BIT));
            
            //test.OnUpdate(0.0f);
            //test.OnRender();
            // Start the Dear ImGui frame
            ImGui_ImplGlfwGL3_NewFrame();

            if (currentTest)
            {
                currentTest->OnUpdate(0.0f);
                currentTest->OnRender();
                ImGui::Begin("Test");
                if (currentTest != testMenu && ImGui::Button("<-"))
                {
                    delete currentTest;
                    currentTest = testMenu;
                }
                currentTest->OnImGuiRender();
                ImGui::End();
            }
            //test.OnImGuiRender();
            //ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::Render();
            ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
            /* Swap front and back buffers */
            GLCall(glfwSwapBuffers(window));

            /* Poll for and process events */
            GLCall(glfwPollEvents());
            //glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
            //glm::mat4 mvp = proj * view * model;

            //shader.Bind();
            //shader.SetUniform4f("u_Color", myColors.x,myColors.y,myColors.z,myColors.w);
            //shader.SetUniformMat4f("u_MVP", mvp);
            //shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
           /* GLCall(glUseProgram(shader));
            GLCall(glUniform4f(location, r, 0.3f, 0.8f, 1.0f));*/

            /*GLCall(glBindVertexArray(vao));*/
            /*va.Bind();
            ibo.Bind();*/
            //renderer.Draw(va, ibo, shader);

            //model = glm::translate(glm::mat4(1.0f), translationB);
            //mvp = proj * view * model;
            //shader.SetUniformMat4f("u_MVP", mvp);
            //renderer.Draw(va, ibo, shader);

            //GLCall(glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, nullptr));
            //if (r > 1.0f)
            //    increment = -0.05f;
            //else if (r < 0.0f)
            //    increment = 0.05f;
            //r += increment;
            {

                //ImGui::SliderFloat3("TranslationA", &translationA.x, 0.0f, 960.0f);          // Edit 1 float using a slider from 0.0f to 1.0f
                //ImGui::SliderFloat3("TranslationB", &translationB.x, 0.0f, 960.0f);          // Edit 1 float using a slider from 0.0f to 1.0f
                //ImGui::SliderFloat4("Color", &myColors.x, 0.0f, 1.0f);
                //ImGui::ColorEdit4("Color", &myColors.x);
                //ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            }
            //glBegin(GL_TRIANGLES);
            //glColor3f(1.0f, 0.0f, 0.0f); // Set color to red
            //glVertex2f(-0.5f, -0.5f);
            //glVertex2f(-0.5f, 0.5f);
            //glVertex2f(0.5f, 0.5f );
            //glEnd();

        }
        delete currentTest;
        if (currentTest != testMenu)
            delete testMenu;
    }
    
    // Cleanup
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}