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
    /// \brief Verifica se um botão do mouse está atualmente pressionado.
    ///
    /// Este método retorna true enquanto o botão do mouse especificado
    /// estiver pressionado.
    ///
    /// \param button O botão do mouse a ser verificado.
    /// \return true se o botão estiver pressionado, false caso contrário.
    /// 
    ////////////////////////////////////////////////////////////
    static bool ButtonPressed(MouseButton button);

    ////////////////////////////////////////////////////////////
    /// \brief Retorna true uma vez quando o botão do mouse é pressionado.
    ///
    /// Este método detecta o evento de pressionamento do botão e retorna
    /// true apenas uma vez durante o ciclo de pressionamento. Subsequentemente,
    /// retornará false até que o botão seja liberado e pressionado novamente.
    ///
    /// \param button O botão do mouse a ser verificado.
    /// \return true uma vez se o botão foi pressionado, false caso contrário.
    /// 
    ////////////////////////////////////////////////////////////
    static bool ButtonDown(MouseButton button);

    ////////////////////////////////////////////////////////////
    /// \brief Obtém a posição atual do mouse em coordenadas globais.
    ///
    /// Este método retorna a posição do cursor do mouse na tela, em relação
    /// às coordenadas globais (geralmente a posição em relação à tela principal).
    ///
    /// \return A posição global do mouse como um vetor de coordenadas (x, y).
    /// 
    ////////////////////////////////////////////////////////////
    static SDL_Point Position();

    ////////////////////////////////////////////////////////////
    /// \brief Define a posição global do cursor do mouse.
    ///
    /// Este método move o cursor do mouse para uma posição específica
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
    SDL_WarpMouseInWindow(nullptr, int(x), int(y)); // Move o cursor para a posição especificada
}

// ------------------------------------------------------------------------------------------------

#endif
