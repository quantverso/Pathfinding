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
    std::string title{};             ///< T�tulo da janela
                                     
    int Loop();                      ///< La�o principal
                                     
public:                              
    static sf::RenderWindow* window; ///< Janela gr�fica
    static sf::Event         event;  ///< Eventos da janela
    static Entity*           entity; ///< Aplica��o a ser executada

    Engine();                        ///< Construtor padr�o
    Engine(int width, int height);   ///< Construtor
    ~Engine();                       ///< Destrutor    

    int Run(Entity* entity);         ///< Inicia a execu��o da aplica��o
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
