#ifndef QUANTVERSO_MAP_H
#define QUANTVERSO_MAP_H

// ---------------------------------------------------------------------------------------------------------------------

#include <SFML/Graphics.hpp>
#include "Entity.h"

// ---------------------------------------------------------------------------------------------------------------------

////////////////////////////////////////////////////////////
/// \class Map
/// \brief Classe para representar um mapa de nós.
///
/// A classe Map herda de Entity e é usada para criar e manipular
/// um mapa de nós que pode ser utilizado em algoritmos de busca.
/// 
////////////////////////////////////////////////////////////
class Map : public Entity {
public:
    ////////////////////////////////////////////////////////////
    /// \enum Status
    /// \brief Estados possíveis para cada nó.
    /// 
    ////////////////////////////////////////////////////////////
    enum class Status : char {
        Empty,    ///< Nó vazio
        Obstacle, ///< Nó que representa um obstáculo
        Origin,   ///< Nó raiz (ponto de início da busca)
        Target,   ///< Nó objetivo (alvo da busca)
        Visited,  ///< Nó visitado durante a busca
        Explored, ///< Nó explorado durante a busca
        Path      ///< Nó que faz parte do caminho encontrado
    };

    ////////////////////////////////////////////////////////////
    /// \struct Node
    /// \brief Representa um nó na matriz do mapa.
    /// 
    ////////////////////////////////////////////////////////////
    struct Node {
        Status                 status{};   ///< Estado do nó
        unsigned short         distance{}; ///< Distância até o nó raiz
        Node*                  parent{};   ///< Nó pai (antecessor)
        const unsigned short   row{};      ///< Linha do nó na matriz do mapa
        const unsigned short   column{};   ///< Coluna do nó na matriz do mapa

        ////////////////////////////////////////////////////////////
        /// \brief Construtor padrão.
        ///
        ////////////////////////////////////////////////////////////
        Node() {}

        ////////////////////////////////////////////////////////////
        /// \brief Construtor.
        ///
        /// Inicializa um nó com sua posição específica na matriz do mapa.
        ///
        /// \param row Linha do nó na matriz
        /// \param colum Coluna do nó na matriz
        /// 
        ////////////////////////////////////////////////////////////
        Node(unsigned short row, unsigned short column) : row(row), column(column) {}
    };

    const int DIVISOR; ///< Divide as dimensões da janela para obter linhas e colunas
    const int ROWS;    ///< Número de linhas na matriz
    const int COLUMNS; ///< Número de colunas na matriz

    ////////////////////////////////////////////////////////////
    /// \brief Construtor.
    ///
    /// Inicializa o mapa com o divisor fornecido.
    /// O divisor define a quantidade de linhas e colunas da matriz
    /// dividindo as dimensões da janela. Ex: Na resolução 1280x720,
    /// se o divisor fornecido for 10, resultará em 1280 / 10 = 128 colunas
    /// e 720 / 10 = 72 linhas.
    ///
    /// \param divisor Divide as dimensões da janela para obter linhas e colunas.
    /// 
    ////////////////////////////////////////////////////////////
    Map(int divisor);

    ////////////////////////////////////////////////////////////
    /// \brief Destrutor.
    ///
    ////////////////////////////////////////////////////////////
    ~Map();

    ////////////////////////////////////////////////////////////
    /// \brief Processa atualizações no mapa.
    ///
    ////////////////////////////////////////////////////////////
    void Update();

    ////////////////////////////////////////////////////////////
    /// \brief Desenha o mapa.
    ///
    ////////////////////////////////////////////////////////////
    void Draw();

    ////////////////////////////////////////////////////////////
    /// \brief Método usado para informar ao objeto da classe Map
    /// o estado atual da busca. Altera a variável 'searching' do
    /// objeto da classe Map.
    ///
    /// \param status Status da busca -> true: em andamento; false: parada.
    /// 
    ////////////////////////////////////////////////////////////
    void Searching(bool status);

private:
    Node** nodes;            ///< Matriz para representar o mapa
    static Node* root;       ///< Nó raiz (ponto de início)
    static Node* target;     ///< Nó objetivo (ponto final)

    sf::Clock clock;         ///< Relógio da SFML
    sf::Texture cellTexture; ///< Textura das células do mapa
    sf::Sprite cell;         ///< Sprite das células do mapa
    sf::Image maze;          ///< Imagem de labirinto

    bool searching{};        ///< Status da busca (true = em andamento)

    ////////////////////////////////////////////////////////////
    /// \brief Modifica células (nós) do mapa.
    ///
    /// \param status Novo estado para os nós.
    /// 
    ////////////////////////////////////////////////////////////
    void Modify(Status status);

    ////////////////////////////////////////////////////////////
    /// \brief Reseta todos os nós do mapa.
    ///
    ////////////////////////////////////////////////////////////
    void Reset();

    ////////////////////////////////////////////////////////////
    /// \brief Desenha o labirinto no mapa.
    ///
    ////////////////////////////////////////////////////////////
    void setMaze();

    friend class PathFinder;
};

// ---------------------------------------------------------------------------------------------------------------------

inline void Map::Searching(bool status)
{
	searching = status;
}

// ---------------------------------------------------------------------------------------------------------------------

#endif
