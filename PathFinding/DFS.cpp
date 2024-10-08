#include "DFS.h"
#include <vector>
#include <SFML/Graphics.hpp>

// ---------------------------------------------------------------------------------------------------------------------

DFS::DFS(Map* map) : PathFinder(map)
{
}

// ---------------------------------------------------------------------------------------------------------------------

DFS::~DFS()
{
}

// ---------------------------------------------------------------------------------------------------------------------

Map::Node* DFS::SearchRecursive(Map::Node*& current)
{
    // Hack para sair da recursividade \O/
    // N�o vou otimizar esse algoritmo :(
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::End))
        return getRoot();

    // Define a dist�ncia e estado do n�
    static int distance{};
    current->distance = distance++;
    current->status = Map::Status::Visited;

    // Desenha o progresso da busca dentro da recursividade
    // Necess�rio 2 vezes para os sprites n�o piscarem, n�o me pergunte o porqu� \0/
    for (int i{}; i < 2; i++)
        map->Draw();

    // Verifica se o estado objetivo foi alcan�ado
    if (current == getTarget())
        return current;

    // Vetor de n�s adjacentes
    std::vector<Map::Node*> adjacent = getAdjacent(current);

    // Visita cada n� adjacente
    for (auto& adj : adjacent)
    {
        if (adj->status == Map::Status::Empty || adj->status == Map::Status::Target)
        {
            adj->parent = current;
            auto result = SearchRecursive(adj);    // Chamada recursiva para o n� adjacente
            visitedNodes++;
            if (result)
                return result;
        }        
    }

    // Marca o n� atual como explorado
    current->status = Map::Status::Explored;

    return nullptr;
}

// ---------------------------------------------------------------------------------------------------------------------

Map::Node* DFS::Search()
{
    auto root = getRoot();
    auto result = SearchRecursive(root);
    if (result) {
        getPath(result);
        return result;
    }
    else
        return getRoot();
}

// ---------------------------------------------------------------------------------------------------------------------
