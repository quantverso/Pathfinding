#ifndef QUANTVERSO_NODE_H
#define QUANTVERSO_NODE_H

//--------------------------------------------------------------------------------------------------

#include "Entity.h"

//--------------------------------------------------------------------------------------------------

enum class Status {
    None,     ///< Fora do espaço de busca
    Empty,    ///< Nó vazio
    Obstacle, ///< Nó que representa um obstáculo
    Root,     ///< Nó raiz (ponto de início da busca)
    Target,   ///< Nó objetivo (alvo da busca)
    Visited,  ///< Nó visitado durante a busca
    Explored, ///< Nó explorado durante a busca
    Path      ///< Nó que faz parte do caminho encontrado
};

//--------------------------------------------------------------------------------------------------

class Node
{
public:
    static Entity cell; ///< Célula do mapa
    const int row;      ///< Linha do nó na matriz
    const int column;   ///< Coluna do nó na matriz

    Node(int row, int column);

    void Status(::Status status);
    void Distance(uint distance);
    void Parent(Node* parent);

    ::Status Status() const;
    uint Distance() const;
    Node* Parent() const;

private:
    ::Status status;   ///< Estado do nó
    uint     distance; ///< Distância até o nó raiz
    Node*    parent;   ///< Nó pai
};

//--------------------------------------------------------------------------------------------------

inline void Node::Distance(uint distance)
{
    this->distance = distance;
}

//--------------------------------------------------------------------------------------------------

inline void Node::Parent(Node* parent)
{
    this->parent = parent;
}

//--------------------------------------------------------------------------------------------------

inline ::Status Node::Status() const
{
    return status;
}

//--------------------------------------------------------------------------------------------------

inline uint Node::Distance() const
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
