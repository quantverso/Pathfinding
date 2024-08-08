#include "Engine.h"
#include "Entity.h"

// ---------------------------------------------------------------------------------------------------------------------
// Inicialização de membros estáticos da classe

sf::RenderWindow* Engine::window{};	   ///< Janela gráfica
sf::Event		  Engine::event{};	   ///< Eventos da janela
Entity*			  Engine::entity{};	   ///< Classe base dos objetos
int				  Engine::width{1280}; ///< Largura da janela
int				  Engine::height{720}; ///< Altura da janela

// ---------------------------------------------------------------------------------------------------------------------

Engine::Engine()
{
}

// ---------------------------------------------------------------------------------------------------------------------

Engine::Engine(int width, int height)
{	
	this->width = width;
	this->height = height;
}

// ---------------------------------------------------------------------------------------------------------------------

Engine::~Engine()
{
	delete window;
}

// ---------------------------------------------------------------------------------------------------------------------

int Engine::Run(Entity* entity)
{
	// Atribui o endereço do objeto principal
	this->entity = entity;

    // Define o título da janela
    std::string className(typeid(*entity).name());
    this->title = className.substr(5); // Remove o prefixo 'class '

	// Cria a janela gráfica
	window = new sf::RenderWindow(
		sf::VideoMode(width, height), title, sf::Style::Titlebar | sf::Style::Close);

	// Chama o laço principal
	return Loop();
}

// ---------------------------------------------------------------------------------------------------------------------

int Engine::Loop()
{
    int cycles{};
    sf::Clock clock;
    sf::Time elapsedTime{ sf::Time::Zero };

    // Laço principal
    while (window->isOpen())
    {
        // Processa os eventos da janela
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        // Atualiza objetos
        Entity::UpdateObjects();

        // Atualiza o título da janela com FPS
        cycles++;
        elapsedTime += clock.restart();
        if (elapsedTime.asSeconds() >= 1.f)
        {            
            window->setTitle(title + " | FPS: " + std::to_string(cycles));
            cycles = 0;
            elapsedTime = sf::Time::Zero;
        }
    }

    delete entity;

    return 0;
}

// ---------------------------------------------------------------------------------------------------------------------
