#include "Engine.h"
#include "Entity.h"
#include "Clock.h"
#include <sstream>

// ------------------------------------------------------------------------------------------------
// Inicializa��o de membros est�ticos da classe

Window      Engine::window{};    ///< Janela gr�fica
Scene*      Engine::scene{};     ///< Cena a ser executada
float       Engine::deltaTime{}; ///< Tempo decorrido entre frames

// ------------------------------------------------------------------------------------------------

Engine::Engine() :
    title(nullptr)
{
}

// ------------------------------------------------------------------------------------------------

int Engine::Run(Scene* scene)
{
    Engine::scene = scene;

    // Define o t�tulo da janela
    title = typeid(*scene).name() + 6; // Remove o prefixo 'class '

    // Instancia a janela gr�fica
    if (!window.IsOpen())
        window.Create();

    // Inicializa a cena
    scene->Start();

    // Chama o la�o principal
    return Loop();
}

// ------------------------------------------------------------------------------------------------

int Engine::Loop()
{
    try {
        // Vari�veis para mapeamento de tempo e ciclos de processamento
        Clock clock{};
        int   cycles{};
        float elapsedTime{};

        // La�o principal
        while (true)
        {
            // Calcula o tempo decorrido desde o �ltimo frame
            deltaTime = clock.ElapsedTime();

#ifdef _DEBUG
            // Atualiza o t�tulo da janela
            cycles++;
            elapsedTime += deltaTime;
            if (elapsedTime >= 1.f)
            {
                std::stringstream text;
                text << std::fixed;
                text.precision(3);

                text << title << "    |    "
                    << "FPS: " << cycles << "    |    "
                    << "Frame Time: " << deltaTime * 1000 << " (ms)";

                window.Title(text.str().c_str());

                cycles = 0;
                elapsedTime = 0;
            }
#endif
            // Atualiza cena
            scene->Update();

            // Desenha cena
            scene->Draw();

            // Processa eventos da janela
            window.WatchEvents();

            // Responde evento de fechar a janela
            if (window.CheckEvent(window.Quit))
            {
                // Destr�i cena
                delete scene;

                // Fecha janela e sai do loop
                window.Close();
                break;
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Erro: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}

// ------------------------------------------------------------------------------------------------
