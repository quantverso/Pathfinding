#include "Component.h"
#include "Entity.h"

// ------------------------------------------------------------------------------------------------
// Inicializa��o de membros est�ticos da classe

Window& Component::window{ Engine::window }; ///< Refer�ncia para a janela gr�fica

//--------------------------------------------------------------------------------------------------

Component::Component(Entity*& entity) :
	entity(entity)
{	
}

//--------------------------------------------------------------------------------------------------