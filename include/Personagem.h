#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include <SFML/Graphics.hpp>

class Personagem
{
private:
    int x;
    int y;
    int velocidade;
    sf::Sprite sprite;

public:
    Personagem(int x, int y, int velocidade, const sf::Texture &textura);
    int getX() const;
    int getY() const;
    int getVelocidade() const;

    void setX(int novoX);
    void setY(int novoY);
    void setVelocidade(int novaVelocidade);
    void mudarPosicao(int novoX, int novoY);
};

#endif