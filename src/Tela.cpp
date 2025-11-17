#include "../include/Tela.h"

#include <iostream>

// Inicializar membros static
int Tela::opcaoSelecionada = 0;
sf::Font Tela::font;

Tela::Tela() {}

int Tela::getOpcaoSelecionada() const
{
    return opcaoSelecionada;
}

void Tela::exibirMenu(sf::RenderWindow &window)
{
    static int opcaoSelecionada = 0; // 0 = Jogar, 1 = Créditos, 2 = Sair
    static bool carregouFonte = false;

    // Carregar a fonte
    if (!carregouFonte)
    {
        if (!font.loadFromFile("../assets/PixelBook-Regular.ttf"))
            std::cerr << "Erro ao carregar a fonte." << std::endl;

        carregouFonte = true;
    }

    // Navegação no menu
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        opcaoSelecionada--;
        if (opcaoSelecionada < 0)
            opcaoSelecionada = 0;

        sf::sleep(sf::milliseconds(300));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        opcaoSelecionada++;
        if (opcaoSelecionada > 2)
            opcaoSelecionada = 2;

        sf::sleep(sf::milliseconds(300));
    }

    // Desenho do menu
    window.clear(sf::Color(0, 0, 0));

    sf::Text titulo("Recicla Mundo: ODS Game", font, 50);
    titulo.setPosition(200, 80);

    sf::Text opcoes[3];
    std::string textos[3] = {"Jogar", "Créditos", "Sair"};

    for (int i = 0; i < 3; i++)
    {
        opcoes[i].setFont(font);
        opcoes[i].setCharacterSize(36);
        opcoes[i].setString(sf::String::fromUtf8(textos[i].begin(), textos[i].end()));
        opcoes[i].setPosition(260, 250 + i * 60);

        if (i == opcaoSelecionada)
            opcoes[i].setFillColor(sf::Color::Yellow);
        else
            opcoes[i].setFillColor(sf::Color::White);

        window.draw(opcoes[i]);
    }

    window.draw(titulo);
}

void Tela::exibirPause(sf::RenderWindow &window)
{
    window.clear(sf::Color::Yellow);
    // Código para desenhar a tela de pausa
    window.display();
}

void Tela::exibirFase(class Fase *fase, sf::RenderWindow &window)
{
    window.clear(sf::Color::Green);
    // Código para desenhar a fase
    window.display();
}