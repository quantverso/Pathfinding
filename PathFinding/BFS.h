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
/// os n�s a serem visitados.
/// 
////////////////////////////////////////////////////////////
class BFS : public PathFinder {
private:
    std::queue<Map::Node*> queue; ///< Fila FIFO para gerenciar n�s a serem visitados

public:
    ////////////////////////////////////////////////////////////
    /// \brief Construtor.
    ///
    /// Inicializa a classe BFS com um mapa.
    ///
    /// \param map Ponteiro para o mapa onde a busca ser� realizada.
    /// 
    ////////////////////////////////////////////////////////////
    BFS(Map* map);

    ////////////////////////////////////////////////////////////
    /// \brief Destrutor.
    ///
    ////////////////////////////////////////////////////////////
    ~BFS();

    ////////////////////////////////////////////////////////////
    /// \brief M�todo da busca.
    ///
    /// Realiza a busca em largura no mapa.
    ///
    /// \return Ponteiro para o n� objetivo se encontrado,
    /// nullptr durante a busca ou n� raiz se a busca falhar.
    /// 
    ////////////////////////////////////////////////////////////
    Map::Node* Search();
};

// ---------------------------------------------------------------------------------------------------------------------

#endif
