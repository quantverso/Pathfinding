#ifndef QUANTVERSO_MATERIAL_H
#define QUANTVERSO_MATERIAL_H

//--------------------------------------------------------------------------------------------------

#include <SDL.h>
#include "Component.h"
#include "Texture.h"
#include "Color.h"
#include <memory>

//--------------------------------------------------------------------------------------------------

class Material : public Component
{
public:
	const std::shared_ptr<Texture>& texture;
	const ::Rect&					rect;

	Material(Entity* entity);	
	
	void Add(const Texture* texture);
	void Add(const char* file);
	void Rect(::Rect rect);
	void Color(::Color color);

private:
	friend class Entity;

	std::shared_ptr<Texture> texture_;
	::Rect					 rect_;
};

//--------------------------------------------------------------------------------------------------

#endif
