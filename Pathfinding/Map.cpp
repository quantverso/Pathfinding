#include "Map.h"
#include "Engine.h"

//--------------------------------------------------------------------------------------------------

Node* Map::root{};   ///< Ponteiro para o n� raiz
Node* Map::target{}; ///< Ponteiro para o n� objetivo

//--------------------------------------------------------------------------------------------------

Map::Map(int cellSize) :
	cellSize(cellSize),
	rows(Engine::window.height / cellSize),
	columns(Engine::window.width / cellSize),
	nodesCount(0)
{
	nodes.resize(size_t(rows * columns));

	// Carrega c�lula para desenhar
	Node::cell.material.Add("Resources/Cell.png");
	Node::cell.transform.Size(float(cellSize), float(cellSize));
	for (int i{}; i < nodes.size(); i++)
		nodes[i].Position(i % columns * cellSize, i / columns * cellSize);

	// Imagem da interface
	LoadImage(Status::None, { 33, 33, 33, 233 }, 15, "Resources/Interface.png");

	// Inicializa n�s vazios
	Engine::window.Clear(35, 35, 70);
	for (auto& node : nodes)
		if (node.Status() != Status::None)
		{
			node.Status(Status::Empty);
			nodesCount++;
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
	// Guarda �ltima posi��o e posi��o atual do mouse
	static Vector2i current, lastMouse;

	// Posi��o atual do mouse
	auto mouse{ Mouse::Position() };
	current.x = mouse.x / cellSize;
	current.y = mouse.y / cellSize;

	// Verifica se current.x e current.y pertencem aos �ndices da matriz
	if (current.x >= 0 && current.x < columns && current.y >= 0 && current.y < rows)
	{
		auto modifyNode{ [&](int x, int y) {
			auto& node{ nodes[size_t(y * columns + x)] };
			if (node.Status() == Status::Empty || status == Status::Empty)
			{
				// Muda estado do n�
				if (node.Status() != Status::None)
					node.Status(status);

				// Define n� raiz
				if (status == Status::Root)
					root = &node;

				// Define n� objetivo
				else if (status == Status::Target)
					target = &node;

				// Apaga n� raiz e n� objetivo
				else if (status == Status::Empty)
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
		else // Modifica o n� diretamente se o tempo entre cliques for longo
			modifyNode(current.x, current.y);

		// Atualiza a �ltima posi��o do mouse
		lastMouse = current;
	}
}

//--------------------------------------------------------------------------------------------------

void Map::Reset()
{
	for (auto& node : nodes) {
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
	float cellWidth{ float(img.Size().width) / columns };
	float cellHeight{ float(img.Size().height) / rows };

	for (int i{}; i < rows; i++) {
		for (int j{}; j < columns; j++)
		{
			auto& node{ nodes[size_t(i * columns + j)] };
			if (node.Status() == Status::Empty)
			{
				// Calcula a posi��o do pixel no centro da c�lula
				int x{ int(j * cellWidth + cellWidth / 2) };
				int y{ int(i * cellHeight + cellHeight / 2) };

				// Modifica n� caso a cor do pixel corresponda � cor informada
				if (img.ComparePixelColor(x, y, color, tolerance))
					node.Status(status);
			}
		}
	}
}

//--------------------------------------------------------------------------------------------------

void Map::GetAdjacent(vector<Node*>& adjacent, Node* current) {
	// Calcula �ndice do n�
	int index{ int(current - nodes.data()) };

	// N� acima
	if (index >= columns)
		adjacent.push_back(current - columns);

	// N� � direita
	if (index % columns < (columns - 1))
		adjacent.push_back(current + 1);

	// N� abaixo
	if (index < (nodes.size() - columns))
		adjacent.push_back(current + columns);

	// N� � esquerda
	if (index % columns > 0)
		adjacent.push_back(current - 1);
}

//--------------------------------------------------------------------------------------------------