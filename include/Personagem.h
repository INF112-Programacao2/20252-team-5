#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include <string>
#include <SFML/Graphics.hpp>
#include "VariaveisGlobais.h"
#include "Fase.h"

class Personagem
{
protected:
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
    virtual ~Personagem();
    float getPosicaoX() const;
    float getPosicaoY() const;
    float getVelocidade() const;
    sf::Sprite getSprite() const;

    void setX(float x);
    void setY(float y);
    void setVelocidade(float novaVelocidade);
    void mudarPosicao(float novoX, float novoY);
    virtual void atualizar(float deltaTime) = 0;
    bool colisao(Direcao direcao, float dist, Fase fase);
    virtual void desenhar(sf::RenderWindow& window);
};

#endif
