#ifndef TELA_H
#define TELA_H

#include <SFML/Graphics.hpp>

class Tela
{
private:
    static int opcaoSelecionada;
    static sf::Font font;

public:
    Tela();
    int getOpcaoSelecionada() const;

    static void exibirMenu(sf::RenderWindow &window);
    static void exibirPause(sf::RenderWindow &window);
    static void exibirFase(class Fase *fase, sf::RenderWindow &window);
};

#endif