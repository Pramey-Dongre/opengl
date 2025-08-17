#include"TestQuadBatch.h"
#include"Renderer.h"
#include"imgui/imgui.h"
#include"Texture.h"
#include <array>
namespace test
{

	std::array<Vertex, 4> TestQuadBatch::CreateQuad(float x, float y, float texID)
	{
		float size = 100.0f; // or make this another parameter if you want variable size

		Vertex v0;
		v0.Position[0] = x;
		v0.Position[1] = y;
		v0.Position[2] = 0.0f;
		v0.Color[0] = 0.18f; v0.Color[1] = 0.6f; v0.Color[2] = 0.96f; v0.Color[3] = 1.0f;
		v0.TexCoords[0] = 0.0f; v0.TexCoords[1] = 0.0f;
		v0.TexID = texID;

		Vertex v1;
		v1.Position[0] = x + size;
		v1.Position[1] = y;
		v1.Position[2] = 0.0f;
		v1.Color[0] = 0.18f; v1.Color[1] = 0.6f; v1.Color[2] = 0.96f; v1.Color[3] = 1.0f;
		v1.TexCoords[0] = 1.0f; v1.TexCoords[1] = 0.0f;
		v1.TexID = texID;

		Vertex v2;
		v2.Position[0] = x + size;
		v2.Position[1] = y + size;
		v2.Position[2] = 0.0f;
		v2.Color[0] = 0.18f; v2.Color[1] = 0.6f; v2.Color[2] = 0.96f; v2.Color[3] = 1.0f;
		v2.TexCoords[0] = 1.0f; v2.TexCoords[1] = 1.0f;
		v2.TexID = texID;

		Vertex v3;
		v3.Position[0] = x;
		v3.Position[1] = y + size;
		v3.Position[2] = 0.0f;
		v3.Color[0] = 0.18f; v3.Color[1] = 0.6f; v3.Color[2] = 0.96f; v3.Color[3] = 1.0f;
		v3.TexCoords[0] = 0.0f; v3.TexCoords[1] = 1.0f;
		v3.TexID = texID;

		return { v0, v1, v2, v3 };
	}
	TestQuadBatch::TestQuadBatch()
		:m_Positions{ 
			50.0f, 50.0f,0.18f,0.6f,0.96f,1.0f,0.0f,0.0f,0.0f,
			100.0f, 50.0f, 0.18f,0.6f,0.96f,1.0f,1.0f,0.0f,0.0f,
			100.0f, 100.0f,0.18f,0.6f,0.96f,1.0f,1.0f,1.0f,0.0f,
			50.0f, 100.0f,0.18f,0.6f,0.96f,1.0f,0.0f,1.0f,0.0f,

			200.0f, 50.0f,1.0f,0.93f,0.24f,1.0f,0.0f,0.0f,1.0f,
			250.0f, 50.0f, 1.0f,0.93f,0.24f,1.0f,1.0f,0.0f,1.0f,
			250.0f, 100.0f,1.0f,0.93f,0.24f,1.0f,1.0f,1.0f,1.0f,
			200.0f, 100.0f,1.0f,0.93f,0.24f,1.0f,0.0f,1.0f,1.0f
		},
		m_Indices{
			0,1,2,
			2,3,0,

			4,5,6,
			6,7,4
		}, 
		//m_Color{ 0.8f, 0.3f, 0.8f, 1.0f },
		m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
		m_View(glm::mat4(1.0f)),
		m_Translation(200.0f, 200.0f, 0.0f),
		m_Scale(1.0f),
		m_Rotation(0.0f)
	{
		std::cout << "Initial Projection Matrix" << std::endl;
		PrintMatrix(m_Proj);
		m_VAO = std::make_unique<VertexArray>();

		m_VertexBuffer = std::make_unique<VertexBuffer>(1000* sizeof(Vertex));
		m_VAO->Bind();
		m_VertexBuffer->Bind();
		GLCall(glEnableVertexAttribArray(0));
		GLCall(glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex), (const void*)offsetof(Vertex, Position)));

		GLCall(glEnableVertexAttribArray(1));
		GLCall(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex,Color)));

		GLCall(glEnableVertexAttribArray(2));
		GLCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex,TexCoords)));

		GLCall(glEnableVertexAttribArray(3));
		GLCall(glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TexID)));

		//VertexBufferLayout layout;
		//layout.Push<float>(2);
		//layout.Push<float>(4);
		//layout.Push<float>(2);
		//layout.Push<float>(1);

		//m_VAO->AddBuffer(*m_VertexBuffer, layout);

		m_IndexBuffer = std::make_unique<IndexBuffer>(m_Indices, 12);

		m_FirstT =  Texture::LoadTexture("res/textures/porsche.png");
		m_SecondT = Texture::LoadTexture("res/textures/lambo.png");

		m_Shader = std::make_unique<Shader>("res/Quad.shader");
	}

	TestQuadBatch::~TestQuadBatch()
	{
	}
	void TestQuadBatch::OnUpdate(float deltaTime)
	{
	}
	void TestQuadBatch::OnRender()
	{
		GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
		/*float v[] = {
			50.0f, 50.0f,0.0f,0.18f,0.6f,0.96f,1.0f,0.0f,0.0f,0.0f,
			100.0f, 50.0f,0.0f, 0.18f,0.6f,0.96f,1.0f,1.0f,0.0f,0.0f,
			100.0f, 100.0f,0.0f,0.18f,0.6f,0.96f,1.0f,1.0f,1.0f,0.0f,
			50.0f, 100.0f,0.0f,0.18f,0.6f,0.96f,1.0f,0.0f,1.0f,0.0f,

			200.0f, 50.0f,0.0f,1.0f,0.93f,0.24f,1.0f,0.0f,0.0f,1.0f,
			250.0f, 50.0f,0.0f, 1.0f,0.93f,0.24f,1.0f,1.0f,0.0f,1.0f,
			250.0f, 100.0f,0.0f,1.0f,0.93f,0.24f,1.0f,1.0f,1.0f,1.0f,
			200.0f, 100.0f,0.0f,1.0f,0.93f,0.24f,1.0f,0.0f,1.0f,1.0f
		};*/

		auto q0 = CreateQuad(m_QuadPosition1[0], m_QuadPosition1[1], 0.0f);
		auto q1 = CreateQuad(m_QuadPosition2[0], m_QuadPosition2[1], 1.0f);

		Vertex v[8];
		memcpy(v, q0.data(), q0.size() * sizeof(Vertex));
		memcpy(v+q0.size(), q1.data(), q1.size() * sizeof(Vertex));

		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer->GetRendererID()));
		GLCall(glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(v),v));

		GLCall(glClear(GL_COLOR_BUFFER_BIT));
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
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

		GLCall(glBindTextureUnit(0, m_FirstT));
		GLCall(glBindTextureUnit(1, m_SecondT));

		//GLCall(glUseProgram(m_Shader->GetRendererId()));
		m_Shader->Bind();
		GLCall(auto loc = glGetUniformLocation(m_Shader->GetRendererId(), "u_Textures"));
		int samplers[2] = { 0,1 };
		GLCall(glUniform1iv(loc, 2, samplers));
		m_Shader->SetUniformMat4f("u_MVP", mvp);
		//m_Shader->SetUniform4f("u_Color", m_Color[0], m_Color[1], m_Color[2], m_Color[3]);
		renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
	}
	void TestQuadBatch::OnImGuiRender()
	{
		//ImGui::SliderFloat4("Color", m_Color, 0.0f, 1.0f);
		ImGui::SliderFloat3("Translation", &m_Translation.x, 0.0f, 960.0f);
		ImGui::SliderFloat("Scale", &m_Scale, 0.1f, 5.0f);
		ImGui::SliderFloat("Rotation", &m_Rotation, 0.0f, 3.14f * 2);
		ImGui::DragFloat2("1st Quad Position", m_QuadPosition1, m_Speed);
		ImGui::DragFloat2("2nd Quad Position", m_QuadPosition2, m_Speed);
		ImGui::DragFloat("Speed", &m_Speed,m_Speed,0.0f,30.0f);
		//ImGui::ColorEdit4("Color", m_Color);
	}
	void TestQuadBatch::PrintMatrix(glm::mat4 mat)
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