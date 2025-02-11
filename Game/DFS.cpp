#include "DFS.h"
#include "Scene.h"
#include <vector>

// ---------------------------------------------------------------------------------------------------------------------

DFS::DFS(Map* map, Scene* pathfinding) :
    Pathfinder{ map },
    pathfinding{ pathfinding }
{
}

// ---------------------------------------------------------------------------------------------------------------------

Node* DFS::SearchRecursive(Node*& current)
{
    // Define a dist�ncia e estado do n�
    static int distance;
    current->Distance(distance++);

    // Verifica se o estado objetivo foi alcan�ado
    if (current == map->target)
        return current;

    // Marca o n� como explorado
    if (current->Status() != Status::Root)
        current->Status(Status::Explored);

    // Desenha o progresso da busca dentro da recursividade
    pathfinding->Draw();

    // Acessa os n�s adjacentes
    map->GetAdjacent(adjacent, current);

    // Visita cada n� adjacente
    for (auto& adj : adjacent)
    {
        if (adj->Status() == Status::Empty || adj->Status() == Status::Target)
        {
            adj->Parent(current);
            auto result{ SearchRecursive(adj) }; // Chamada recursiva para o n� adjacente
            visited++;
            if (result)
                return result;
        }
    }

    return nullptr;
}

// ---------------------------------------------------------------------------------------------------------------------

const Node* DFS::Search()
{
    auto result{ SearchRecursive(map->root) };
    if (result)
    {
        GetPath(result);
        return result;
    }
    else
        return map->root;
}

// ---------------------------------------------------------------------------------------------------------------------
