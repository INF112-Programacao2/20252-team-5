#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include <string>
#include <SFML/Graphics.hpp>
#include "VariaveisGlobais.h"

class Fase;

class Personagem
{
protected:
    float _x;
    float _y;
    float _velocidade; 
    float _velY;
    bool _jump = false;
    const float FORCA_JUMP = 700.f;
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
    void mudarPosicao(Direcao direcao, float dt, const Fase &fase);
    virtual void atualizar(float deltaTime, const Fase& fase) = 0;
    bool colisao(Direcao direcao, float dist, const Fase &fase);
    virtual void desenhar(sf::RenderWindow& window);
};

#endif