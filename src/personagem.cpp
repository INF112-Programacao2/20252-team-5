#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <exception>
#include "../include/Personagem.h"


Personagem::Personagem(float x, float y, float velocidade, std::string imagem){
    _y = y;
    _x = x;
    _velocidade = velocidade;

    if(!_texture.loadFromFile(imagem)){
        std::cout << "Erro ao carregar \"" << imagem << "\"" << std::endl;
        throw std::runtime_error("Erro ao carregar \""  + imagem + "\".");
    }

    _sprite.setTexture(_texture);
    _sprite.setPosition(_x, _y);
}

float Personagem::getX() const{
    return _x;
}

float Personagem::getY() const{
    return _y;
}

float Personagem::getVelocidade() const{
    return _velocidade;
}

sf::Sprite Personagem::getSprite() const{
    return _sprite;
}

void Personagem::setVelocidade(float novaVelocidade){
    _velocidade = novaVelocidade;
}

void Personagem::mudarPosicao(float x, float y){
    _x = x;
    _y = y;
    _sprite.setPosition(_x, _y);
}

bool Personagem::colisao(Direcao direcao, float dist, unsigned char mapa[19][29]){
    int tileX_right = floorf((_x + TAM_PIXEL - 1.f)/ TAM_PIXEL);
    int tileX_left = floorf(_x / TAM_PIXEL);
    int tileY_top = floorf(_y / TAM_PIXEL);
    int tileY_bottom = floorf((_y + TAM_PIXEL - 1.f) / TAM_PIXEL);
    if(direcao == Direcao::Esquerda){
        int newX = floorf((_x - dist) / TAM_PIXEL);
        return mapa[tileY_bottom][newX] == '1' || mapa[tileY_top][newX] == '1';
    }
    if(direcao == Direcao::Direita){
        int newX = floorf((_x + TAM_PIXEL + dist) / TAM_PIXEL);
        return mapa[tileY_bottom][newX] == '1' || mapa[tileY_top][newX] == '1';
    }
    if(direcao == Direcao::Cima){
        int newY = floorf((_y - dist) / TAM_PIXEL);
        return mapa[newY][tileX_left] == '1' || mapa[newY][tileX_right] == '1';
    }
    if(direcao == Direcao::Caindo){
        int newY = floorf((_y + TAM_PIXEL + dist) / TAM_PIXEL);
        return mapa[newY][tileX_left] == '1' || mapa[newY][tileX_right] == '1';
    }
    return false;
}