#include"TestTexture2D.h"
#include"Renderer.h"
#include"imgui/imgui.h"
#include"VertexArray.h"
#include"VertexBufferLayout.h"
#include"IndexBuffer.h"
#include"Shader.h"
#include"Texture.h"

namespace test
{
	TestTexture2D::TestTexture2D()
		:m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
		m_TranslationA(200, 200, 0), m_TranslationB(400, 200, 0)
	{
		float positions[] = {
	       //   X(px)    Y(px)    U     V
	         0.0f,   0.0f,  0.0f, 0.0f,  // vertex 0 (bottom-left)
	       384.0f,   0.0f,  1.0f, 0.0f,  // vertex 1
	       384.0f, 216.0f,  1.0f, 1.0f,  // vertex 2
	         0.0f, 216.0f,  0.0f, 1.0f,  // vertex 3
	       192.0f, 324.0f,  0.5f, 1.2f,  // vertex 4 (top middle)
	       192.0f, -108.0f, 0.5f,-0.2f   // vertex 5 (bottom middle)
	   };

	   //We can calculate uv, values by using formula
	   //u = (x-MINx)/(MAXx-MINx)
	   //v = (y-MINy)/(MAXy-MINy)
	   unsigned int indices[] = {
	       0 , 1 , 2,
	       2 , 3 , 0,
	       2 , 3 , 4,
	       0 , 1 , 5
	   };

	    GLCall(glEnable(GL_BLEND));
	    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		m_VAO = std::make_unique<VertexArray>();
	  
	    //VertexBuffer vbo(positions, 6 * 4 * sizeof(float));
		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 6 * 4 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);

		m_VAO->AddBuffer(*m_VertexBuffer,layout);
		m_IndexBuffer = std::make_unique<IndexBuffer>(indices,12);

		m_Shader = std::make_unique<Shader>("res/Basic.shader");
		m_Shader->Bind();
		m_Shader->SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

		m_Texture = std::make_unique<Texture>("res/textures/porsche.png");
		
		m_Shader->SetUniform1i("u_Texture",0);
	}
	TestTexture2D::~TestTexture2D()
	{
	}
	void TestTexture2D::OnUpdate(float deltaTime)
	{
	}
	void TestTexture2D::OnRender()
	{
		GLCall(glClearColor(0.0f,0.0f,0.0f,1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		Renderer renderer;
		m_Texture->Bind();

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
			glm::mat4 mvp = m_Proj * m_View * model;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);

			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
			glm::mat4 mvp = m_Proj * m_View * model;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);

			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}

		//shader.Bind();
	}
	void TestTexture2D::OnImGuiRender()
	{
		ImGui::SliderFloat3("TranslationA", &m_TranslationA.x, 0.0f, 960.0f);          // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::SliderFloat3("TranslationB", &m_TranslationB.x, 0.0f, 960.0f);          // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}