#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include <string>
#include <SFML/Graphics.hpp>
#include "VariaveisGlobais.h"

class Personagem
{
private:
    float _x;
    float _y;
    float _velocidade;
    // coloquei float pois a movimentação que tentei fazer até agora é baseada nos pixels, 
    // não nos quadrados da matriz, para evitar teleporte de um tile para outro. 
    // Desse jeito ele passa de forma mais suave, mas dá para mudar, qualquer coisa
    sf::Sprite _sprite;
    sf::Texture _texture;

public:
    Personagem(float x, float y, float velocidade, std::string imagem);
    float getX() const;
    float getY() const;
    float getVelocidade() const;
    sf::Sprite getSprite() const;

    void setVelocidade(float novaVelocidade);
    void mudarPosicao(float novoX, float novoY);
    bool colisao(Direcao direcao, float dist, unsigned char mapa[19][29]);
    // esse mapa posteriormente deverá ser substituido por uma referencia para a fase
};

#endif
