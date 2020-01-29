//STD Headers

//Library Headers

//SuperVoid Headers
#include "utils/Logger.h"

#include "BouncingCube.h"

namespace SuperVoid {

	TYPE_INFO_IMPL(BouncingCube)

	ENABLE_FACTORY(BouncingCube, core::Entity)

	BouncingCube::BouncingCube() {
		Velocity = 0.05f;
	}
	
	void BouncingCube::Initialize() {
		Entity::Initialize();
	}

	void BouncingCube::BeginPlay() {
		utils::Logger::LogInfo(ID.StringID + " began play");
	}

	void SuperVoid::BouncingCube::Tick(float deltaSeconds) {
		Entity::Tick(deltaSeconds);

		auto deltaHeight = deltaSeconds * Velocity;
		math::Quaternion deltaRotation(math::Rotator(-1, 1, -1));

		Position.Y += deltaHeight;
		Rotation = Rotation * deltaRotation;

		if (Position.Y > 2 || Position.Y < -2) {
			Velocity *= -1;
		}
	}

	void BouncingCube::Terminate() {
	
	}
}