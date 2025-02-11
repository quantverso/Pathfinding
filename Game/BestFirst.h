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
/// gerenciar nós baseados em uma função heurística.
/// 
////////////////////////////////////////////////////////////
class BestFirst : public Pathfinder
{
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
    /// \brief Método da busca.
    ///
    /// Realiza a busca Best-First no mapa utilizando a função
    /// heurística fornecida.
    ///
    /// \return Ponteiro para o nó objetivo se encontrado,
    /// nullptr durante a busca ou nó raiz se a busca falhar.
    /// 
    ////////////////////////////////////////////////////////////
    const Node* Search();

private:
    inline static double (*h)(const Node* node); ///< Ponteiro para a função heurística

    ////////////////////////////////////////////////////////////
    /// \struct CompareNode
    /// 
    /// \brief Functor para comparar nós na fila de prioridade.
    ///
    /// Utilizado para ordenar a fila de prioridade com base na
    /// função heurística.
    /// 
    ////////////////////////////////////////////////////////////
    struct CompareNode
    {
        bool operator()(Node* a, Node* b)
        {
            return h(a) > h(b);
        }
    };

    std::priority_queue<Node*, std::vector<Node*>, CompareNode> queue; ///< Fila de prioridade

    ////////////////////////////////////////////////////////////
    /// \brief Heurística -> f(n) = (h)n + (g)n
    /// 
    /// \param node Nó atual
    /// 
    /// \return Distância euclidiana até o nó objetivo + custo até o nó raiz
    /// 
    ////////////////////////////////////////////////////////////
    static double Heuristic1(const Node* node);

    ////////////////////////////////////////////////////////////
    /// \brief Heurística -> (fn) = h(n)
    /// 
    /// \param node Nó atual
    /// 
    /// \return Distância euclidiana até o nó objetivo
    /// 
    ////////////////////////////////////////////////////////////
    static double Heuristic2(const Node* node);
};

// ---------------------------------------------------------------------------------------------------------------------

inline double BestFirst::Heuristic1(const Node* node)
{    
    return Heuristic2(node) + node->Distance();
}

// ---------------------------------------------------------------------------------------------------------------------

inline double BestFirst::Heuristic2(const Node* node)
{
    return sqrt(
        (Map::target->column - node->column) *
        (Map::target->column - node->column) +
        (Map::target->row - node->row) *
        (Map::target->row - node->row)
    );
}

// ---------------------------------------------------------------------------------------------------------------------

#endif
