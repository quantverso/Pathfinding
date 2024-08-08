#ifndef QUANTVERSO_ENTITY_H
#define QUANTVERSO_ENTITY_H

// ---------------------------------------------------------------------------------------------------------------------

#include <SFML/Graphics.hpp>

// ---------------------------------------------------------------------------------------------------------------------

////////////////////////////////////////////////////////////
/// \class Entity
/// \brief Classe base para objetos gráficos que interagem
/// com uma janela gráfica.
///
/// A classe Entity gerencia objetos gráficos e fornece
/// mecanismos para registrar e atualizar esses objetos.
/// 
////////////////////////////////////////////////////////////
class Entity {
private:
    static std::vector<Entity*> objects; ///< Armazena todos os objetos do tipo Entity

    ////////////////////////////////////////////////////////////
    /// \brief Guarda objetos da classe Entity no vetor objects.
    /// 
    /// Registra o endereço de um objeto no vetor estático
    /// objects para rastreamento e atualização.
    ///
    /// \param obj Endereço do objeto que será guardado.
    /// 
    ////////////////////////////////////////////////////////////
    static void Register(Entity* obj);

    ////////////////////////////////////////////////////////////
    /// \brief Remove objetos do vetor objects.
    /// 
    /// Remove o endereço de um objeto do vetor estático
    /// objects, parando seu rastreamento e atualização.
    ///
    /// \param obj Endereço do objeto que será removido.
    /// 
    ////////////////////////////////////////////////////////////
    static void Unregister(Entity* obj);

protected:
    static sf::RenderWindow*& window; ///< Ponteiro para a janela gráfica.
    static sf::Event& event;          ///< Referência para eventos da janela.

    ////////////////////////////////////////////////////////////
    /// \brief Atualiza objetos derivados desta classe.
    /// 
    /// Método virtual para atualizar o estado dos objetos derivados.
    /// Deve ser implementado pelas classes derivadas.
    /// 
    ////////////////////////////////////////////////////////////
    virtual void Update();

public:
    ////////////////////////////////////////////////////////////
    /// \brief Construtor padrão.
    /// 
    /// Chama o método Register() para guardar o endereço do objeto
    /// no vetor objects.
    /// 
    ////////////////////////////////////////////////////////////
    Entity();

    ////////////////////////////////////////////////////////////
    /// \brief Destrutor virtual.
    /// 
    /// Chama o método Unregister() para remover o endereço do objeto
    /// do vetor objects.
    /// 
    ////////////////////////////////////////////////////////////
    virtual ~Entity();

    ////////////////////////////////////////////////////////////
    /// \brief Atualiza todos os objetos derivados desta classe.
    /// 
    /// Chama o método Update() para cada objeto registrado,
    /// atualizando seu estado.
    /// 
    ////////////////////////////////////////////////////////////
    static void UpdateObjects();
};

// ---------------------------------------------------------------------------------------------------------------------

#endif
