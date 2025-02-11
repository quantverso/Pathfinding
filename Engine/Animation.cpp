#include "Animation.h"
#include "Entity.h"
#include <limits>

// ---------------------------------------------------------------------------------------------------------------------

Animation::Animation(Entity* entity, const char* file) :
    Component{ entity }
{
    entity->sprite.SetTexture(file);
}

// ---------------------------------------------------------------------------------------------------------------------

Animation::Animation(Entity* entity, Texture* texture) :
    Component{ entity }
{
    entity->sprite.SetTexture(texture);
}

// ---------------------------------------------------------------------------------------------------------------------

void Animation::Add(unsigned id, std::vector<Rect> sequence, bool loop, bool continuous)
{
    m_RectMap.emplace(id, RectVector{ std::move(sequence), continuous, loop });
    entity->sprite.SetRect(sequence.front());
    entity->transform.SetSize(float(sequence.front().w), float(sequence.front().h));
}

// ---------------------------------------------------------------------------------------------------------------------

void Animation::Add(unsigned id, Rect rect)
{
    Add(id, std::vector<Rect>{ rect }, false, false);
}

// ---------------------------------------------------------------------------------------------------------------------

bool Animation::Run(unsigned id, float frameTime)
{
    static Clock       clock;            ///< Rel�gio para controle de tempo de exibi��o dos quadros.
    static RectVector* currentAnimation; ///< Ponteiro para a anima��o atualmente selecionada.
    static int         index;            ///< �ndice do quadro atual.
    static unsigned    lastIndex;        ///< �ltimo �ndice usado (para anima��es cont�nuas).
    static unsigned    currentId{ std::numeric_limits<unsigned>::max() }; ///< ID da anima��o atual.

    if (currentId != id)
    {
        auto sequence{ m_RectMap.find(id) };

        if (sequence != m_RectMap.end())
        {
            currentAnimation = &sequence->second;
            currentId = id;

            // Se for s� um quadro, defini��o ocorre somente uma vez
            if (currentAnimation->size() == 1)
            {
                entity->sprite.SetRect((*currentAnimation)[0]);
                index = -1;
                return true;
            }

            // Reinicia o �ndice dependendo da continuidade da anima��o
            if (!currentAnimation->continuous || currentAnimation->size() <= lastIndex)
                index = 0;
            else
                index = lastIndex;

            auto& rect{ (*currentAnimation)[index % currentAnimation->size()] };
            entity->sprite.SetRect(rect);
            entity->transform.SetSize(float(rect.w), float(rect.h));
        }
        else
        {
            std::cerr << "ID da animacao invalido!\n";
            return true;
        }
    }

    if (index >= 0)
    {
        if (clock.Count() * 1000 >= frameTime)
        {
            if (index >= currentAnimation->size())
            {
                if (currentAnimation->loop) // Reseta o ind�ce se estiver em loop
                    index = 0;
                else
                    return false; // Retorna false se n�o estiver em loop e chegar ao �ltimo quadro
            }

            if (index < currentAnimation->size())
            {
                entity->sprite.SetRect((*currentAnimation)[index++]);

                // Salva o �ltimo �ndice se a anima��o for cont�nua
                if (currentAnimation->continuous)
                    lastIndex = index;

                clock.Reset();
            }
        }
    }

    return true;
}

// ---------------------------------------------------------------------------------------------------------------------
