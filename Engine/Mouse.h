#ifndef QUANTVERSO_MOUSE_H
#define QUANTVERSO_MOUSE_H

// ------------------------------------------------------------------------------------------------

#include "Transformable.h"
#include <bitset>

// ------------------------------------------------------------------------------------------------

class Mouse
{
public:
    enum MouseButton
    {
        Left     = SDL_BUTTON_LEFT,
        Middle   = SDL_BUTTON_MIDDLE,
        Right    = SDL_BUTTON_RIGHT,
        XButton1 = SDL_BUTTON_X1,
        XButton2 = SDL_BUTTON_X2
    };
    using MouseButtonBitset = std::bitset<XButton2 + 1>;

    struct MouseState
    {
        Vector2i position;
        bool     isInViewport;
    };

    ////////////////////////////////////////////////////////////
    /// \brief Verifica se um bot�o do mouse est� atualmente pressionado.
    ///
    /// Este m�todo retorna true enquanto o bot�o do mouse especificado
    /// estiver pressionado.
    ///
    /// \param button O bot�o do mouse a ser verificado.
    /// 
    /// \return true se o bot�o estiver pressionado, false caso contr�rio.
    /// 
    ////////////////////////////////////////////////////////////
    static bool IsButtonPressed(MouseButton button);

    ////////////////////////////////////////////////////////////
    /// \brief Retorna true uma vez quando o bot�o do mouse � pressionado.
    ///
    /// Este m�todo detecta o evento de pressionamento do bot�o e retorna
    /// true apenas uma vez durante o ciclo de pressionamento. Subsequentemente,
    /// retornar� false at� que o bot�o seja liberado e pressionado novamente.
    ///
    /// \param button O bot�o do mouse a ser verificado.
    /// 
    /// \return true uma vez se o bot�o foi pressionado, false caso contr�rio.
    /// 
    ////////////////////////////////////////////////////////////
    static bool IsButtonDown(MouseButton button);

    ////////////////////////////////////////////////////////////
    /// \brief Obt�m a posi��o atual do mouse em coordenadas globais.
    ///
    /// Este m�todo retorna a posi��o do cursor do mouse na tela, em rela��o
    /// �s coordenadas globais (geralmente a posi��o em rela��o � tela principal).
    ///
    /// \return A posi��o global do mouse como um vetor de coordenadas (x, y).
    /// 
    ////////////////////////////////////////////////////////////
    static const Vector2i& GetPosition();
    static const MouseState& GetPosition(const Rect& viewport);

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
    static void SetPosition(float x, float y);

private:
    inline static MouseButtonBitset s_WasPressed;
    inline static MouseState        s_Mouse;
};

// ------------------------------------------------------------------------------------------------

inline bool Mouse::IsButtonPressed(MouseButton button)
{
    return SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(button) ? true : s_WasPressed[button] = false;
}

// ------------------------------------------------------------------------------------------------

inline bool Mouse::IsButtonDown(MouseButton button)
{
    if (IsButtonPressed(button) && !s_WasPressed[button])
        return s_WasPressed[button] = true;

    return false;
}

// ------------------------------------------------------------------------------------------------

inline const Vector2i& Mouse::GetPosition()
{
    SDL_GetMouseState(&s_Mouse.position.x, &s_Mouse.position.y);
    return s_Mouse.position;
}

// ------------------------------------------------------------------------------------------------

inline const Mouse::MouseState& Mouse::GetPosition(const Rect& viewport)
{
    GetPosition();
    s_Mouse.position.x -= viewport.x;
    s_Mouse.position.y -= viewport.y;
    s_Mouse.isInViewport = (
        s_Mouse.position.x >= 0 && s_Mouse.position.x < viewport.w &&
        s_Mouse.position.y >= 0 && s_Mouse.position.y < viewport.h);
    return s_Mouse;
}

// ------------------------------------------------------------------------------------------------

inline void Mouse::SetPosition(float x, float y)
{
    SDL_WarpMouseInWindow(nullptr, int(x), int(y));
}

// ------------------------------------------------------------------------------------------------

#endif
