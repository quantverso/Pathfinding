#ifndef QUANTVERSO_BESTFIRST_H
#define QUANTVERSO_BESTFIRST_H

// ---------------------------------------------------------------------------------------------------------------------

#include "Pathfinder.h"
#include <queue>

// ---------------------------------------------------------------------------------------------------------------------

////////////////////////////////////////////////////////////
/// \class BestFirst
/// \brief Classe para realizar busca Best-First.
/// 
/// A classe BestFirst herda de Pathfinder e implementa a busca
/// Best-First em um mapa. Utiliza uma fila de prioridade para
/// gerenciar n�s baseados em uma fun��o heur�stica.
/// 
////////////////////////////////////////////////////////////
class BestFirst : public Pathfinder
{
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
    /// \brief M�todo da busca.
    ///
    /// Realiza a busca Best-First no mapa utilizando a fun��o
    /// heur�stica fornecida.
    ///
    /// \return Ponteiro para o n� objetivo se encontrado,
    /// nullptr durante a busca ou n� raiz se a busca falhar.
    /// 
    ////////////////////////////////////////////////////////////
    Node* Search();

private:
    static double (*h)(const Node* node); ///< Ponteiro para a fun��o heur�stica

    ////////////////////////////////////////////////////////////
    /// \struct CompareNode
    /// \brief Functor para comparar n�s na fila de prioridade.
    ///
    /// Utilizado para ordenar a fila de prioridade com base na
    /// fun��o heur�stica.
    /// 
    ////////////////////////////////////////////////////////////
    struct CompareNode {
        bool operator()(Node* a, Node* b) {
            return h(a) > h(b);
        }
    };

    std::priority_queue<Node*, std::vector<Node*>, CompareNode> queue; ///< Fila de prioridade

    ////////////////////////////////////////////////////////////
    /// \brief Heur�stica -> f(n) = (h)n + (g)n
    /// 
    /// \param node N� atual
    /// 
    /// \return Dist�ncia euclidiana at� o n� objetivo + custo at� o n� raiz
    /// 
    ////////////////////////////////////////////////////////////
    static double Heuristic1(const Node* node);

    ////////////////////////////////////////////////////////////
    /// \brief Heur�stica -> (fn) = h(n)
    /// 
    /// \param node N� atual
    /// 
    /// \return Dist�ncia euclidiana at� o n� objetivo
    /// 
    ////////////////////////////////////////////////////////////
    static double Heuristic2(const Node* node);
};

// ---------------------------------------------------------------------------------------------------------------------

inline double BestFirst::Heuristic1(const Node* node)
{    
    return Heuristic2(node) + node->Distance() * Node::cell.width;
}

// ---------------------------------------------------------------------------------------------------------------------

inline double BestFirst::Heuristic2(const Node* node)
{
    auto targetPosition{ Map::target->Position() };
    auto nodePosition{ node->Position() };
    return sqrt(
        (targetPosition.x - nodePosition.x) *
        (targetPosition.x - nodePosition.x) +
        (targetPosition.y - nodePosition.y) *
        (targetPosition.y - nodePosition.y)
    );
}

// ---------------------------------------------------------------------------------------------------------------------

#endif