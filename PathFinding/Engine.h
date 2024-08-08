#ifndef QUANTVERSO_ENGINE_H
#define QUANTVERSO_ENGINE_H

// ---------------------------------------------------------------------------------------------------------------------

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include <string>

// ---------------------------------------------------------------------------------------------------------------------

class Engine
{
private:    
    static int width;                ///< Largura da janela
    static int height;               ///< Altura da janela
    std::string title{};             ///< Título da janela
                                     
    int Loop();                      ///< Laço principal
                                     
public:                              
    static sf::RenderWindow* window; ///< Janela gráfica
    static sf::Event         event;  ///< Eventos da janela
    static Entity*           entity; ///< Aplicação a ser executada

    Engine();                        ///< Construtor padrão
    Engine(int width, int height);   ///< Construtor
    ~Engine();                       ///< Destrutor    

    int Run(Entity* entity);         ///< Inicia a execução da aplicação
    static const int Width();        ///< Retorna a largura da janela
    static const int Height();       ///< Retorna a altura da janela
};

// ---------------------------------------------------------------------------------------------------------------------

inline const int Engine::Width()
{
    return width;
}

// ---------------------------------------------------------------------------------------------------------------------

inline const int Engine::Height()
{
    return height;
}

// ---------------------------------------------------------------------------------------------------------------------

#endif
