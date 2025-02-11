#ifndef QUANTVERSO_NODE_H
#define QUANTVERSO_NODE_H

//--------------------------------------------------------------------------------------------------

#include "Entity.h"

//--------------------------------------------------------------------------------------------------

enum class Status
{
    None,     ///< Fora do espa�o de busca
    Empty,    ///< N� vazio
    Obstacle, ///< N� que representa um obst�culo
    Root,     ///< N� raiz (ponto de in�cio da busca)
    Target,   ///< N� objetivo (alvo da busca)
    Visited,  ///< N� visitado durante a busca
    Explored, ///< N� explorado durante a busca
    Path      ///< N� que faz parte do caminho encontrado
};

//--------------------------------------------------------------------------------------------------

class Node
{
public:
    inline static Entity cell;   ///< C�lula do mapa
    const int            row;    ///< Linha do n� na matriz
    const int            column; ///< Coluna do n� na matriz

    Node(int row, int column);

    void Status(::Status status);
    void Distance(Uint32 distance);
    void Parent(Node* parent);

    const ::Status Status() const;
    const Uint32 Distance() const;
    Node* Parent() const;

private:
    ::Status status;   ///< Estado do n�
    Uint32   distance; ///< Dist�ncia at� o n� raiz
    Node*    parent;   ///< N� pai
};

//--------------------------------------------------------------------------------------------------

inline void Node::Distance(Uint32 distance)
{
    this->distance = distance;
}

//--------------------------------------------------------------------------------------------------

inline void Node::Parent(Node* parent)
{
    this->parent = parent;
}

//--------------------------------------------------------------------------------------------------

inline const ::Status Node::Status() const
{
    return status;
}

//--------------------------------------------------------------------------------------------------

inline const Uint32 Node::Distance() const
{
    return distance;
}

//--------------------------------------------------------------------------------------------------

inline Node* Node::Parent() const
{
    return parent;
}

//--------------------------------------------------------------------------------------------------

#endif
