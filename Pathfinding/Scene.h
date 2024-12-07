#ifndef QUANTVERSO_SCENE_H
#define QUANTVERSO_SCENE_H

// ------------------------------------------------------------------------------------------------

#include "Window.h"
#include "Engine.h"

// ------------------------------------------------------------------------------------------------

class Scene
{
public:
	virtual ~Scene() = default;

	////////////////////////////////////////////////////////////
	/// \brief Inicializa objetos derivados desta classe.
	/// 
	/// É obrigatório implementá-lo nas classes derivadas.
	/// 
	////////////////////////////////////////////////////////////
	virtual void Start() = 0;

	////////////////////////////////////////////////////////////
	/// \brief Atualiza objetos derivados desta classe.
	/// 
	/// Método virtual chamado a cada frame para atualizar objetos.
	/// Pode ser implementado pelas classes derivadas.
	/// 
	////////////////////////////////////////////////////////////
	virtual void Update() {};

	////////////////////////////////////////////////////////////
	/// \brief Renderiza o conteúdo da cena.
	///
	/// Este método virtual é chamado uma vez a cada frame e é
	/// responsável por desenhar todos os elementos visuais da cena.
	/// O conteúdo desenhado por este método geralmente representa
	/// os elementos principais da cena, backgrounds, ou quaisquer
	/// outros elementos visuais.
	///
	/// Deve ser sobrescrito em classes derivadas para personalizar o desenho.
	///
	////////////////////////////////////////////////////////////
	virtual void Draw() {};

protected:
	inline static Window& window{ Engine::window };
	inline static float&  deltaTime{ Engine::deltaTime };
};

// ------------------------------------------------------------------------------------------------

#endif
