#ifndef QUANTVERSO_ENGINE_H
#define QUANTVERSO_ENGINE_H

// ------------------------------------------------------------------------------------------------

#include "Window.h"
#include "Scene.h"

class Entity;

// ------------------------------------------------------------------------------------------------

////////////////////////////////////////////////////////////
/// class Engine
/// \brief Classe principal respons�vel pelo loop, gerenciamento
/// de eventos e comunica��o entre as demais classes.
/// 
////////////////////////////////////////////////////////////
class Engine
{
public:
    static Window window;    ///< Janela gr�fica 
    static float  deltaTime; ///< Tempo decorrido entre frames

    ////////////////////////////////////////////////////////////
    /// \brief Contrutor padr�o.
    ///
    /// Inicializa vari�veis da classe.
    /// 
    ////////////////////////////////////////////////////////////
    Engine();

    ////////////////////////////////////////////////////////////
    /// \brief Inicia a execu��o do jogo com a entidade principal
    ///
    /// \param entity  Ponteiro para a entidade principal do jogo
    /// \return Retorna um c�digo de status da execu��o (0 em caso de sucesso)
    /// 
    ////////////////////////////////////////////////////////////
    int Run(Scene* scene);

private:
    static Scene* scene; ///< Cena a ser executada
    const char*   title; ///< T�tulo da janela

    ////////////////////////////////////////////////////////////
    /// \brief La�o principal do jogo
    /// O la�o roda enquanto a janela gr�fica estiver aberta
    ///
    /// \return Retorna um c�digo de status da execu��o (0 em caso de sucesso)
    /// 
    ////////////////////////////////////////////////////////////
    int Loop();
};

// ------------------------------------------------------------------------------------------------

#endif
