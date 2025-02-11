#include "Node.h"

//--------------------------------------------------------------------------------------------------

Node::Node(int row, int column) :
    row{ row },
    column{ column },
    status{ Status::Empty },
    distance{},
    parent{}
{
}

//--------------------------------------------------------------------------------------------------

void Node::Status(::Status status)
{
    this->status = status;

    // Modifica a cor da célula e desenha com base no estado e posição do nó
    if (status != Status::Visited)
    {
        switch (status)
        {
        case Status::None:
        case Status::Empty:
            cell.sprite.SetColor(Color{ 35, 35, 70 });
            break;
        case Status::Obstacle:
            cell.sprite.SetColor(Color::White);
            break;
        case Status::Root:
            cell.sprite.SetColor(Color::Green);
            break;
        case Status::Target:
            cell.sprite.SetColor(Color::Red);
            break;
        case Status::Explored:
            cell.sprite.SetColor(Color::Blue);
            break;
        case Status::Path:
            cell.sprite.SetColor(Color::Magenta);
            break;
        }
        cell.transform.Position(column * cell.transform.GetSize().width, row * cell.transform.GetSize().height);
        cell.Draw();
    }
}

//--------------------------------------------------------------------------------------------------
