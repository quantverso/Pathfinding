#include "Entity.h"
#include "Engine.h"

// ------------------------------------------------------------------------------------------------

Window&	Entity::window{ Engine::window };		///< Janela gráfica
float&	Entity::deltaTime{ Engine::deltaTime };	///< Tempo decorrido entre frames

//--------------------------------------------------------------------------------------------------

Entity::Entity() :
	material(*AddComponent<Material>()),
	transform(*AddComponent<Transform>())
{
}

//--------------------------------------------------------------------------------------------------
