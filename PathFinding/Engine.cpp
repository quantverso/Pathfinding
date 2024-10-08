#include "Engine.h"
#include "Entity.h"

// ---------------------------------------------------------------------------------------------------------------------
// Inicializa��o de membros est�ticos da classe

sf::RenderWindow* Engine::window{};	   ///< Janela gr�fica
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
	// Atribui o endere�o do objeto principal
	this->entity = entity;

    // Define o t�tulo da janela
    std::string className(typeid(*entity).name());
    this->title = className.substr(5); // Remove o prefixo 'class '

	// Cria a janela gr�fica
	window = new sf::RenderWindow(
		sf::VideoMode(width, height), title, sf::Style::Titlebar | sf::Style::Close);

	// Chama o la�o principal
	return Loop();
}

// ---------------------------------------------------------------------------------------------------------------------

int Engine::Loop()
{
    int cycles{};
    sf::Clock clock;
    sf::Time elapsedTime{ sf::Time::Zero };

    // La�o principal
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

        // Atualiza o t�tulo da janela com FPS
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
