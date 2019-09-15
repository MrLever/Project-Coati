//STD Headers

//Library Headers

//Void Engine Headers
#include "Entity.h"

namespace EngineCore {
	///CTORS
	Entity::Entity(const std::string& name) : ID(std::move(name)), GraphicsData(nullptr) {

	}

	Entity::Entity(const EngineUtils::Name& name) : ID(std::move(name)), GraphicsData(nullptr) {
	
	}

	Entity::~Entity() {
		delete GraphicsData;
	}

	EngineMath::Vector3 Entity::GetPostion() {
		return Position;
	}

	void Entity::SetPosition(const EngineMath::Vector3& newPosition) {
		Position = newPosition;
	}
	
	void Entity::SetGraphicsComponent(GraphicsComponent* component) {
		if (GraphicsData != nullptr) {
			delete GraphicsData;
			GraphicsData = nullptr;
		}

		GraphicsData = component;
	}

	GraphicsComponent* Entity::GetGraphicsComponent() {
		return GraphicsData;
	}
}
