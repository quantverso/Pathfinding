#ifndef QUANTVERSO_BFS_H
#define QUANTVERSO_BFS_H

// ---------------------------------------------------------------------------------------------------------------------

#include "PathFinder.h"
#include <queue>

// ---------------------------------------------------------------------------------------------------------------------

////////////////////////////////////////////////////////////
/// \class BFS
/// \brief Classe para realizar busca em largura (BFS).
///
/// A classe BFS herda de PathFinder e implementa a busca em
/// largura em um mapa. Utiliza uma fila (FIFO) para gerenciar
/// os nós a serem visitados.
/// 
////////////////////////////////////////////////////////////
class BFS : public PathFinder {
private:
    std::queue<Map::Node*> queue; ///< Fila FIFO para gerenciar nós a serem visitados

public:
    ////////////////////////////////////////////////////////////
    /// \brief Construtor.
    ///
    /// Inicializa a classe BFS com um mapa.
    ///
    /// \param map Ponteiro para o mapa onde a busca será realizada.
    /// 
    ////////////////////////////////////////////////////////////
    BFS(Map* map);

    ////////////////////////////////////////////////////////////
    /// \brief Destrutor.
    ///
    ////////////////////////////////////////////////////////////
    ~BFS();

    ////////////////////////////////////////////////////////////
    /// \brief Método da busca.
    ///
    /// Realiza a busca em largura no mapa.
    ///
    /// \return Ponteiro para o nó objetivo se encontrado,
    /// nullptr durante a busca ou nó raiz se a busca falhar.
    /// 
    ////////////////////////////////////////////////////////////
    Map::Node* Search();
};

// ---------------------------------------------------------------------------------------------------------------------

#endif
