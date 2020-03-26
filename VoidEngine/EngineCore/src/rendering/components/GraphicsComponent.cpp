//STD Headers

//Library Headers
#include <glm/gtx/quaternion.hpp>

//Void Engine Headers
#include "utils/TimeUtils.h"

#include "gameplay_framework/Entity.h"
#include "rendering/components/GraphicsComponent.h"
#include "rendering/ShaderProgram.h"
#include "rendering/Texture.h"

namespace core {

	TYPE_INFO_IMPL(GraphicsComponent)

	ENABLE_FACTORY(GraphicsComponent, Component)

	GraphicsComponent::GraphicsComponent()
		: m_TransformMatrix(1.0f), m_Shader(nullptr), m_IsValid(true) {

	}

	GraphicsComponent::~GraphicsComponent() {

	}

	void GraphicsComponent::Initialize() {
		if (!m_Parent) {
			return;
		}
		
		auto modelCache = std::make_shared<utils::ResourceAllocator<Model>>();

		m_Model = modelCache->GetResource(ConfigData["model"].get<std::string>());
		m_Model->Initialize();

		if (ConfigData.find("shader") != ConfigData.end()) {
			AddMaterial(
				ConfigData["shader"]["name"].get<std::string>(),
				ConfigData["shader"]["vertexShader"].get<std::string>(),
				ConfigData["shader"]["fragmentShader"].get<std::string>()
			);
		}
		else {
			AddMaterial("DefaultMaterial", "Resources/Shaders/default.vert", "Resources/Shaders/default.frag");
		}
	}

	void GraphicsComponent::AddMaterial(const std::string& name, const std::string& vertShaderPath, const std::string& fragShaderPath) {
		m_Shader = std::make_shared<ShaderProgram>(
			name,
			new Shader(
				ShaderType::VERTEX,
				vertShaderPath
			),
			new Shader(
				ShaderType::FRAGMENT,
				fragShaderPath
			)
		);
	}

	void GraphicsComponent::Draw() {
		m_TransformMatrix = glm::mat4(1.0f);

		//Translate
		auto position = m_Transform->GetPosition();
		m_TransformMatrix = glm::translate(
			m_TransformMatrix, 
			glm::vec3(position.X, position.Y, position.Z)
		);

		//Rotate
		auto rotation = math::Quaternion(m_Transform->GetRotation()).Normalize();
		auto rotationMatrix = glm::toMat4(glm::quat(rotation.W, rotation.X, rotation.Y, rotation.Z));
		m_TransformMatrix = m_TransformMatrix * rotationMatrix;

		//Scale
		auto scale = m_Transform->GetScale();
		m_TransformMatrix = glm::scale(
			m_TransformMatrix, 
			glm::vec3(scale.X, scale.Y, scale.Z)
		);
		
		if (m_Model) {
			m_Model->Draw(m_Shader, m_TransformMatrix);
		}
	}

}