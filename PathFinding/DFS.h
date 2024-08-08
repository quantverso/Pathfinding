#ifndef QUANTVERSO_DFS_H
#define QUANTVERSO_DFS_H

// ---------------------------------------------------------------------------------------------------------------------

#include "PathFinder.h"

// ---------------------------------------------------------------------------------------------------------------------

////////////////////////////////////////////////////////////
/// \class DFS
/// \brief Classe para realizar busca em profundidade (DFS).
///
/// A classe DFS herda de PathFinder e implementa a busca em
/// profundidade em um mapa.
/// 
////////////////////////////////////////////////////////////
class DFS : public PathFinder {
public:
    ////////////////////////////////////////////////////////////
    /// \brief Construtor.
    ///
    /// Inicializa a classe DFS com um mapa.
    ///
    /// \param map Ponteiro para o mapa onde a busca será realizada.
    /// 
    ////////////////////////////////////////////////////////////
    DFS(Map* map);

    ////////////////////////////////////////////////////////////
    /// \brief Destrutor.
    ///
    ////////////////////////////////////////////////////////////
    ~DFS();

    ////////////////////////////////////////////////////////////
    /// \brief Método da busca.
    ///
    /// Realiza a busca em profundidade no mapa.
    ///
    /// \return Ponteiro para o nó objetivo se encontrado ou
    /// nó raiz se a busca falhar.
    /// 
    ////////////////////////////////////////////////////////////
    Map::Node* Search();

    ////////////////////////////////////////////////////////////
    /// \brief Método recursivo da busca em profundidade.
    ///
    /// Realiza a busca em profundidade de forma recursiva.
    ///
    /// \param current Ponteiro para o nó atual durante a busca.
    ///
    /// \return Ponteiro para o nó objetivo se encontrado,
    /// nullptr se a busca falhar.
    /// 
    ////////////////////////////////////////////////////////////
    Map::Node* SearchRecursive(Map::Node*& current);
};

// ---------------------------------------------------------------------------------------------------------------------

#endif
