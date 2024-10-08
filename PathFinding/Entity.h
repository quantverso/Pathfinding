#ifndef QUANTVERSO_ENTITY_H
#define QUANTVERSO_ENTITY_H

// ---------------------------------------------------------------------------------------------------------------------

#include <SFML/Graphics.hpp>

// ---------------------------------------------------------------------------------------------------------------------

////////////////////////////////////////////////////////////
/// \class Entity
/// \brief Classe base para objetos gr�ficos que interagem
/// com uma janela gr�fica.
///
/// A classe Entity gerencia objetos gr�ficos e fornece
/// mecanismos para registrar e atualizar esses objetos.
/// 
////////////////////////////////////////////////////////////
class Entity {
private:
    static std::vector<Entity*> objects; ///< Armazena todos os objetos do tipo Entity

    ////////////////////////////////////////////////////////////
    /// \brief Guarda objetos da classe Entity no vetor objects.
    /// 
    /// Registra o endere�o de um objeto no vetor est�tico
    /// objects para rastreamento e atualiza��o.
    ///
    /// \param obj Endere�o do objeto que ser� guardado.
    /// 
    ////////////////////////////////////////////////////////////
    static void Register(Entity* obj);

    ////////////////////////////////////////////////////////////
    /// \brief Remove objetos do vetor objects.
    /// 
    /// Remove o endere�o de um objeto do vetor est�tico
    /// objects, parando seu rastreamento e atualiza��o.
    ///
    /// \param obj Endere�o do objeto que ser� removido.
    /// 
    ////////////////////////////////////////////////////////////
    static void Unregister(Entity* obj);

protected:
    static sf::RenderWindow*& window; ///< Ponteiro para a janela gr�fica.
    static sf::Event& event;          ///< Refer�ncia para eventos da janela.

    ////////////////////////////////////////////////////////////
    /// \brief Atualiza objetos derivados desta classe.
    /// 
    /// M�todo virtual para atualizar o estado dos objetos derivados.
    /// Deve ser implementado pelas classes derivadas.
    /// 
    ////////////////////////////////////////////////////////////
    virtual void Update();

public:
    ////////////////////////////////////////////////////////////
    /// \brief Construtor padr�o.
    /// 
    /// Chama o m�todo Register() para guardar o endere�o do objeto
    /// no vetor objects.
    /// 
    ////////////////////////////////////////////////////////////
    Entity();

    ////////////////////////////////////////////////////////////
    /// \brief Destrutor virtual.
    /// 
    /// Chama o m�todo Unregister() para remover o endere�o do objeto
    /// do vetor objects.
    /// 
    ////////////////////////////////////////////////////////////
    virtual ~Entity();

    ////////////////////////////////////////////////////////////
    /// \brief Atualiza todos os objetos derivados desta classe.
    /// 
    /// Chama o m�todo Update() para cada objeto registrado,
    /// atualizando seu estado.
    /// 
    ////////////////////////////////////////////////////////////
    static void UpdateObjects();
};

// ---------------------------------------------------------------------------------------------------------------------

#endif
