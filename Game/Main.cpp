#include "Engine.h"
#include "Scene.h"
#include "Map.h"
#include "Node.h"
#include "BFS.h"
#include "BestFirst.h"
#include "DFS.h"
#include <memory>
#include <string>
#include <sstream>

//--------------------------------------------------------------------------------------------------

class Pathfinding : public Scene
{
public:
    void Start();
    void Update();
    void Draw();

private:
    std::unique_ptr<Map>		map;			 ///< Mapa de busca
    std::unique_ptr<Pathfinder> pathfinder;		 ///< Ponteiro para algoritmos de busca
	Texture						interface;		 ///< Textura da interface
	Text						text;			 ///< Textos da interface
	std::string					selected{ " " }; ///< Algoritmo de busca selecionado
	int							cellSize{ 11 };	 ///< Tamanho de cada célula
	int							count{};		 ///< Contador de ciclos para controle de renderização
};

//--------------------------------------------------------------------------------------------------

void Pathfinding::Start()
{
    // Carrega textura e fonte da interface
	interface.Load("Resources/Interface.png");
	text.Load("Resources/jetbrains.ttf", 15);
	text.SetColor(Color::White);

	// Instancia o mapa de busca
	map = std::make_unique<Map>(cellSize);
}

//--------------------------------------------------------------------------------------------------

void Pathfinding::Update()
{
	// Modifica o mapa com o mouse
	if (Mouse::IsButtonPressed(Mouse::Left))
		map->Modify(Status::Obstacle);
	else if (Mouse::IsButtonDown(Mouse::Right))
	{
		if (!map->root)
			map->Modify(Status::Root);
		else if (!map->target)
			map->Modify(Status::Target);
	}

	if (Mouse::IsButtonPressed(Mouse::Middle))
		map->Modify(Status::Empty);

	// Instancia o algoritmo de busca selecionado
	if (!pathfinder) {
		if (map->target)
		{
			// BFS
			if (Keyboard::IsKeyDown(Keyboard::Num1))
			{
				pathfinder = std::make_unique<BFS>(map.get());
				selected = "BFS";
			}

			// A*
			if (Keyboard::IsKeyDown(Keyboard::Num2))
			{
				pathfinder = std::make_unique<BestFirst>(map.get(), true);
				selected = "A*";
			}

			// Busca gulosa
			if (Keyboard::IsKeyDown(Keyboard::Num3))
			{
				pathfinder = std::make_unique<BestFirst>(map.get(), false);
				selected = "Busca Gulosa";
			}

			// DFS
#ifdef NDEBUG
			if (Keyboard::KeyDown(Keyboard::Num0) && cellSize >= 11)
			{
				pathfinder = std::make_unique<DFS>(map.get(), this);
				selected = "DFS";
			}
#endif
		}
	}
	// Processa a busca do algoritmo selecionado
	else if (pathfinder->Search() || Keyboard::IsKeyPressed(Keyboard::End) || Keyboard::IsKeyPressed(Keyboard::Delete))
		pathfinder.reset();

	// Limpa o mapa
	if (Keyboard::IsKeyDown(Keyboard::Delete))
		map.reset();

	// Carrega o labirinto
	if (Keyboard::IsKeyDown(Keyboard::Insert))
		map->LoadImage(Status::Obstacle, Color::Black, 35, "Resources/maze.jpg");

	// Controla o tamanho das células
	if (Keyboard::IsKeyDown(Keyboard::Up) && cellSize < 20)
	{
		cellSize++;

		map.reset();
	}
	else if (Keyboard::IsKeyDown(Keyboard::Down) && cellSize > 2)
	{
		cellSize--;

		map.reset();
	}

	// Cria uma nova instância do mapa
	if (!map)
	{	
		pathfinder.reset();
		map = std::make_unique<Map>(cellSize);
	}
}

//--------------------------------------------------------------------------------------------------

void Pathfinding::Draw()
{
	// Quantidade de ciclos necessários para a renderização
	const int cyclesToRender{ int(29 / std::pow(cellSize, 1.5f)) + 1 };

	// Desenha a interface e textos
	if (count % size_t(cyclesToRender * 50) == 0)
	{
		// Dimensões da janela
		auto windowSize{ window.GetSize() };

		// Desenha a interface
		window.Draw(&interface);

		// Busca selecionada
		text.SetSize(windowSize.width / 85, windowSize.height / 29);
		text.SetString(selected);
		text.Position(int(windowSize.centerX) - text.GetRect().w / 2, 3);
		window.Draw(&text);

		// Nós visitados
		text.SetSize(windowSize.width / 128, windowSize.height / 36);
		text.SetString("Nós visitados " + std::to_string(Pathfinder::visited));
		text.Position(int(windowSize.width / 42.666f), int(windowSize.height * 0.9625f));
		window.Draw(&text);

		// Tempo decorrido da busca
		std::stringstream time{};
		time << std::fixed;
		time.precision(3);
		time << (pathfinder ? Pathfinder::clock.Count() : pathfinder->timeElapsed);
		text.SetSize(windowSize.width / 128, windowSize.height / 36);
		text.SetString("Tempo " + time.str());
		text.Position(int(windowSize.width / 4.266f), int(windowSize.height * 0.9625f));
		window.Draw(&text);

		// Distância do caminho encontrado
		text.SetSize(windowSize.width / 128, windowSize.height / 36);
		text.SetString("Distância " + std::to_string(map->target ? map->target->Distance() : 0));
		text.Position(int(windowSize.width / 2.566f), int(windowSize.height * 0.9625f));
		window.Draw(&text);

		// Quantidade de nós
		text.SetSize(windowSize.width / 128, windowSize.height / 36);
		text.SetString("Nós " + std::to_string(map->Size()));
		text.Position(int(windowSize.width / 1.8f), int(windowSize.height * 0.9625f));
		window.Draw(&text);

		// Reseta o contador de ciclos
		count = 0;
	}

	// Renderiza com base na quantidade de ciclos calculada em cyclesToRender
	if (count++ % cyclesToRender == 0)
		window.Display();
}

//--------------------------------------------------------------------------------------------------

int main(int argc, char** argv)
{
    Engine::window.SetSize(1280, 720);
	Engine::window.SetTitle("Pathfinder");
    Engine::Run(new Pathfinding);

	return 0;
}

//--------------------------------------------------------------------------------------------------
