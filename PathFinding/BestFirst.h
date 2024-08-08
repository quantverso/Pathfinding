#ifndef QUANTVERSO_BESTFIRST_H
#define QUANTVERSO_BESTFIRST_H

// ---------------------------------------------------------------------------------------------------------------------

#include "PathFinder.h"
#include <queue>

// ---------------------------------------------------------------------------------------------------------------------

////////////////////////////////////////////////////////////
/// \class BestFirst
/// \brief Classe para realizar busca Best-First.
/// 
/// A classe BestFirst herda de PathFinder e implementa a busca
/// Best-First em um mapa. Utiliza uma fila de prioridade para
/// gerenciar nós baseados em uma função heurística.
/// 
////////////////////////////////////////////////////////////
class BestFirst : public PathFinder {
private:
    static double (*h)(Map::Node*); ///< Ponteiro para a função heurística

    ////////////////////////////////////////////////////////////
    /// \struct CompareNode
    /// \brief Functor para comparar nós na fila de prioridade.
    ///
    /// Utilizado para ordenar a fila de prioridade com base na
    /// função heurística.
    /// 
    ////////////////////////////////////////////////////////////
    struct CompareNode {
        bool operator()(Map::Node* a, Map::Node* b) {
            return h(a) > h(b); ///< Ordena nós de acordo com o valor da função heurística
        }
    };

    std::priority_queue<Map::Node*, std::vector<Map::Node*>, CompareNode> queue; ///< Fila de prioridade para nós

public:
    ////////////////////////////////////////////////////////////
    /// \brief Construtor.
    ///
    /// Inicializa a classe BestFirst com um mapa e configura a
    /// função heurística.
    ///
    /// \param map Ponteiro para o mapa onde a busca será realizada.
    /// \param cost Flag para definir se o custo será usado na heurística
    /// -> true: considera o custo; false: não considera o custo.
    /// 
    ////////////////////////////////////////////////////////////
    BestFirst(Map* map, bool cost);

    ////////////////////////////////////////////////////////////
    /// \brief Destrutor.
    ///
    ////////////////////////////////////////////////////////////
    ~BestFirst();

    ////////////////////////////////////////////////////////////
    /// \brief Método da busca.
    ///
    /// Realiza a busca Best-First no mapa utilizando a função
    /// heurística fornecida.
    ///
    /// \return Ponteiro para o nó objetivo se encontrado,
    /// nullptr durante a busca ou nó raiz se a busca falhar.
    /// 
    ////////////////////////////////////////////////////////////
    Map::Node* Search();
};

// ---------------------------------------------------------------------------------------------------------------------

#endif
