#include "Entity.h"
#include "Engine.h"

// ------------------------------------------------------------------------------------------------
// Inicialização de membros estáticos da classe

Window&	Entity::window{ Engine::window };		///< Janela gráfica
float&	Entity::deltaTime{ Engine::deltaTime };	///< Tempo decorrido entre frames

//--------------------------------------------------------------------------------------------------

Entity::Entity() :
	material(*AddComponent<Material>()),
	transform(*AddComponent<Transform>()),	
	position(transform.rect.position),
	width(transform.rect.width),
	height(transform.rect.height),
	bounds(transform.rect.bounds)
{
}

//--------------------------------------------------------------------------------------------------
