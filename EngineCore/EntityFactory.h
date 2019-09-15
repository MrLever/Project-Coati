#pragma once
//STD Headers
#include <memory>
#include <vector>
#include <string>

//Library Headers
#include "nlohmann/json.hpp"

//Void Engine Headers
#include "Entity.h"
#include "GraphicsComponent.h"

namespace EngineCore {
	
	/**
	 * @class EntityFactory
	 * @brief Factory class to generate game enities from JSON data
	 */
	class EntityFactory	{
	public:
		[[nodiscard]] std::vector<std::shared_ptr<Entity>> CreateEntityList(const nlohmann::json& entityList);

		template<class T>
		[[nodiscard]] std::shared_ptr<T> CreateEntity(const nlohmann::json& entityData);

	};

	template<class T>
	inline std::shared_ptr<T> EntityFactory::CreateEntity(const nlohmann::json& entityData) {
		auto entityName = entityData["name"].get<std::string>();
		auto entity = std::make_shared<T>(entityName);

		EngineMath::Vector3 position;
		position.X = entityData["location"][0].get<float>();
		position.Y = entityData["location"][1].get<float>();
		position.Z = entityData["location"][2].get<float>();

		entity->SetPosition(position);
		
		std::vector<float> verts;

		auto graphicsData = entityData["graphicsComponent"];

		for (auto vert : graphicsData["model"]) {
			verts.push_back(vert.get<float>());
		}

		Shader vertShader(
			ShaderType::VERTEX, 
			graphicsData["material"]["vertexShader"].get<std::string>()
		);

		Shader fragShader(
			ShaderType::FRAGMENT,
			 graphicsData["material"]["fragmentShader"].get<std::string>()
		);

		GraphicsComponent* entityDrawData = new GraphicsComponent(
			verts,
			ShaderProgram(
				graphicsData["material"]["name"].get<std::string>(), 
				vertShader, 
				fragShader
			)
		);

		entity->SetGraphicsComponent(entityDrawData);

		return entity;
	}
}