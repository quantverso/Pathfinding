#include "Material.h"
#include "Entity.h"
#include "Texture.h"

//--------------------------------------------------------------------------------------------------

Material::Material(Entity* entity) :
	Component(entity),
	texture(texture_),
	rect_({}),
	texture_(nullptr),
	rect(rect_)
{
}

//--------------------------------------------------------------------------------------------------

void Material::Color(::Color color)
{
	if (texture)
		texture->Color(color);
}

//--------------------------------------------------------------------------------------------------

void Material::Add(const Texture* texture)
{
	this->texture_ = std::shared_ptr<Texture>(const_cast<Texture*>(texture), [](Texture*) {});
	entity->transform.Size(texture->Size().width, texture->Size().height);
	rect_.w = int(texture->Size().width);
	rect_.h = int(texture->Size().height);
}

//--------------------------------------------------------------------------------------------------

void Material::Add(const char* file)
{
	texture_ = std::make_shared<Texture>();
	texture_->Load(file);
	entity->transform.Size(texture->Size().width, texture->Size().height);
	rect_.w = int(texture->Size().width);
	rect_.h = int(texture->Size().height);
}

//--------------------------------------------------------------------------------------------------

void Material::Rect(::Rect rect)
{
	rect_ = rect;
}

//--------------------------------------------------------------------------------------------------
