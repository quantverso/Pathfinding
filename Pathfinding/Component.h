#ifndef QUANTVERSO_COMPONENT_H
#define QUANTVERSO_COMPONENT_H

//--------------------------------------------------------------------------------------------------

#include "Engine.h"

class Entity;

//--------------------------------------------------------------------------------------------------

class Component
{
public:
	Component(Entity*& entity);
	virtual ~Component() = default;

protected:
	static Window& window;	///< Refer�ncia para a janela gr�fica
	Entity* const  entity;	///< Entidade a qual pertence o componente
};

//--------------------------------------------------------------------------------------------------

#endif
