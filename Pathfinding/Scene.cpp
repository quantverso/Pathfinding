#include "Scene.h"
#include "Engine.h"

// ------------------------------------------------------------------------------------------------

Window& Scene::window{ Engine::window };	   ///< Janela gr�fica
float&  Scene::deltaTime{ Engine::deltaTime }; ///< Tempo decorrido entre frames

// ------------------------------------------------------------------------------------------------