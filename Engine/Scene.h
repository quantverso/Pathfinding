#ifndef QUANTVERSO_SCENE_H
#define QUANTVERSO_SCENE_H

// ------------------------------------------------------------------------------------------------

#include "Window.h"
#include "Texture.h"
#include "Music.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Point.h"
#include "Polygon.h"
#include <string>
#include <list>
#include <vector>
#include <unordered_map>
#include <concepts>

class Entity;
class Collider;

template<typename T>
concept DerivedEntity = std::derived_from<T, Entity>;

// ------------------------------------------------------------------------------------------------

class Scene
{
public:
	Scene();
	virtual ~Scene();

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
	/// M�todo virtual chamado a cada frame para atualizar a cena.
	/// Pode ser implementado pelas classes derivadas.
	/// 
	////////////////////////////////////////////////////////////
	virtual void Update() {};

	////////////////////////////////////////////////////////////
	/// \brief Desenha todo cont�udo da cena.
	/// 
	/// Chama o m�todo Draw() da cena, Draw() das entidades e
	/// DrawOver() da cena nesta ordem.
	/// 
	////////////////////////////////////////////////////////////
	virtual void Draw();

	///////////////////////////////////////////////////////////
	/// \brief Define o background a partir de uma textura.
	///
	/// \param texture Ponteiro para o objeto `Texture` que ser� utilizado
	/// para definir a textura do background.
	///
	///////////////////////////////////////////////////////////
	void SetBackground(Texture* texture);

	///////////////////////////////////////////////////////////
	/// \brief Define a �rea da viewport.
	///
	/// \param x Coordenada X inicial da viewport.
	/// \param y Coordenada Y inicial da viewport.
	/// \param width Largura da viewport.
	/// \param height Altura da viewport.
	///
	///////////////////////////////////////////////////////////
	void SetViewport(int x, int y, int width, int height);

	////////////////////////////////////////////////////////////
	/// \brief Adiciona um objeto existente � cena.
	///
	/// Se o ID (�nico) for informado, o objeto ser� adicionado
	/// � tabela hash e poder� ser recuperado posteriormente
	/// usando o m�todo FindObject(). O objeto n�o ser� destru�do
	/// pela cena (precisa ser destru�do manualmente).
	///
	/// \tparam T O tipo de objeto a ser instanciado.
	/// 
	/// \param id (Opcional) A chave que identifica a entidade a ser instanciada.
	///
	////////////////////////////////////////////////////////////
	void AddObject(Entity* object, const char* id = nullptr);

	////////////////////////////////////////////////////////////
	/// \brief Atualiza objetos da cena.
	/// 
	/// Chama o m�todo Update() para cada objeto registrado,
	/// atualizando seu estado.
	/// 
	////////////////////////////////////////////////////////////
	void UpdateObjects();

	////////////////////////////////////////////////////////////
	/// \brief Destr�i entidades solicitadas.
	///
	/// Este m�todo � respons�vel por remover ou deletar objetos cujo
	/// m�todo Remove() ou Destroy() foi invocado no frame atual.
	///
	////////////////////////////////////////////////////////////
	void RemoveObjects();
	
	////////////////////////////////////////////////////////////
	/// \brief Ordena os objetos.
	///
	/// Este m�todo ordena os objetos da cena com base na profundidade
	/// `depth` para que sejam renderizados na ordem correta.
	///
	////////////////////////////////////////////////////////////
	void SortObjects();

	///////////////////////////////////////////////////////////
	/// \brief Obt�m o ret�ngulo da �rea da viewport.
	///
	/// \return Refer�ncia constante para o ret�ngulo da viewport.
	///
	///////////////////////////////////////////////////////////
	const Rect& GetViewport() const;

	////////////////////////////////////////////////////////////
	/// \brief Instancia um objeto na cena.
	///
	/// Se o ID (�nico) for informado, o objeto ser� adicionado � tabela hash e
	/// poder� ser recuperado posteriormente usando o m�todo FindObject().
	/// O objeto ser� destru�do automaticamente quando o destrutor da cena for chamado.
	/// 
	/// \param id (Opcional) A chave que identifica a entidade a ser instanciada.
	/// 
	/// \tparam T O tipo de objeto a ser instanciado.
	/// \tparam Args Tipos dos argumentos a serem passado para o construtor do componente.
	/// 
	/// \return Um ponteiro para o objeto do tipo `T`.
	///
	////////////////////////////////////////////////////////////
	template <DerivedEntity T, typename... Args>
	T* CreateObject(const char* id = nullptr, Args&&... args);

	////////////////////////////////////////////////////////////
	/// \brief Encontra um objeto registrado pelo nome e retorna o tipo espec�fico.
	///
	/// Este m�todo gen�rico busca um objeto pelo seu id (chave) na tabela de objetos.
	/// Se o objeto for encontrado, retorna um ponteiro para o tipo derivado.
	///
	/// \tparam T O tipo de entidade esperado.
	/// 
	/// \param id A chave que identifica o objeto a ser buscado.
	/// 
	/// \return Um ponteiro para o tipo `T` se o objeto for encontrado e
	/// corresponder ao tipo; caso contr�rio, retorna `nullptr`.
	///
	////////////////////////////////////////////////////////////
	template<DerivedEntity T>
	T* FindObject(const std::string& id);

protected:
	static Window& window;
	static float&  deltaTime;

	///////////////////////////////////////////////////////////
	/// \brief Define o background a partir de um arquivo.
	///
	/// Este m�todo carrega uma textura a partir de um arquivo especificado e a 
	/// define para o background.
	///
	/// \param file Caminho para o arquivo de textura que ser� carregado e 
	/// utilizado para definir a textura do background.
	/// 
	///////////////////////////////////////////////////////////
	void SetBackground(const char* file);

private:
	friend class Component;

	std::shared_ptr<Texture>				  m_Texture;			 ///< Textura carregada na cena (background)
	Rect									  m_Viewport;			 ///< Viewport da cena
	std::list<Entity*>						  m_Objects;			 ///< Lista de objetos do tipo Entity
	std::unordered_map<std::string, Entity*>  m_ObjectMap;			 ///< Tabela de objetos do tipo Entity
	std::vector<Entity*>					  m_CreatedObjects;		 ///< Vetor de objetos a serem inicializados (pr�ximo frame)
	std::vector<std::list<Entity*>::iterator> m_ObjectsToRemove;     ///< Vetor de objetos a serem destruidos (ao final do frame)
	std::vector<Entity*>					  m_DestructibleObjects; ///< Objetos que ser�o destru�dos no destrutor da cena
	bool									  m_SortObjectsRequest;	 ///< Flag para ordena��o dos objetos
	std::list<Collider*>					  m_Colliders;			 ///< Lista de colisores instanciados
};

// ------------------------------------------------------------------------------------------------

inline void Scene::SortObjects()
{
	m_SortObjectsRequest = true;
}

// ------------------------------------------------------------------------------------------------

inline const Rect& Scene::GetViewport() const
{
	return m_Viewport;
}

// ------------------------------------------------------------------------------------------------

template <DerivedEntity T, typename... Args>
T* Scene::CreateObject(const char* id, Args&&... args)
{
	T* obj{ new T{ std::forward<Args>(args)... } };
	AddObject(obj, id);
	m_DestructibleObjects.push_back(obj);
	return obj;
}

// ------------------------------------------------------------------------------------------------

template<DerivedEntity T>
inline T* Scene::FindObject(const std::string& id)
{
	if (auto it{ m_ObjectMap.find(id) }; it != m_ObjectMap.end())
		return (T*)it->second;

	return nullptr;
}

// ------------------------------------------------------------------------------------------------

#endif
