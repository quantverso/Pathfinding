#ifndef QUANTVERSO_ENTITY_H
#define QUANTVERSO_ENTITY_H

//--------------------------------------------------------------------------------------------------

#include "Window.h"
#include "Material.h"
#include "Transform.h"
#include "Texture.h"
#include <unordered_map>
#include <typeindex>

using ComponentsMap = std::unordered_map<std::type_index, std::unique_ptr<Component>>;

//--------------------------------------------------------------------------------------------------

class Entity
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Cosntrutor padr�o
    /// 
    /// Inicializa vari�veis da classe.
    /// 
    ////////////////////////////////////////////////////////////
    Entity();

    ////////////////////////////////////////////////////////////
    /// \brief Destrutor virtual.
    /// 
    /// Remove o endere�o do objeto do vector objects.
    /// 
    ////////////////////////////////////////////////////////////
    virtual ~Entity() = default;

    ////////////////////////////////////////////////////////////
    /// \brief Adiciona um componente � entidade.
    ///
    /// Este m�todo cria e adiciona um novo componente do tipo `T` 
    /// � entidade, passando os argumentos fornecidos para o
    /// construtor do componente. A entidade � associada ao componente.
    ///
    /// \tparam Args Tipos dos argumentos a serem passados para o construtor do componente.
    /// 
    /// \return Um ponteiro para o componente rec�m-adicionado.
    ///
    ////////////////////////////////////////////////////////////
    template<typename T, typename... Args>
    T* AddComponent(Args&&... args);

    ////////////////////////////////////////////////////////////
    /// \brief Obt�m um componente da entidade atual.
    ///
    /// Este m�todo recupera um componente do tipo `T` associado � 
    /// entidade atual.
    ///
    /// \tparam T O tipo de componente a ser obtido.
    /// 
    /// \return Um ponteiro para o componente solicitado.
    ///
    ////////////////////////////////////////////////////////////
    template<typename T>
    T* GetComponent();

    ////////////////////////////////////////////////////////////
    /// \brief Atualiza objetos derivados desta classe.
    /// 
    /// M�todo virtual chamado a cada frame para atualizar objetos.
    /// Deve ser implementado pelas classes derivadas.
    /// 
    ////////////////////////////////////////////////////////////
    virtual void Update() {};

    ////////////////////////////////////////////////////////////
    /// \brief Desenha objetos derivados desta classe.
    /// 
    /// M�todo virtual chamado a cada frame para desenhar objetos.
    /// Deve ser implementado pelas classes derivadas.
    /// 
    ////////////////////////////////////////////////////////////
    virtual void Draw();

protected:
    static Window& window;    ///< Referencia para a janela gr�fica.
    static float&  deltaTime; ///< Tempo decorrido entre frames

private:
    friend class Component;
 
    ComponentsMap components; ///< Hash de components

public:	
	Material&  material;  ///< Componente padr�o de textura e cores
    Transform& transform; ///< Componente padr�o de transforma��o
};

// ------------------------------------------------------------------------------------------------

inline void Entity::Draw()
{    
    if (material.texture)
        window.Draw(
            material.texture.get(),
            &material,
            &transform,
            0,
            &transform.offset
        );
}

// ------------------------------------------------------------------------------------------------

template<typename T, typename... Args>
T* Entity::AddComponent(Args&&... args)
{
    auto component{ std::make_unique<T>(this, std::forward<Args>(args)...) };
    T* componentPtr{ component.get() };
    components[typeid(T)] = std::move(component);
    return componentPtr;
}

// ------------------------------------------------------------------------------------------------

template<typename T>
T* Entity::GetComponent()
{
    auto it{ components.find(std::type_index(typeid(T))) };
    if (it != components.end())
        return static_cast<T*>(it->second.get());
    return nullptr;
}

// ------------------------------------------------------------------------------------------------

#endif
