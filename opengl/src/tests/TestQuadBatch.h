#pragma once
#include"Test.h"
#include"VertexArray.h"
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include"VertexBufferLayout.h"
#include"Shader.h"
#include<memory>
#include<iostream>
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
namespace test
{
	//struct Vertex
	//{
	//	float Position[3];
	//	float Color[4];
	//	float TexCoords[2];
	//	float TexID;
	//};
	struct Vertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoords;
		float TexID;
	};
	class TestQuadBatch :public Test
	{
	public:
		TestQuadBatch();
		~TestQuadBatch();
		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
		void PrintMatrix(glm::mat4 mat);
		static std::array<Vertex, 4>CreateQuad(float x, float y, float texID);

	private:
		float m_Positions[72];
		float m_QuadPosition1[2] = {300.0f,100.0f};
		float m_QuadPosition2[2] = {450.0f,100.0f};
		float m_Speed = 0.1f;
		unsigned int m_Indices[12];
		uint32_t m_FirstT;
		uint32_t m_SecondT;
		//float m_Color[4];
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