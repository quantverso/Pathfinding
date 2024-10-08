#ifndef QUANTVERSO_PATHFINDER_H
#define QUANTVERSO_PATHFINDER_H

// ---------------------------------------------------------------------------------------------------------------------

#include "Map.h"
#include <vector>
#include <chrono>

// ---------------------------------------------------------------------------------------------------------------------

////////////////////////////////////////////////////////////
/// \class PathFinder
/// 
/// \brief Classe base para algoritmos de busca.
/// 
/// A classe PathFinder define a interface para algoritmos de
/// busca. As classes derivadas devem implementar o m�todo Search()
///
////////////////////////////////////////////////////////////
class PathFinder
{
private:	
	struct { int x, y;			  ///< Coordenadas para adjacentes
	} const adjacent[4]{ {0, -1}, ///< N� acima
						 {1, 0},  ///< N� a direita
						 {0, 1},  ///< N� abaixo
						 {-1, 0}, ///< N� a esquerda
	};

protected:
	Map* map;										  ///< Ponteiro para inst�ncia do mapa
	std::chrono::steady_clock::time_point start, end; ///< Vari�veis para cronometragem
	int visitedNodes{};								  ///< Guarda a quantidade de n�s visitados
	int pathSteps{};								  ///< Guarda a quantidade de passos do caminho encontrado

	////////////////////////////////////////////////////////////
	/// \brief Acessa n�s adjacentes
	/// 
	/// \param N� cujos adjacentes ser�o acessados
	/// 
	/// \return Um vetor contendo os n�s adjacentes
	/// 
	////////////////////////////////////////////////////////////
	std::vector<Map::Node*> getAdjacent(const Map::Node* currentNode);

	////////////////////////////////////////////////////////////
	/// \brief Percorre o caminho de volta at� o n� raiz
	/// 
	/// \param N� objetivo
	/// 
	////////////////////////////////////////////////////////////
	void getPath(Map::Node*& current);
	
	////////////////////////////////////////////////////////////
	/// \brief Heur�stica -> f(n) = (h)n + (g)n
	/// 
	/// \param Um n�
	/// 
	/// \return Dist�ncia euclidiana at� o n� objetivo + custo at� o n� raiz
	/// 
	////////////////////////////////////////////////////////////
	static double Heuristic1(Map::Node* node);

	////////////////////////////////////////////////////////////
	/// \brief Heur�stica -> (fn) = h(n)
	/// 
	/// \param Um n�
	/// 
	/// \return Dist�ncia euclidiana at� o n� objetivo
	/// 
	////////////////////////////////////////////////////////////
	static double Heuristic2(Map::Node* node);
	
public:
	////////////////////////////////////////////////////////////
	/// \brief Construtor
	///
	/// Inicializa PathFinder com um ponteiro para o mapa da busca.
	///
	/// \param map Ponteiro para o mapa.
	/// 
	////////////////////////////////////////////////////////////
	PathFinder(Map*& map);

	////////////////////////////////////////////////////////////
	/// \brief Destrutor virtual
	///
	////////////////////////////////////////////////////////////
	virtual ~PathFinder();

	////////////////////////////////////////////////////////////
	/// \brief Acessa o n� raiz
	/// 
	/// \return Ponteiro para o n� raiz
	/// 
	////////////////////////////////////////////////////////////
	static Map::Node* const getRoot();

	////////////////////////////////////////////////////////////
	/// \brief Acessa o n� objetivo
	/// 
	/// \return Ponteiro para o n� objetivo
	/// 
	////////////////////////////////////////////////////////////
	static Map::Node* const getTarget();

	////////////////////////////////////////////////////////////
	/// \brief M�todo para atualizar a busca
	/// 
	/// \return Endere�o do n� objetivo se encontrado,
	/// nullptr durante a busca ou n� raiz se a busca falhar
	/// 
	////////////////////////////////////////////////////////////
	const virtual Map::Node* Search() = 0;

	////////////////////////////////////////////////////////////
	/// \brief Reseta n�s alterados pela busca
	///
	////////////////////////////////////////////////////////////
	void Reset();
};

// ---------------------------------------------------------------------------------------------------------------------

inline Map::Node* const PathFinder::getRoot()
{
	return Map::root;
}

// ---------------------------------------------------------------------------------------------------------------------

inline Map::Node* const PathFinder::getTarget()
{
	return Map::target;
}

// ---------------------------------------------------------------------------------------------------------------------

inline double PathFinder::Heuristic1(Map::Node* node)
{
	return sqrt((getTarget()->column - node->column) * (getTarget()->column - node->column) +
		(getTarget()->row - node->row) * (getTarget()->row - node->row)) + node->distance;
}

// ---------------------------------------------------------------------------------------------------------------------

inline double PathFinder::Heuristic2(Map::Node* node)
{
	return sqrt((getTarget()->column - node->column) * (getTarget()->column - node->column) +
		(getTarget()->row - node->row) * (getTarget()->row - node->row));
}

// ---------------------------------------------------------------------------------------------------------------------

#endif
