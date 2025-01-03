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
	/// � obrigat�rio implement�-lo nas classes derivadas.
	/// 
	////////////////////////////////////////////////////////////
	virtual void Start() = 0;

	////////////////////////////////////////////////////////////
	/// \brief Atualiza objetos derivados desta classe.
	/// 
	/// M�todo virtual chamado a cada frame para atualizar objetos.
	/// Pode ser implementado pelas classes derivadas.
	/// 
	////////////////////////////////////////////////////////////
	virtual void Update() {};

	////////////////////////////////////////////////////////////
	/// \brief Renderiza o conte�do da cena.
	///
	/// Este m�todo virtual � chamado uma vez a cada frame e �
	/// respons�vel por desenhar todos os elementos visuais da cena.
	/// O conte�do desenhado por este m�todo geralmente representa
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
