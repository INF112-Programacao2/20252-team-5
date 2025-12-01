#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <exception>
#include "../include/Personagem.h"
#include "../include/Fase.h"
#include "../include/VariaveisGlobais.h"

Personagem::Personagem(float x, float y, float velocidade, std::string imagem)
{
    _y = y;
    _x = x;
    _velocidade = velocidade;

    if (!_texture.loadFromFile(imagem))
    {
        std::cout << "Erro ao carregar \"" << imagem << "\"" << std::endl;
        throw std::runtime_error("Erro ao carregar \"" + imagem + "\".");
    }

    _sprite.setTexture(_texture);
    _sprite.setPosition(_x, _y);
}

Personagem::~Personagem()
{
}

float Personagem::getPosicaoX() const
{
    return _x;
}

float Personagem::getPosicaoY() const
{
    return _y;
}

float Personagem::getVelocidade() const
{
    return _velocidade;
}

sf::Sprite Personagem::getSprite() const
{
    return _sprite;
}

void Personagem::setX(float x){
    _x = x;
}

void Personagem::setY(float y){
    _y = y;
}

void Personagem::setVelocidade(float novaVelocidade)
{
    _velocidade = novaVelocidade;
}



void Personagem::mudarPosicao(Direcao direcao, float dt, Fase fase)
{
    float Mov = getVelocidade() * dt;   // velocidade horizontal
    float MovVert = velY * dt;  // velocidade vertical

    /////////// Movimento Vertical //////////


    /////////// Movimento Horizontal ////////
    if (colisao(direcao, Mov, fase)) {
        int parede;
        float novoX;
        if (direcao == Direcao::ESQUERDA) {
            parede = floorf((getX() - Mov) / TAM_PIXEL);
            novoX = (float(parede) * TAM_PIXEL) + TAM_PIXEL;
        } else if (direcao == Direcao::DIREITA) {
            parede = floorf((getX() + Mov + TAM_PIXEL) / TAM_PIXEL);
            novoX = (float(parede) * TAM_PIXEL) - TAM_PIXEL;
        }

        setX(novoX);
    }
    else {
        if (direcao == Direcao::Esquerda) Mov = -Mov;
        setX(getX() + Mov);
    }
}

bool Personagem::colisao(Direcao direcao, float dist, Fase fase)
{
    int tileX_right = floorf((_x + TAM_PIXEL - 1.f) / TAM_PIXEL);
    int tileX_left = floorf(_x / TAM_PIXEL);
    int tileY_top = floorf(_y / TAM_PIXEL);
    int tileY_bottom = floorf((_y + TAM_PIXEL - 1.f) / TAM_PIXEL);
    if (direcao == Direcao::ESQUERDA)
    {
        int newX = floorf((_x - dist) / TAM_PIXEL);
        return fase.getMapa(tileY_bottom)[newX] == '1' || fase.getMapa(tileY_top)[newX] == '1';
    }
    if (direcao == Direcao::DIREITA)
    {
        int newX = floorf((_x + TAM_PIXEL + dist) / TAM_PIXEL);
        return fase.getMapa(tileY_bottom)[newX] == '1' || fase.getMapa(tileY_top)[newX] == '1';
    }
    if (direcao == Direcao::CIMA)
    {
        int newY = floorf((_y - dist) / TAM_PIXEL);
        return fase.getMapa(newY)[tileX_left] == '1' || fase.getMapa(newY)[tileX_right] == '1';
    }
    if (direcao == Direcao::CAINDO)
    {
        int newY = floorf((_y + TAM_PIXEL + dist) / TAM_PIXEL);
        return fase.getMapa(newY)[tileX_left] == '1' || fase.getMapa(newY)[tileX_right] == '1';
    }
    return false;
}
void Personagem::desenhar(sf::RenderWindow &window)
{
    window.draw(_sprite);
}
