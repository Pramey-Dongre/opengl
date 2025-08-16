#include"TestTriangle.h"
#include"Renderer.h"
#include"imgui/imgui.h"
namespace test
{
	TestTriangle::TestTriangle()
		:m_Positions{ 100.0f, 100.0f,   // bottom-left  
	300.0f, 100.0f,   // bottom-right  
	200.0f, 300.0f },
		m_Indices{0,1,2}, m_Color{ 0.8f, 0.3f, 0.8f, 1.0f },
		m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
		m_View(glm::mat4(1.0f)),
		m_Translation(200.0f, 200.0f, 0.0f),
		m_Scale(1.0f),
		m_Rotation(1.0f)
	{
		std::cout << "Initial Projection Matrix" << std::endl;
		PrintMatrix(m_Proj);
		m_VAO = std::make_unique<VertexArray>();

		m_VertexBuffer = std::make_unique<VertexBuffer>(m_Positions, 6 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(2);

		m_VAO->AddBuffer(*m_VertexBuffer, layout);

		m_IndexBuffer = std::make_unique<IndexBuffer>(m_Indices, 3);

		m_Shader = std::make_unique<Shader>("res/Triangle.shader");
	}

	TestTriangle::~TestTriangle()
	{
	}
	void TestTriangle::OnUpdate(float deltaTime)
	{
	}
	void TestTriangle::OnRender()
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
		Renderer renderer;

		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation);
		//std::cout << "Initial Model Matrix" << std::endl;
		//PrintMatrix(model);
		model = glm::scale(model, glm::vec3(m_Scale, m_Scale, 1.0f));
		//std::cout << "Initial Scale Matrix" << std::endl;
		//PrintMatrix(model);
		model = glm::rotate(model, m_Rotation, glm::vec3(0, 0, 1));
		//std::cout << "Initial Rotation Matrix" << std::endl;
		//PrintMatrix(model);

		glm::mat4 mvp = m_Proj * m_View * model;


		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_MVP", mvp);
		m_Shader->SetUniform4f("u_Color", m_Color[0], m_Color[1], m_Color[2], m_Color[3]);
		renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
	}
	void TestTriangle::OnImGuiRender()
	{
		ImGui::SliderFloat4("Color", m_Color, 0.0f, 1.0f);
		ImGui::SliderFloat3("Translation", &m_Translation.x, 0.0f, 960.0f);
		ImGui::SliderFloat("Scale", &m_Scale, 0.1f, 5.0f);
		ImGui::SliderFloat("Rotation", &m_Rotation, 0.0f, 3.14f * 2);
		//ImGui::ColorEdit4("Color", m_Color);
	}
	void TestTriangle::PrintMatrix(glm::mat4 mat)
	{
		for (int row = 0; row < 4; ++row)
		{
		    for (int col = 0; col < 4; ++col)
		    {
		        std::cout << mat[col][row] << "\t"; // glm is column-major
		    }
		    std::cout << "\n";
		}
	}
}