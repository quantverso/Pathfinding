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
	text.Color(Color::White);
}

//--------------------------------------------------------------------------------------------------

void Pathfinding::Update()
{
	// Modifica o mapa com o mouse
	if (Mouse::ButtonPressed(Mouse::Left))
		map->Modify(Status::Obstacle);
	else if (Mouse::ButtonDown(Mouse::Right))
	{
		if (!map->root)
			map->Modify(Status::Root);
		else if (!map->target)
			map->Modify(Status::Target);
	}
	if (Mouse::ButtonPressed(Mouse::Middle))
		map->Modify(Status::Empty);

	// Instancia o algoritmo de busca selecionado
	if (!pathfinder) {
		if (map->target)
		{
			// BFS
			if (Keyboard::KeyDown(Keyboard::Num1))
			{
				pathfinder = std::make_unique<BFS>(map.get());
				selected = "BFS";
			}

			// A*
			if (Keyboard::KeyDown(Keyboard::Num2))
			{
				pathfinder = std::make_unique<BestFirst>(map.get(), true);
				selected = "A*";
			}

			// Busca gulosa
			if (Keyboard::KeyDown(Keyboard::Num3))
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
	else if (pathfinder->Search() ||
		Keyboard::KeyPressed(Keyboard::End) ||
		Keyboard::KeyPressed(Keyboard::Delete))
		pathfinder.reset();

	// Limpa o mapa
	if (Keyboard::KeyDown(Keyboard::Delete))
		map.reset();

	// Carrega o labirinto
	if (Keyboard::KeyDown(Keyboard::Insert))
		map->LoadImage(Status::Obstacle, Color::Black, 35, "Resources/maze.jpg");

	// Controla o tamanho das células
	if (Keyboard::KeyDown(Keyboard::Up))
	{
		if (cellSize < 20)
			cellSize++;
		map.reset();
	}
	else if (Keyboard::KeyDown(Keyboard::Down))
	{
		if (cellSize > 2)
			cellSize--;
		map.reset();
	}

	// Instancia o mapa
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
	int cyclesToRender{ int(29 / std::pow(cellSize, 1.5f)) + 1 };

	// Desenha a interface e textos
	if (count % size_t(cyclesToRender * 50) == 0)
	{
		// Desenha a interface
		window.Draw(&interface);

		// Busca selecionada
		text.Size(window.Size().width / 85, window.Size().height / 29);
		text.String(selected);
		text.Position(int(window.Center().x) - text.Bounds().w / 2, 3);
		window.Draw(&text);

		// Nós visitados
		text.Size(window.Size().width / 128, window.Size().height / 36);
		text.String("Nós visitados " + std::to_string(Pathfinder::visited));
		text.Position(int(window.Size().width / 42.666f), int(window.Size().height * 0.9625f));
		window.Draw(&text);

		// Tempo decorrido da busca
		std::stringstream time;
		time << std::fixed;
		time.precision(3);
		time << (pathfinder ? Pathfinder::clock.Count() : pathfinder->timeElapsed);
		text.Size(window.Size().width / 128, window.Size().height / 36);
		text.String("Tempo " + time.str());
		text.Position(int(window.Size().width / 4.266f), int(window.Size().height * 0.9625f));
		window.Draw(&text);

		// Distância do caminho encontrado
		text.Size(window.Size().width / 128, window.Size().height / 36);
		text.String("Distância " + std::to_string(map->target ? map->target->Distance() : 0));
		text.Position(int(window.Size().width / 2.566f), int(window.Size().height * 0.9625f));
		window.Draw(&text);

		// Quantidade de nós
		text.Size(window.Size().width / 128, window.Size().height / 36);
		text.String("Nós " + std::to_string(map->Size()));
		text.Position(int(window.Size().width / 1.8f), int(window.Size().height * 0.9625f));
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
    Engine::window.Size(1280, 720);
	Engine::window.Title("Pathfinder");
    Engine::Run(new Pathfinding);

	return 0;
}

//--------------------------------------------------------------------------------------------------
