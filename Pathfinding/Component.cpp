#include "Component.h"
#include "Entity.h"

// ------------------------------------------------------------------------------------------------
// Inicialização de membros estáticos da classe

Window& Component::window{ Engine::window }; ///< Referência para a janela gráfica

//--------------------------------------------------------------------------------------------------

Component::Component(Entity*& entity) :
	entity(entity)
{	
}

//--------------------------------------------------------------------------------------------------
