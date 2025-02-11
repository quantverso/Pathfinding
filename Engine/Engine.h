#ifndef QUANTVERSO_ENGINE_H
#define QUANTVERSO_ENGINE_H

// ------------------------------------------------------------------------------------------------

#include "Window.h"

class Scene;

// ------------------------------------------------------------------------------------------------

////////////////////////////////////////////////////////////
/// class Engine
/// \brief Classe respons�vel pelo gerenciamento, atualiza��o e
/// renderiza��o do cena, janela e tempo do jogo.
/// 
////////////////////////////////////////////////////////////
class Engine
{
public:
    inline static Window window;    ///< Janela gr�fica 
    inline static float  deltaTime; ///< Tempo decorrido do �ltimo frame

    ////////////////////////////////////////////////////////////
    /// \brief Carrega uma cena na Engine.
    /// 
    /// Este m�todo inicia o loop da Engine com a cena fornecida quando chamado pela primeira vez.
    /// Caso j� exista uma cena anterior, ela ser� destru�da e substitu�da pela nova cena.
    /// 
    /// \param scene Ponteiro para o objeto da cena do jogo a ser carregada.
    /// 
    /// \note Este m�todo invoca `Loop()` para iniciar o loop principal de execu��o do jogo,
    /// quando chamado pela primeira vez.
    /// 
    /// \warning Ap�s o m�todo ser executado, se uma cena anterior existia,
    /// ela ser� deletada da mem�ria e substitu�da pela cena atual.
    /// 
    ////////////////////////////////////////////////////////////
    static void Run(Scene* scene);

private:
    inline static Scene* s_Scene; ///< Cena atual

    ////////////////////////////////////////////////////////////
    /// \brief La�o principal do jogo.
    /// 
    /// O la�o roda enquanto a janela gr�fica estiver aberta.
    /// 
    ////////////////////////////////////////////////////////////
    static void Loop();
};

// ------------------------------------------------------------------------------------------------

#endif
