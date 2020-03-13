//STD Headers

//Library Headers

//Void Engine Headers
#include "utils/resource/JsonResource.h"

#include "gameplay_framework/Entity.h"
#include "gameplay_framework/Component.h"
#include "Scene.h"

namespace core {
	
	TYPE_INFO_IMPL(Entity)

	ENABLE_FACTORY(Entity, Entity)
	
	Entity::Entity() : m_Name("Entity"), m_World(nullptr), m_Parent(nullptr){
	
	}

	Entity::~Entity() {
		for (auto& componentEntry : m_Components) {
			delete componentEntry.second;
		}
		m_Components.clear();
	}

	void Entity::Input(const InputAction& input, float deltaTime) {
		for (auto& componentEntry : m_Components) {
			componentEntry.second->Input(input, deltaTime);
		}
	}

	void Entity::Input(const AxisInputAction& input, float deltaTime) {
		for (auto& componentEntry : m_Components) {
			componentEntry.second->Input(input, deltaTime);
		}
	}

	void Entity::Initialize() {
		if (!ConfigData.is_null()) {
			m_Name = utils::Name(ConfigData["name"]);

			auto locationData = ConfigData["location"];
			m_Transform.Position = math::Vector3(
				locationData[0].get<float>(),
				locationData[1].get<float>(),
				locationData[2].get<float>()
			);
		
			auto rotationData = ConfigData["rotation"];
			if (!rotationData.is_null()) {
				m_Transform.Rotation = math::Quaternion(
					math::Rotator(
						rotationData[0].get<float>(),
						rotationData[1].get<float>(),
						rotationData[2].get<float>()
					)
				);
			}

			auto scaleData = ConfigData["scale"];
			if (!scaleData.is_null()) {
				m_Transform.Scale = math::Vector3(
					scaleData[0].get<float>(),
					scaleData[1].get<float>(),
					scaleData[2].get<float>()
				);
			}
		}
		
		for (auto& componentEntry : m_Components) {
			componentEntry.second->Initialize();
		}
	}

	void Entity::BeginPlay() {
		;
	}

	void Entity::Tick(float deltaTime) {
		for (auto& componentEntry : m_Components) {
			componentEntry.second->Tick(deltaTime);
		}
	}

	void Entity::Terminate() {
		;
	}

	void Entity::Draw() const {
		for (auto& componentEntry : m_Components) {
			componentEntry.second->Draw();
		}
	}

	float Entity::GetDistance(const Entity* const other) const {
		return (m_Transform.Position - other->GetPostion()).Magnitude();
	}

	float Entity::GetDistanceSquared(const Entity* const other) const {
		return (m_Transform.Position - other->GetPostion()).Magnitude2();
	}

	math::Vector3 Entity::GetPostion() const {
		return m_Transform.Position;
	}

	void Entity::SetPosition(const math::Vector3& newPosition) {
		m_Transform.Position = newPosition;
	}

	math::Rotator Entity::GetRotation() const {
		return m_Transform.Rotation.ToEuler();
	}

	void Entity::SetRotation(const math::Rotator& newRotation) {
		m_Transform.Rotation = math::Quaternion(newRotation);
	}

	math::Vector3 Entity::GetScale() const {
		return m_Transform.Scale;
	}

	void Entity::SetScale(const math::Vector3& newScale) {
		m_Transform.Scale = newScale;
	}

	Transform& Entity::GetTransform() {
		return m_Transform;
	}

	std::string Entity::GetName() const {
		return m_Name.StringID;
	}

	void Entity::SetName(const std::string& name) {
		m_Name = utils::Name(name);
	}

	void Entity::SetName(const utils::Name& name) {
		m_Name = name;
	}

	void Entity::AddComponent(Component* component) {
		//Abuse friendship to give the child component necessary references
		component->m_Parent = this;
		component->m_Transform = &m_Transform;

		//Register component
		m_Components[component->GetTypename()] = component;
	}

	Scene* Entity::GetWorld() const {
		return m_World;
	}

	void Entity::SetScene(Scene* world) {
		m_World = world;
	}

	void Entity::SetParent(Entity* parent) {
		m_Parent = parent;
	}

}
