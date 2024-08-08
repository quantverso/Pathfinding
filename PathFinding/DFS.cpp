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
    // Não vou otimizar esse algoritmo :(
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::End))
        return getRoot();

    // Define a distância e estado do nó
    static int distance{};
    current->distance = distance++;
    current->status = Map::Status::Visited;

    // Desenha o progresso da busca dentro da recursividade
    // Necessário 2 vezes para os sprites não piscarem, não me pergunte o porquê \0/
    for (int i{}; i < 2; i++)
        map->Draw();

    // Verifica se o estado objetivo foi alcançado
    if (current == getTarget())
        return current;

    // Vetor de nós adjacentes
    std::vector<Map::Node*> adjacent = getAdjacent(current);

    // Visita cada nó adjacente
    for (auto& adj : adjacent)
    {
        if (adj->status == Map::Status::Empty || adj->status == Map::Status::Target)
        {
            adj->parent = current;
            auto result = SearchRecursive(adj);    // Chamada recursiva para o nó adjacente
            visitedNodes++;
            if (result)
                return result;
        }        
    }

    // Marca o nó atual como explorado
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
