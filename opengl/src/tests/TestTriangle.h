#pragma once
#include"Test.h"
#include"VertexArray.h"
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include"VertexBufferLayout.h"
#include"Shader.h"
#include<memory>
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
namespace test
{
	class TestTriangle :public Test
	{
	public:
		TestTriangle();
		~TestTriangle();
		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
		void PrintMatrix(glm::mat4 mat);

	private:
		float m_Positions[6];
		unsigned int m_Indices[3];
		float m_Color[4];
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;

		glm::vec3 m_Translation;
		float m_Scale;            // scale factor
		float m_Rotation;

		glm::mat4 m_Proj;          // projection matrix
		glm::mat4 m_View;          // view matrix (camera)
	};
}