#include "Map.h"
#include "Engine.h"
#include <cmath>
#include <chrono>

// ---------------------------------------------------------------------------------------------------------------------
// Inicialização de membros estáticos

Map::Node* Map::root{};   ///< Nó raiz
Map::Node* Map::target{}; ///< Nó objetivo

// ---------------------------------------------------------------------------------------------------------------------

Map::Map(int divisor)
	: DIVISOR{ divisor },
	ROWS(Engine::Height() / DIVISOR),
	COLUMNS(Engine::Width() / DIVISOR)
{
	// Aloca memória para a matriz
	nodes = new Node * [ROWS];
	for (int i = 0; i < ROWS; ++i) {
		nodes[i] = new Node[COLUMNS];
		for (int j = 0; j < COLUMNS; ++j)
			// placement new para inicializar cada nó e respectivos índices
			new(&nodes[i][j]) Node(i, j);
	}

	// Carrega imagens, texturas e sprites
	cellTexture.loadFromFile("./Resources/img/cell.png");
	cell.setTexture(cellTexture);
	maze.loadFromFile("./Resources/img/maze.jpg");

	// Calcula o tamanho do sprite
	auto cellSize = cellTexture.getSize().x;
	auto cellScale = float(DIVISOR) / cellSize;
	cell.setScale(cellScale, cellScale);
}

// ---------------------------------------------------------------------------------------------------------------------

Map::~Map()
{
	// Destrói a matriz dinâmica
	for (int i = 0; i < ROWS; ++i)
	{
		// Chama o destrutor para cada objeto Node na linha
		for (int j = 0; j < COLUMNS; ++j)
			nodes[i][j].~Node(); // Chama o destrutor manualmente

		delete[] nodes[i]; // Libera a memória da linha
	}
	delete[] nodes; // Libera a memória da matriz
}

// ---------------------------------------------------------------------------------------------------------------------

void Map::Update()
{
	static bool keyPressed{};
	if (!searching)
	{
		// Reseta o mapa
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) {
			if (!keyPressed) {
				Reset();
				keyPressed = true;
			}
		}
		// Carrega o labirinto
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Insert)) {
			if (!keyPressed) {
				setMaze();
				keyPressed = true;
			}
		}
		else if (keyPressed)
			keyPressed = false;

		// Desenha os obstáculos
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			Modify(Status::Obstacle);

		// Define origem e objetivo
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			if (!root)
				Modify(Status::Origin);
			else if (root && !target)
				Modify(Status::Target);

		// Reseta células clicadas
		if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
			Modify(Status::Empty);

		// Desenha o mapa
		Draw();
	}
}

// ---------------------------------------------------------------------------------------------------------------------

void Map::Draw()
{
	for (int i{}; i < ROWS; ++i)
		for (int j{}; j < COLUMNS; ++j)
		{
			// Define a cor da célula do nó raiz (Verde)
			if (&nodes[i][j] == root)
				cell.setColor(sf::Color(sf::Color::Green));

			// Define a cor da célula do nó objetivo (Vermelha)
			else if (&nodes[i][j] == target)
				cell.setColor(sf::Color(sf::Color::Red));

			// Define a cor do sprite com base no estado da célula
			else				
				switch (nodes[i][j].status)
				{
				case Status::Empty:				
					cell.setColor(sf::Color(35, 35, 70));
					break;
				case Status::Obstacle:
					cell.setColor(sf::Color(230, 230, 230));
					break;
				case Status::Visited:
				case Status::Explored:
					cell.setColor(sf::Color(0, 0, 180));
					break;
				case Status::Path:
					cell.setColor(sf::Color::Magenta);
					break;
				}

			// Pula as células com estado diferente de Visitado durante a busca
			if (searching && nodes[i][j].status != Status::Visited)
				continue;

			// Atualiza a posição e desenha o sprite
			cell.setPosition(float(j * DIVISOR), float(i * DIVISOR));
			window->draw(cell);			
		}
	window->display();
}

// ---------------------------------------------------------------------------------------------------------------------

void Map::Modify(Status status)
{
	// Guarda a última posição do mouse e a posição atual
	static struct {
		int x{};
		int y{};
	} current, lastMouse;

	// Pega a posição atual do mouse
	auto currentPosition{ sf::Mouse::getPosition(*window) };
	current.x = currentPosition.x / DIVISOR;
	current.y = currentPosition.y / DIVISOR;

	// Verifica se current.x e current.y pertencem aos índices da matriz
	if (current.x >= 0 && current.x < COLUMNS && current.y >= 0 && current.y < ROWS)
	{
		auto modifyCell = [&](int x, int y)
		{
			if (nodes[y][x].status == Status::Empty || status == Status::Empty)
			{
				nodes[y][x].status = status;

				// Define nó raiz e nó objetivo
				if (status == Status::Origin)
					root = &nodes[y][x];
				else if (status == Status::Target)
					target = &nodes[y][x];

				// Apaga nó raiz e nó objetivo
				else if (status == Status::Empty) {
					if (root == &nodes[y][x] && !target)
						root = nullptr;
					else if (target == &nodes[y][x])
						target = nullptr;
				}
			}
		};

		// Se o tempo entre cliques for curto, desenha uma linha entre os pontos clicados
		if (clock.restart().asSeconds() < 0.1f)
		{
			// Algoritmo de Bresenham para desenhar uma linha entre dois pontos
			int dx{ abs(current.x - lastMouse.x) }, sx{ lastMouse.x < current.x ? 1 : -1 };
			int dy{ -abs(current.y - lastMouse.y) }, sy{ lastMouse.y < current.y ? 1 : -1 };
			int err{ dx + dy }, e2;

			while (lastMouse.x != current.x || lastMouse.y != current.y)
			{
				modifyCell(lastMouse.x, lastMouse.y);
				e2 = 2 * err;
				if (e2 >= dy) {
					err += dy;
					lastMouse.x += sx;
				}
				if (e2 <= dx) {
					err += dx;
					lastMouse.y += sy;
				}
			}
		}
		else {
			// Modifica o nó diretamente se o tempo entre cliques for longo
			modifyCell(current.x, current.y);
		}

		// Atualiza a última posição do mouse para a posição atual
		lastMouse = current;
	}
}


// ---------------------------------------------------------------------------------------------------------------------

void Map::Reset()
{
	for (int i{}; i < ROWS; ++i)
		for (int j{}; j < COLUMNS; ++j) {
			nodes[i][j].status = {};
			nodes[i][j].distance = {};
			nodes[i][j].parent = {};
		}
	root = target = nullptr;
}

// ---------------------------------------------------------------------------------------------------------------------

void Map::setMaze() {
	// Define a tolerância para pixel branco (nó vazio)
	float tolerance{ 100 };

	// Calcula parâmetros para redimensionar imagem na matriz
	auto mazeSize{ maze.getSize() };
	float cellWidth{ mazeSize.x / float(COLUMNS) };
	float cellHeight{ mazeSize.y / float(ROWS) };

	// Define a cor branca para comparação
	sf::Color white(sf::Color::White);

	// Lambda para calcular a distância entre duas cores
	auto colorDistance = [](const sf::Color& color1, const sf::Color& color2)
	{
		float redDiff = float(color1.r - color2.r);
		float greenDiff = float(color1.g - color2.g);
		float blueDiff = float(color1.b - color2.b);
		return std::sqrt(redDiff * redDiff + greenDiff * greenDiff + blueDiff * blueDiff);
	};

	for (int i{}; i < ROWS; i++)
		for (int j{}; j < COLUMNS; j++)
		{
			// Calcula a posição do pixel no centro da célula
			int x{ int(j * cellWidth + cellWidth / 2) };
			int y{ int(i * cellHeight + cellHeight / 2) };

			// Pega a cor do pixel
			sf::Color color = maze.getPixel(x, y);

			// Verifica se a cor do pixel está próxima da cor branca
			if (colorDistance(color, white) <= tolerance)
				nodes[i][j].status = {};
			else
				nodes[i][j].status = Status::Obstacle;

			nodes[i][j].distance = {};
			nodes[i][j].parent = {};
		}
	root = target = nullptr;
}

// ---------------------------------------------------------------------------------------------------------------------
