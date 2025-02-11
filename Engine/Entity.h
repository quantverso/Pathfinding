#ifndef QUANTVERSO_ENTITY_H
#define QUANTVERSO_ENTITY_H

//--------------------------------------------------------------------------------------------------

#include "Window.h"
#include "Scene.h"
#include "Sprite.h"
#include "Transform.h"
#include "Collider.h"
#include "Animation.h"
#include "Sound.h"
#include "Texture.h"
#include "Text.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Point.h"
#include "Polygon.h"
#include <string>
#include <map>
#include <typeindex>
#include <concepts>

template<typename T>
concept DerivedComponent = std::derived_from<T, Component>;

template<typename T>
concept DerivedScene = std::derived_from<T, Scene>;

//--------------------------------------------------------------------------------------------------

class Entity
{
public:
    Entity();
    virtual ~Entity() = default;

    ////////////////////////////////////////////////////////////
    /// \brief Lida com colis�es entre este objeto e outro.
    ///
    /// Este m�todo virtual � chamado automaticamente quando h� uma colis�o
    /// entre este objeto e outro objeto do jogo. Pode ser sobrescrito
    /// nas classes derivadas para implementar comportamentos espec�ficos de colis�o.
    /// 
    /// \param obj Uma refer�ncia para a entidade que colidiu com esta.
    ///
    ////////////////////////////////////////////////////////////
    virtual void OnCollision(Entity& other) {};

    ////////////////////////////////////////////////////////////
    /// \brief Define a tag associada ao objeto.
    ///
    /// A tag � uma string que pode ser usada para agrupar ou
    /// identificar objetos, permitindo a categoriza��o de
    /// m�ltiplos objetos sob a mesma tag.
    ///
    /// \param tag A string contendo a nova tag do objeto.
    ///
    ////////////////////////////////////////////////////////////
    void SetTag(const char* tag);

    ////////////////////////////////////////////////////////////
    /// \brief Desenha objetos derivados desta classe.
    /// 
    /// M�todo virtual chamado a cada frame para desenhar objetos.
    /// Deve ser implementado pelas classes derivadas.
    /// 
    ////////////////////////////////////////////////////////////
    virtual void Draw();

    ////////////////////////////////////////////////////////////
    /// \brief Remove o objeto da cena em que ele estiver associado.
    ///
    /// Este m�todo remove o objeto da cena sem destru�-lo.
    ///
    ////////////////////////////////////////////////////////////
    void Remove();

    ////////////////////////////////////////////////////////////
    /// \brief Destr�i o objeto.
    ///
    /// Este m�todo remove e destr�i o objeto ao final do frame
    /// em que foi invocado.
    ///
    ////////////////////////////////////////////////////////////
    void Destroy();

    ////////////////////////////////////////////////////////////
    /// \brief Retorna o id do objeto.
    ///
    /// A ID � uma string que cont�m a identifica��o �nica do objeto.
    ///
    /// \return Uma refer�ncia para a string contendo o ID do objeto.
    ///
    ////////////////////////////////////////////////////////////
    const std::string& GetId() const;

    ////////////////////////////////////////////////////////////
    /// \brief Retorna a tag do objeto.
    ///
    /// A tag � uma string que pode ser usada para agrupar ou identificar objetos,
    /// permitindo a categoriza��o de m�ltiplos objetos sob a mesma tag.
    ///
    /// \return Uma refer�ncia para a string contendo a tag do objeto.
    ///
    ////////////////////////////////////////////////////////////
    const std::string& GetTag() const;

    ////////////////////////////////////////////////////////////
    /// \brief Adiciona um componente ao objeto.
    ///
    /// Este m�todo cria e adiciona um novo componente do tipo `T` ao objeto,
    /// passando os argumentos fornecidos para o construtor do componente.
    ///
    /// \tparam Args Tipos dos argumentos a serem passado para o construtor do componente.
    /// 
    /// \return Um ponteiro para o componente rec�m-adicionado.
    ///
    ////////////////////////////////////////////////////////////
    template<DerivedComponent T, typename... Args>
    T* AddComponent(Args&&... args);

    ////////////////////////////////////////////////////////////
    /// \brief Obt�m um componente do objeto atual.
    ///
    /// Este m�todo recupera um componente do tipo `T` associado ao objeto atual.
    ///
    /// \tparam T O tipo de componente a ser obtido.
    /// 
    /// \return Um ponteiro para o componente solicitado.
    ///
    ////////////////////////////////////////////////////////////
    template<DerivedComponent T>
    T* GetComponent() const;

    ////////////////////////////////////////////////////////////
    /// \brief Retorna um ponteiro para a cena associada.
    ///
    /// \tparam T O tipo da cena a ser obtida.
    /// 
    /// \return O endere�o da cena em que o objeto foi criado ou adicionado.
    ///
    ////////////////////////////////////////////////////////////
    template<DerivedScene T = Scene>
    T* GetScene() const;

protected:
    static Window& window;    ///< Referencia para a janela gr�fica.
    static float&  deltaTime; ///< Tempo decorrido entre frames

private:
	friend class Scene;

    using ComponentMap = std::map<std::type_index, std::unique_ptr<Component>>;
    
    std::string  m_Id;                 ///< Identifica��o �nica do objeto
    std::string  m_Tag;                ///< Tag para agrupar o objeto
    Scene*       m_Scene;              ///< Refer�ncia interna para a cena
    bool         m_RemovalRequest;     ///< Flag para remo��o do objeto da cena
    bool         m_DestructionRequest; ///< Flag para destrui��o do objeto   
    ComponentMap m_Components;         ///< Tabela de componentes

    ////////////////////////////////////////////////////////////
    /// \brief Inicializa objetos derivados desta classe.
    /// 
    /// M�todo virtual chamado uma vez no mesmo frame em que o objeto
    /// � instanciado, logo ap�s sua refer�ncia para a cena ser inicializada.
    /// Deve ser implementado pelas classes derivadas.
    /// 
    ////////////////////////////////////////////////////////////
    virtual void Awake() {};

    ////////////////////////////////////////////////////////////
    /// \brief Inicializa objetos derivados desta classe.
    /// 
    /// M�todo virtual chamado uma vez no pr�ximo frame ap�s a
    /// cria��o do objeto.
    /// Deve ser implementado pelas classes derivadas.
    /// 
    ////////////////////////////////////////////////////////////
    virtual void Start() {};

    ////////////////////////////////////////////////////////////
    /// \brief Atualiza objetos derivados desta classe.
    /// 
    /// M�todo virtual chamado a cada frame para atualizar objetos.
    /// Deve ser implementado pelas classes derivadas.
    /// 
    ////////////////////////////////////////////////////////////
    virtual void Update() {};

public:	
	Sprite&    sprite;
    Transform& transform;
};

// ------------------------------------------------------------------------------------------------

inline void Entity::Draw()
{    
    if (sprite.m_Texture)
        window.Draw(sprite.m_Texture.get(), &sprite, &transform, transform.GetAngle().degrees, &transform.GetOrigin());
}

// ------------------------------------------------------------------------------------------------

inline const std::string& Entity::GetId() const
{
    return m_Id;
}

// ------------------------------------------------------------------------------------------------

inline const std::string& Entity::GetTag() const
{
    return m_Tag;
}

// ------------------------------------------------------------------------------------------------

template<DerivedComponent T, typename... Args>
T* Entity::AddComponent(Args&&... args)
{
    auto component{ std::make_unique<T>(this, std::forward<Args>(args)...) };
    T* componentPtr{ component.get() };
    m_Components[std::type_index(typeid(T))] = std::move(component);
    return componentPtr;
}

// ------------------------------------------------------------------------------------------------

template<DerivedComponent T>
T* Entity::GetComponent() const
{
    if (auto it{ m_Components.find(std::type_index(typeid(T))) }; it != m_Components.end())
        return (T*)it->second.get();
    return nullptr;
}

// ------------------------------------------------------------------------------------------------

template<DerivedScene T>
inline T* Entity::GetScene() const
{
    return (T*)m_Scene;
}

// ------------------------------------------------------------------------------------------------

#endif
