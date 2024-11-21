#ifndef QUANTVERSO_MAP_H
#define QUANTVERSO_MAP_H

//--------------------------------------------------------------------------------------------------

#include "Node.h"
#include "Clock.h"
#include <vector>
#include <string>
using std::vector;

class Pathfinder;

//--------------------------------------------------------------------------------------------------

class Map
{
public:
    inline static Node* root;   ///< Ponteiro para o nó raiz
    inline static Node* target; ///< Ponteiro para o nó objetivo

    Map(int cellSize);
    ~Map();
    void Modify(Status status);
    void Reset();
    void LoadImage(Status status, Color color, int tolerance, const char* file);
    void GetAdjacent(vector<Node*>& adjacent, Node* current);

    int Size() const;

private:
    const int	 cellSize;   ///< Tamanho da célula
    const int	 rows;       ///< Linhas
    const int	 columns;    ///< Colunas
    vector<Node> nodes;      ///< Vetor de nós
    int          validNodes; ///< Quantidade de nós válidos
    Clock		 clock;      ///< Relógio
};

//--------------------------------------------------------------------------------------------------

inline int Map::Size() const
{
    return validNodes;
}

//--------------------------------------------------------------------------------------------------

#endif
