#include "Engine.h"
#include "Entity.h"
#include "Clock.h"
#include <sstream>

// ------------------------------------------------------------------------------------------------
// Inicialização de membros estáticos da classe

Window      Engine::window{};    ///< Janela gráfica
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

    // Define o título da janela
    title = typeid(*scene).name() + 6; // Remove o prefixo 'class '

    // Instancia a janela gráfica
    if (!window.IsOpen())
        window.Create();

    // Inicializa a cena
    scene->Start();

    // Chama o laço principal
    return Loop();
}

// ------------------------------------------------------------------------------------------------

int Engine::Loop()
{
    try {
        // Variáveis para mapeamento de tempo e ciclos de processamento
        Clock clock{};
        int   cycles{};
        float elapsedTime{};

        // Laço principal
        while (true)
        {
            // Calcula o tempo decorrido desde o último frame
            deltaTime = clock.ElapsedTime();

#ifdef _DEBUG
            // Atualiza o título da janela
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
                // Destrói cena
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
