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
/// busca. As classes derivadas devem implementar o método Search()
///
////////////////////////////////////////////////////////////
class PathFinder
{
private:	
	struct { int x, y;			  ///< Coordenadas para adjacentes
	} const adjacent[4]{ {0, -1}, ///< Nó acima
						 {1, 0},  ///< Nó a direita
						 {0, 1},  ///< Nó abaixo
						 {-1, 0}, ///< Nó a esquerda
	};

protected:
	Map* map;										  ///< Ponteiro para instância do mapa
	std::chrono::steady_clock::time_point start, end; ///< Variáveis para cronometragem
	int visitedNodes{};								  ///< Guarda a quantidade de nós visitados
	int pathSteps{};								  ///< Guarda a quantidade de passos do caminho encontrado

	////////////////////////////////////////////////////////////
	/// \brief Acessa nós adjacentes
	/// 
	/// \param Nó cujos adjacentes serão acessados
	/// 
	/// \return Um vetor contendo os nós adjacentes
	/// 
	////////////////////////////////////////////////////////////
	std::vector<Map::Node*> getAdjacent(const Map::Node* currentNode);

	////////////////////////////////////////////////////////////
	/// \brief Percorre o caminho de volta até o nó raiz
	/// 
	/// \param Nó objetivo
	/// 
	////////////////////////////////////////////////////////////
	void getPath(Map::Node*& current);
	
	////////////////////////////////////////////////////////////
	/// \brief Heurística -> f(n) = (h)n + (g)n
	/// 
	/// \param Um nó
	/// 
	/// \return Distância euclidiana até o nó objetivo + custo até o nó raiz
	/// 
	////////////////////////////////////////////////////////////
	static double Heuristic1(Map::Node* node);

	////////////////////////////////////////////////////////////
	/// \brief Heurística -> (fn) = h(n)
	/// 
	/// \param Um nó
	/// 
	/// \return Distância euclidiana até o nó objetivo
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
	/// \brief Acessa o nó raiz
	/// 
	/// \return Ponteiro para o nó raiz
	/// 
	////////////////////////////////////////////////////////////
	static Map::Node* const getRoot();

	////////////////////////////////////////////////////////////
	/// \brief Acessa o nó objetivo
	/// 
	/// \return Ponteiro para o nó objetivo
	/// 
	////////////////////////////////////////////////////////////
	static Map::Node* const getTarget();

	////////////////////////////////////////////////////////////
	/// \brief Método para atualizar a busca
	/// 
	/// \return Endereço do nó objetivo se encontrado,
	/// nullptr durante a busca ou nó raiz se a busca falhar
	/// 
	////////////////////////////////////////////////////////////
	const virtual Map::Node* Search() = 0;

	////////////////////////////////////////////////////////////
	/// \brief Reseta nós alterados pela busca
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
