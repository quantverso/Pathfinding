#ifndef QUANTVERSO_ENGINE_H
#define QUANTVERSO_ENGINE_H

// ------------------------------------------------------------------------------------------------

#include "Window.h"
#include "Scene.h"

class Entity;

// ------------------------------------------------------------------------------------------------

////////////////////////////////////////////////////////////
/// class Engine
/// \brief Classe principal responsável pelo loop, gerenciamento
/// de eventos e comunicação entre as demais classes.
/// 
////////////////////////////////////////////////////////////
class Engine
{
public:
    static Window window;    ///< Janela gráfica 
    static float  deltaTime; ///< Tempo decorrido entre frames

    ////////////////////////////////////////////////////////////
    /// \brief Contrutor padrão.
    ///
    /// Inicializa variáveis da classe.
    /// 
    ////////////////////////////////////////////////////////////
    Engine();

    ////////////////////////////////////////////////////////////
    /// \brief Inicia a execução do jogo com a entidade principal
    ///
    /// \param entity  Ponteiro para a entidade principal do jogo
    /// \return Retorna um código de status da execução (0 em caso de sucesso)
    /// 
    ////////////////////////////////////////////////////////////
    int Run(Scene* scene);

private:
    static Scene* scene; ///< Cena a ser executada
    const char*   title; ///< Título da janela

    ////////////////////////////////////////////////////////////
    /// \brief Laço principal do jogo
    /// O laço roda enquanto a janela gráfica estiver aberta
    ///
    /// \return Retorna um código de status da execução (0 em caso de sucesso)
    /// 
    ////////////////////////////////////////////////////////////
    int Loop();
};

// ------------------------------------------------------------------------------------------------

#endif
