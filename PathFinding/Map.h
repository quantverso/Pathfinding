#ifndef QUANTVERSO_MAP_H
#define QUANTVERSO_MAP_H

// ---------------------------------------------------------------------------------------------------------------------

#include <SFML/Graphics.hpp>
#include "Entity.h"

// ---------------------------------------------------------------------------------------------------------------------

////////////////////////////////////////////////////////////
/// \class Map
/// \brief Classe para representar um mapa de n�s.
///
/// A classe Map herda de Entity e � usada para criar e manipular
/// um mapa de n�s que pode ser utilizado em algoritmos de busca.
/// 
////////////////////////////////////////////////////////////
class Map : public Entity {
public:
    ////////////////////////////////////////////////////////////
    /// \enum Status
    /// \brief Estados poss�veis para cada n�.
    /// 
    ////////////////////////////////////////////////////////////
    enum class Status : char {
        Empty,    ///< N� vazio
        Obstacle, ///< N� que representa um obst�culo
        Origin,   ///< N� raiz (ponto de in�cio da busca)
        Target,   ///< N� objetivo (alvo da busca)
        Visited,  ///< N� visitado durante a busca
        Explored, ///< N� explorado durante a busca
        Path      ///< N� que faz parte do caminho encontrado
    };

    ////////////////////////////////////////////////////////////
    /// \struct Node
    /// \brief Representa um n� na matriz do mapa.
    /// 
    ////////////////////////////////////////////////////////////
    struct Node {
        Status                 status{};   ///< Estado do n�
        unsigned short         distance{}; ///< Dist�ncia at� o n� raiz
        Node*                  parent{};   ///< N� pai (antecessor)
        const unsigned short   row{};      ///< Linha do n� na matriz do mapa
        const unsigned short   column{};   ///< Coluna do n� na matriz do mapa

        ////////////////////////////////////////////////////////////
        /// \brief Construtor padr�o.
        ///
        ////////////////////////////////////////////////////////////
        Node() {}

        ////////////////////////////////////////////////////////////
        /// \brief Construtor.
        ///
        /// Inicializa um n� com sua posi��o espec�fica na matriz do mapa.
        ///
        /// \param row Linha do n� na matriz
        /// \param colum Coluna do n� na matriz
        /// 
        ////////////////////////////////////////////////////////////
        Node(unsigned short row, unsigned short column) : row(row), column(column) {}
    };

    const int DIVISOR; ///< Divide as dimens�es da janela para obter linhas e colunas
    const int ROWS;    ///< N�mero de linhas na matriz
    const int COLUMNS; ///< N�mero de colunas na matriz

    ////////////////////////////////////////////////////////////
    /// \brief Construtor.
    ///
    /// Inicializa o mapa com o divisor fornecido.
    /// O divisor define a quantidade de linhas e colunas da matriz
    /// dividindo as dimens�es da janela. Ex: Na resolu��o 1280x720,
    /// se o divisor fornecido for 10, resultar� em 1280 / 10 = 128 colunas
    /// e 720 / 10 = 72 linhas.
    ///
    /// \param divisor Divide as dimens�es da janela para obter linhas e colunas.
    /// 
    ////////////////////////////////////////////////////////////
    Map(int divisor);

    ////////////////////////////////////////////////////////////
    /// \brief Destrutor.
    ///
    ////////////////////////////////////////////////////////////
    ~Map();

    ////////////////////////////////////////////////////////////
    /// \brief Processa atualiza��es no mapa.
    ///
    ////////////////////////////////////////////////////////////
    void Update();

    ////////////////////////////////////////////////////////////
    /// \brief Desenha o mapa.
    ///
    ////////////////////////////////////////////////////////////
    void Draw();

    ////////////////////////////////////////////////////////////
    /// \brief M�todo usado para informar ao objeto da classe Map
    /// o estado atual da busca. Altera a vari�vel 'searching' do
    /// objeto da classe Map.
    ///
    /// \param status Status da busca -> true: em andamento; false: parada.
    /// 
    ////////////////////////////////////////////////////////////
    void Searching(bool status);

private:
    Node** nodes;            ///< Matriz para representar o mapa
    static Node* root;       ///< N� raiz (ponto de in�cio)
    static Node* target;     ///< N� objetivo (ponto final)

    sf::Clock clock;         ///< Rel�gio da SFML
    sf::Texture cellTexture; ///< Textura das c�lulas do mapa
    sf::Sprite cell;         ///< Sprite das c�lulas do mapa
    sf::Image maze;          ///< Imagem de labirinto

    bool searching{};        ///< Status da busca (true = em andamento)

    ////////////////////////////////////////////////////////////
    /// \brief Modifica c�lulas (n�s) do mapa.
    ///
    /// \param status Novo estado para os n�s.
    /// 
    ////////////////////////////////////////////////////////////
    void Modify(Status status);

    ////////////////////////////////////////////////////////////
    /// \brief Reseta todos os n�s do mapa.
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
