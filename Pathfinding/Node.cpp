#include "Node.h"

//--------------------------------------------------------------------------------------------------
// Inicializa��o de membros est�ticos

Entity Node::cell{}; ///< C�lula do mapa

//--------------------------------------------------------------------------------------------------

Node::Node(int row, int column) :
    row(row),
    column(column),
    status(Status::Empty),
    distance(0),
    parent(nullptr)
{
}

//--------------------------------------------------------------------------------------------------

void Node::Status(::Status status)
{
    this->status = status;

    // Modifica a cor da c�lula e desenha com base no estado e posi��o do n�
    if (status != Status::Visited)
    {
        switch (status)
        {
        case Status::None:
        case Status::Empty:
            cell.material.Color(Color{ 35, 35, 70 });
            break;
        case Status::Obstacle:
            cell.material.Color(Color::White);
            break;
        case Status::Root:
            cell.material.Color(Color::Green);
            break;
        case Status::Target:
            cell.material.Color(Color::Red);
            break;
        case Status::Explored:
            cell.material.Color(Color::Blue);
            break;
        case Status::Path:
            cell.material.Color(Color::Magenta);
            break;
        }
        cell.transform.Position(column * cell.width, row * cell.height);
        cell.Draw();
    }
}

//--------------------------------------------------------------------------------------------------
