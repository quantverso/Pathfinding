#ifndef QUANTVERSO_MOUSE_H
#define QUANTVERSO_MOUSE_H

// ------------------------------------------------------------------------------------------------

#include <SDL.h>

// ------------------------------------------------------------------------------------------------

class Mouse
{
public:
    enum MouseButton {
        Left     = SDL_BUTTON_LEFT,     ///< Left mouse button
        Middle   = SDL_BUTTON_MIDDLE,   ///< Middle (wheel) mouse button
        Right    = SDL_BUTTON_RIGHT,    ///< Right mouse button        
        XButton1 = SDL_BUTTON_X1,       ///< Extra mouse button 1
        XButton2 = SDL_BUTTON_X2        ///< Extra mouse button 2
    };

    ////////////////////////////////////////////////////////////
    /// \brief Verifica se um bot�o do mouse est� atualmente pressionado.
    ///
    /// Este m�todo retorna true enquanto o bot�o do mouse especificado
    /// estiver pressionado.
    ///
    /// \param button O bot�o do mouse a ser verificado.
    /// \return true se o bot�o estiver pressionado, false caso contr�rio.
    /// 
    ////////////////////////////////////////////////////////////
    static bool ButtonPressed(MouseButton button);

    ////////////////////////////////////////////////////////////
    /// \brief Retorna true uma vez quando o bot�o do mouse � pressionado.
    ///
    /// Este m�todo detecta o evento de pressionamento do bot�o e retorna
    /// true apenas uma vez durante o ciclo de pressionamento. Subsequentemente,
    /// retornar� false at� que o bot�o seja liberado e pressionado novamente.
    ///
    /// \param button O bot�o do mouse a ser verificado.
    /// \return true uma vez se o bot�o foi pressionado, false caso contr�rio.
    /// 
    ////////////////////////////////////////////////////////////
    static bool ButtonDown(MouseButton button);

    ////////////////////////////////////////////////////////////
    /// \brief Obt�m a posi��o atual do mouse em coordenadas globais.
    ///
    /// Este m�todo retorna a posi��o do cursor do mouse na tela, em rela��o
    /// �s coordenadas globais (geralmente a posi��o em rela��o � tela principal).
    ///
    /// \return A posi��o global do mouse como um vetor de coordenadas (x, y).
    /// 
    ////////////////////////////////////////////////////////////
    static SDL_Point Position();

    ////////////////////////////////////////////////////////////
    /// \brief Define a posi��o global do cursor do mouse.
    ///
    /// Este m�todo move o cursor do mouse para uma posi��o espec�fica
    /// em coordenadas globais (na tela inteira).
    ///
    /// \param x A nova coordenada x do cursor.
    /// \param y A nova coordenada y do cursor.
    /// 
    ////////////////////////////////////////////////////////////
    static void Position(float x, float y);
};

// ------------------------------------------------------------------------------------------------

inline bool Mouse::ButtonPressed(MouseButton button)
{
    return SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(button);
}

// ------------------------------------------------------------------------------------------------

inline bool Mouse::ButtonDown(MouseButton button)
{
    static bool wasPressed[5]{};

    if (ButtonPressed(button)) {
        if (!wasPressed[button - 1])
            return wasPressed[button - 1] = true;
    }
    else
        wasPressed[button - 1] = false;

    return false;
}

// ------------------------------------------------------------------------------------------------

inline SDL_Point Mouse::Position()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    return { x, y };
}

// ------------------------------------------------------------------------------------------------

inline void Mouse::Position(float x, float y)
{
    SDL_WarpMouseInWindow(nullptr, int(x), int(y)); // Move o cursor para a posi��o especificada
}

// ------------------------------------------------------------------------------------------------

#endif
