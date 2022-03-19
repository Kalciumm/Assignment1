#include "Gameplay/Components/MovementComponent.h"
#include <GLFW/glfw3.h>
#include "Gameplay/GameObject.h"
#include "Gameplay/Scene.h"
#include "Utils/ImGuiHelper.h"
#include "Application/Application.h"

void MovementComponent::Awake()
{
	_body = GetComponent<Gameplay::Physics::RigidBody>();
	if (_body == nullptr)
	{
		IsEnabled = false;
	}
}

void MovementComponent::RenderImGui()
{
	LABEL_LEFT(ImGui::DragFloat, "Impulse", &_impulse, 1.0f);
}

nlohmann::json MovementComponent::ToJson() const
{
	return
	{
		{ "impulse", _impulse }
	};
}

MovementComponent::MovementComponent() : IComponent(), _impulse(15.0f)
{

}

MovementComponent::~MovementComponent() = default;

MovementComponent::Sptr MovementComponent::FromJson(const nlohmann::json & blob)
{
	MovementComponent::Sptr result = std::make_shared<MovementComponent>();
	result->_impulse = blob["impulse"];
	return result;
}

void MovementComponent::Update(float deltaTime)
{
	bool pressed = glfwGetKey(Application::Get().GetWindow(), GLFW_KEY_W);
	if (pressed)
	{
		isIdle = false;
		if (_isPressed == false)
		{
			_body->SetLinearVelocity(glm::vec3(0.0f, _impulse, 0.0f));
			GetGameObject()->SetRotation(glm::vec3(90.0f, 0.0f, -90.0f));
			rotation = 1;
		}
		_isPressed = pressed;
	}
	else
	{
		_isPressed = false;
	}

	bool pressed1 = glfwGetKey(Application::Get().GetWindow(), GLFW_KEY_S);
	if (pressed1)
	{
		isIdle = false;
		if (_isPressed == false)
		{
			_body->SetLinearVelocity(glm::vec3(0.0f, _impulse * -1.0f, 0.0f));
			GetGameObject()->SetRotation(glm::vec3(90.0f, 0.0f, 90.0f));
			rotation = 2;
		}
		_isPressed = pressed1;
	}
	else
	{
		_isPressed = false;
	}

	bool pressed2 = glfwGetKey(Application::Get().GetWindow(), GLFW_KEY_A);
	if (pressed2)
	{
		isIdle = false;
		if (_isPressed == false)
		{
			_body->SetLinearVelocity(glm::vec3(_impulse * -1.0f, 0.0f, 0.0f));
			GetGameObject()->SetRotation(glm::vec3(90.0f, 0.0f, 0.0f));
			rotation = 3;
		}
		_isPressed = pressed2;
	}
	else
	{
		_isPressed = false;
	}

	bool pressed3 = glfwGetKey(Application::Get().GetWindow(), GLFW_KEY_D);
	if (pressed3)
	{
		isIdle = false;
		if (_isPressed == false)
		{
			_body->SetLinearVelocity(glm::vec3(_impulse, 0.0f, 0.0f));
			GetGameObject()->SetRotation(glm::vec3(90.0f, 0.0f, 180.0f));
			rotation = 4;
		}
		_isPressed = pressed3;
	}
	else
	{
		_isPressed = false;
	}

	if (pressed == false && pressed1 == false)
	{
		if (pressed2 == false && pressed3 == false)
		{
			isIdle = true;
			_body->SetLinearVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
		}
	}
}

