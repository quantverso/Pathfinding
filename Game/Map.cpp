#include "Map.h"
#include "Engine.h"

//--------------------------------------------------------------------------------------------------

Map::Map(int cellSize) :
	cellSize{ cellSize },
	rows{ int(Engine::window.GetSize().height / cellSize) },
	columns{ int(Engine::window.GetSize().width / cellSize) },
	validNodes{}
{
	// Instancia os nós
	nodes.reserve(size_t(rows * columns));
	for (int i{}; i < rows; i++)
		for (int j{}; j < columns; j++)
			nodes.emplace_back(Node{ i, j });

	// Carrega célula para desenhar
	Node::cell.sprite.SetTexture("Resources/Cell.png");
	Node::cell.transform.SetSize(float(cellSize), float(cellSize));

	// Carrega imagem da interface
	LoadImage(Status::None, { 33, 33, 33, 233 }, 15, "Resources/Interface.png");

	// Inicializa nós com estado vazio
	Engine::window.Clear(Color(35, 35, 70));
	for (auto& node : nodes)
	{
		if (node.Status() != Status::None)
		{
			node.Status(Status::Empty);
			validNodes++;
		}
	}
}

//--------------------------------------------------------------------------------------------------

Map::~Map()
{
	target = root = nullptr;
}

//--------------------------------------------------------------------------------------------------

void Map::Modify(Status status)
{
	// Guarda última posição e posição atual do mouse
	static Vector2i current, lastMouse;

	// Posição atual do mouse
	auto mouse{ Mouse::GetPosition() };
	current.x = mouse.x / cellSize;
	current.y = mouse.y / cellSize;

	// Verifica se current.x e current.y pertencem aos índices da matriz
	if (current.x >= 0 && current.x < columns && current.y >= 0 && current.y < rows)
	{
		auto modifyNode{ [&](int x, int y)
			{
				auto& node{ nodes[size_t(y * columns + x)] };
				if (node.Status() == Status::Empty || status == Status::Empty)
				{
					// Muda estado do nó
					if (node.Status() != Status::None)
						node.Status(status);

					// Define nó raiz
					if (status == Status::Root)
						root = &node;					
					else if (status == Status::Target) // Define nó objetivo
						target = &node;					
					else if (status == Status::Empty) // Apaga nó raiz e nó objetivo
					{
						if (root == &node && !target)
							root = nullptr;
						else if (target == &node)
							target = nullptr;
					}
				}
			}
		};

		// Se o tempo entre cliques for curto, desenha linha entre os pontos clicados
		if (clock.ElapsedTime() < 0.1f)
		{
			// Algoritmo de Bresenham para desenhar linha entre pontos
			int dx{ abs(current.x - lastMouse.x) }, sx{ lastMouse.x < current.x ? 1 : -1 };
			int dy{ -abs(current.y - lastMouse.y) }, sy{ lastMouse.y < current.y ? 1 : -1 };
			int err{ dx + dy }, e2;

			while (lastMouse.x != current.x || lastMouse.y != current.y)
			{
				modifyNode(lastMouse.x, lastMouse.y);
				e2 = 2 * err;
				if (e2 >= dy)
				{
					err += dy;
					lastMouse.x += sx;
				}

				if (e2 <= dx)
				{
					err += dx;
					lastMouse.y += sy;
				}
			}
		}
		else // Modifica o nó diretamente se o tempo entre cliques for longo
			modifyNode(current.x, current.y);

		// Atualiza a última posição do mouse
		lastMouse = current;
	}
}

//--------------------------------------------------------------------------------------------------

void Map::Reset()
{
	for (auto& node : nodes)
	{
		if (node.Status() == Status::Path ||
			node.Status() == Status::Explored ||
			node.Status() == Status::Visited)
			&node == target ? node.Status(Status::Target) : node.Status(Status::Empty);
		else
			node.Status(node.Status());
	}
}

//--------------------------------------------------------------------------------------------------

void Map::LoadImage(Status status, Color color, int tolerance, const char* file)
{
	// Carrega imagem para desenhar na matriz
	Image img;
	img.Load(file);

	// Calculos para redimensionar imagem na matriz
	float cellWidth{ float(img.GetRect().w) / columns };
	float cellHeight{ float(img.GetRect().h) / rows };

	for (int i{}; i < rows; i++)
	{
		for (int j{}; j < columns; j++)
		{
			auto& node{ nodes[size_t(i * columns + j)] };
			if (node.Status() == Status::Empty)
			{
				// Calcula a posição do pixel no centro da célula
				int x{ int(j * cellWidth + cellWidth / 2) };
				int y{ int(i * cellHeight + cellHeight / 2) };

				// Modifica nó caso a cor do pixel corresponda à cor informada
				if (img.ComparePixelColor(x, y, color, tolerance))
					node.Status(status);
			}
		}
	}
}

//--------------------------------------------------------------------------------------------------

void Map::GetAdjacent(vector<Node*>& adjacent, Node* current)
{
	adjacent.clear();

	// Nó acima
	if (current->column > 0)
		adjacent.push_back(current - columns);

	// Nó à direita
	if (current->row < rows)
		adjacent.push_back(current + 1);

	// Nó abaixo
	if (current->column < columns)
		adjacent.push_back(current + columns);

	// Nó à esquerda
	if (current->row > 0)
		adjacent.push_back(current - 1);
}

//--------------------------------------------------------------------------------------------------
