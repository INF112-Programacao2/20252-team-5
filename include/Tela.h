#ifndef TELA_H
#define TELA_H

#include <SFML/Graphics.hpp>

class Tela
{
private:
    static int opcaoSelecionada;
    static sf::Font font;

    static void carregarFonte();

public:
    Tela();
    static int getOpcaoSelecionada();
    static void proximaOpcao();
    static void anteriorOpcao();

    static void exibirMenu(sf::RenderWindow &window);
    static void exibirPause(sf::RenderWindow &window);
    static void exibirFase(class Fase *fase, sf::RenderWindow &window);
    static void exibirCreditos(sf::RenderWindow &window);
    static void exibirVitoria(sf::RenderWindow &window);
    static void exibirDerrota(sf::RenderWindow &window);
};

#endif