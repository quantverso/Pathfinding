#ifndef QUANTVERSO_COLLIDER_H
#define QUANTVERSO_COLLIDER_H

// ---------------------------------------------------------------------------------------------------------------------

#include "Component.h"
#include <vector>
#include <unordered_set>
#include <memory>

class Entity;
class Shape;

template<typename T>
concept DerivedShape = std::is_base_of_v<Shape, T>;

// ---------------------------------------------------------------------------------------------------------------------

////////////////////////////////////////////////////////////
/// \class Collider
/// \brief Respons�vel por gerenciar colisores e detectar colis�es entre objetos.
///
/// A classe Collider mant�m e gerencia os objetos com delimitadores de colis�o, permitindo
/// a verifica��o de colis�es entre diferentes tipos de objetos (est�ticos ou m�veis) e a
/// intera��o entre suas formas geom�tricas.
/// 
////////////////////////////////////////////////////////////
class Collider : public Component
{
public:
    ////////////////////////////////////////////////////////////
    /// \enum Type
    /// \brief Define o tipo de colisor: Ativo ou Passivo.
    ///
    /// O enum Type classifica os tipos de colisores em ativos ou passivos.
    /// - Um **colisor ativo** deve ser utilizado em objetos din�micos que
    ///   causam colis�es com outros objetos.
    /// - Um **colisor passivo** � apropriado para objetos est�ticos que
    ///   n�o iniciam colis�es, mas podem ser atingidos por colisores ativos.
    ///
    /// Esses tipos ajudam a otimizar o comportamento da simula��o de colis�o,
    /// diferenciando entre objetos que interagem ativamente e os que permanecem
    /// inertes no cen�rio.
    ///
    ////////////////////////////////////////////////////////////
    enum Type
    {
        Active, ///< Colisor ativo: usado em objetos m�veis que causam colis�o.
        Passive ///< Colisor passivo: usado em objetos est�ticos que n�o causam colis�o.
    };

    ////////////////////////////////////////////////////////////
    /// \brief Construtor da classe `Collider`.
    ///
    /// Inicializa o colisor com a entidade associada e define o tipo (est�tico ou m�vel).
    ///
    /// \param entity Ponteiro para a entidade associada.
    /// \param type Tipo do colisor (Active ou Passive).
    /// 
    ////////////////////////////////////////////////////////////
    Collider(Entity* entity, Type type);

    ////////////////////////////////////////////////////////////
    /// \brief Destrutor da classe `Collider`.
    /// 
    ////////////////////////////////////////////////////////////
    ~Collider();

    ////////////////////////////////////////////////////////////
    /// \brief Desenha os delimitadores de colis�o.
    ///
    /// Desenha os delimitadores de colis�o.
    /// 
    ////////////////////////////////////////////////////////////
    void Draw();
    
    ////////////////////////////////////////////////////////////
    /// \brief Adiciona um delimitador de colis�o.
    ///
    /// \tparam T A forma geom�trica a ser adicionada ao colisor.
    /// 
    /// \return Um ponteiro para a forma rec�m-adicionada.
    /// 
    ////////////////////////////////////////////////////////////
    template <DerivedShape T, typename... Args>
    T* Add(Args&&... args);

    ////////////////////////////////////////////////////////////
    /// \brief Adiciona um pol�gono delimitador de colis�o.
    /// 
    /// \param std::initializer_list<SDL_Point> Uma lista com as coordenadas
    /// dos v�rtices do pol�gono.
    /// 
    /// \tparam T A forma geom�trica a ser adicionada ao colisor.  
    /// 
    /// \return Um ponteiro para a forma rec�m-adicionada.
    /// 
    ////////////////////////////////////////////////////////////
    template <DerivedShape T>
    T* Add(std::initializer_list<SDL_Point> list);

private:
    Type                                m_Type;      ///< Tipo de colisor (Active, Passive)
    std::unordered_set<Collider*>       m_Collided;  ///< Armazena colisores que colidiram com este
    std::vector<std::unique_ptr<Shape>> m_Boundings; ///< Vetor de delimitadores de colis�o
    bool                                m_Standard;  ///< Indica se o delimitador de colis�o � padr�o

    ////////////////////////////////////////////////////////////
    /// \brief Atualiza o estado do colisor.
    ///
    /// Executa opera��es necess�rias para atualizar a l�gica de colis�o e intera��es.
    ///
    ////////////////////////////////////////////////////////////
    void Update();

    ////////////////////////////////////////////////////////////
    /// \brief Posiciona os delimitadores de colis�o.
    ///
    /// Este metodo posiciona todos os delimitadores de colis�o
    /// com base nos valores informados em x e y.
    /// 
    /// \param x Posi��o no eixo x para os delimitadores.
    /// \param y Posi��o no eixo y para os delimitadores.
    /// 
    ////////////////////////////////////////////////////////////
    void Position(float x, float y);

    ////////////////////////////////////////////////////////////
    /// \brief Adiciona um delimitador de colis�o.
    ///
    /// \param geometry Forma geom�trica do delimitador (Rectangle, Circle, etc.).
    /// 
    ////////////////////////////////////////////////////////////
    Shape* Add(std::unique_ptr<Shape> shape);

    ////////////////////////////////////////////////////////////
    /// \brief Verifica se h� colis�o entre dois conjuntos de delimitadores.
    ///
    /// Este m�todo percorre dois conjuntos de delimitadores (`Bounding`),
    /// comparando cada delimitador de um conjunto com cada delimitador do outro.
    /// Para cada par de delimitadores, chama internamente o m�todo `CheckCollision()`,
    /// que realiza a verifica��o real da colis�o entre dois delimitadores.
    ///
    /// \param boundings Um par de vetores contendo os delimitadores de colis�o:
    /// - O primeiro vetor representa os delimitadores do primeiro objeto.
    /// - O segundo vetor representa os delimitadores do segundo objeto.
    ///
    /// \return Retorna `true` se qualquer par de delimitadores de objetos distintos
    /// estiver colidindo, caso contr�rio, retorna `false`.
    /// 
    ////////////////////////////////////////////////////////////
    bool IsColliding(const Collider* other);
};

// ---------------------------------------------------------------------------------------------------------------------

template<DerivedShape T, typename ...Args>
T* Collider::Add(Args && ...args)
{
    return (T*)Add(std::make_unique<T>(std::forward<Args>(args)...));
}

// ---------------------------------------------------------------------------------------------------------------------

template<DerivedShape T>
T* Collider::Add(std::initializer_list<SDL_Point> list)
{
    return (T*)Add(std::make_unique<T>(list));
}

// ---------------------------------------------------------------------------------------------------------------------

#endif
