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
/// gerenciar n�s baseados em uma fun��o heur�stica.
/// 
////////////////////////////////////////////////////////////
class BestFirst : public PathFinder {
private:
    static double (*h)(Map::Node*); ///< Ponteiro para a fun��o heur�stica

    ////////////////////////////////////////////////////////////
    /// \struct CompareNode
    /// \brief Functor para comparar n�s na fila de prioridade.
    ///
    /// Utilizado para ordenar a fila de prioridade com base na
    /// fun��o heur�stica.
    /// 
    ////////////////////////////////////////////////////////////
    struct CompareNode {
        bool operator()(Map::Node* a, Map::Node* b) {
            return h(a) > h(b); ///< Ordena n�s de acordo com o valor da fun��o heur�stica
        }
    };

    std::priority_queue<Map::Node*, std::vector<Map::Node*>, CompareNode> queue; ///< Fila de prioridade para n�s

public:
    ////////////////////////////////////////////////////////////
    /// \brief Construtor.
    ///
    /// Inicializa a classe BestFirst com um mapa e configura a
    /// fun��o heur�stica.
    ///
    /// \param map Ponteiro para o mapa onde a busca ser� realizada.
    /// \param cost Flag para definir se o custo ser� usado na heur�stica
    /// -> true: considera o custo; false: n�o considera o custo.
    /// 
    ////////////////////////////////////////////////////////////
    BestFirst(Map* map, bool cost);

    ////////////////////////////////////////////////////////////
    /// \brief Destrutor.
    ///
    ////////////////////////////////////////////////////////////
    ~BestFirst();

    ////////////////////////////////////////////////////////////
    /// \brief M�todo da busca.
    ///
    /// Realiza a busca Best-First no mapa utilizando a fun��o
    /// heur�stica fornecida.
    ///
    /// \return Ponteiro para o n� objetivo se encontrado,
    /// nullptr durante a busca ou n� raiz se a busca falhar.
    /// 
    ////////////////////////////////////////////////////////////
    Map::Node* Search();
};

// ---------------------------------------------------------------------------------------------------------------------

#endif
