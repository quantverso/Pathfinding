#ifndef QUANTVERSO_MAP_H
#define QUANTVERSO_MAP_H

//--------------------------------------------------------------------------------------------------

#include "Scene.h"
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
    static Node* root;   ///< Ponteiro para o n� raiz
    static Node* target; ///< Pointeiro para o n� objetivo

    Map(int cellSize);
    ~Map();
    void Modify(Status status);    
    void Reset();
    void LoadImage(Status status, Color color, int tolerance, const char* file);
    void GetAdjacent(vector<Node*>& adjacent, Node* current);
    int Size();

private:
    const int	 cellSize;   ///< Tamanho da c�lula
    const int	 rows;       ///< Linhas
    const int	 columns;    ///< Colunas
    vector<Node> nodes;      ///< Vetor de n�s
    int          nodesCount; ///< Quantidade de n�s v�lidos
    Clock		 clock;      ///< Rel�gio
};

//--------------------------------------------------------------------------------------------------

inline int Map::Size()
{
    return nodesCount;
}

//--------------------------------------------------------------------------------------------------

#endif