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
        std::cerr << "Erro ao carregar \"" << imagem << "\"" << std::endl;
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

void Personagem::setX(float x)
{
    _x = x;
    _sprite.setPosition(sf::Vector2f(_x, _y));
}

void Personagem::setY(float y)
{
    _y = y;
    _sprite.setPosition(sf::Vector2f(_x, _y));
}

void Personagem::setVelocidade(float novaVelocidade)
{
    _velocidade = novaVelocidade;
}

void Personagem::mudarPosicao(Direcao direcao, float dt, const Fase &fase)
{
    float Mov = _velocidade * dt;

    if (colisao(direcao, Mov, fase))
    {
        int parede;
        float novoX;
        if (direcao == Direcao::ESQUERDA)
        {
            parede = floorf((_x - Mov) / TAM_PIXEL);
            novoX = (float(parede) * TAM_PIXEL) + TAM_PIXEL;
            setX(novoX);
        }
        else if (direcao == Direcao::DIREITA)
        {
            parede = floorf((_x + Mov + TAM_PIXEL) / TAM_PIXEL);
            novoX = (float(parede) * TAM_PIXEL) - (TAM_PIXEL + 1.f);
        }

        setX(novoX);
    }
    else
    {
        if (direcao == Direcao::ESQUERDA)
            Mov = -Mov;
        setX(_x + Mov);
    }
    _sprite.setPosition(sf::Vector2f(_x, _y));
}

bool Personagem::colisao(Direcao direcao, float dist, const Fase &fase)
{
    int tileX_right = floorf((_x + TAM_PIXEL - 1.f) / TAM_PIXEL);
    int tileX_left = floorf(_x / TAM_PIXEL);
    int tileY_top = floorf(_y / TAM_PIXEL);
    int tileY_bottom = floorf((_y + TAM_PIXEL - 1.f) / TAM_PIXEL);
    
    if (direcao == Direcao::ESQUERDA)
    {
        int newX = floorf((_x - dist) / TAM_PIXEL);
        if (newX >= 0 && tileY_top >= 0 && tileY_bottom < MAPA_LINHAS)
        {
            const char *mapaLinhaTop = fase.getMapa(tileY_top);
            const char *mapaLinhaBottom = fase.getMapa(tileY_bottom);

            if (mapaLinhaTop && mapaLinhaBottom)
            {
                return mapaLinhaBottom[newX] != '0' || mapaLinhaTop[newX] != '0';
            }
        }
    }

    if (direcao == Direcao::DIREITA)
    {
        int newX = floorf((_x + TAM_PIXEL + dist) / TAM_PIXEL);
        if (newX < MAPA_COLUNAS && tileY_top >= 0 && tileY_bottom < MAPA_LINHAS)
        {
            const char *mapaLinhaTop = fase.getMapa(tileY_top);
            const char *mapaLinhaBottom = fase.getMapa(tileY_bottom);

            if (mapaLinhaTop && mapaLinhaBottom)
            {
                return mapaLinhaBottom[newX] != '0' || mapaLinhaTop[newX] != '0';
            }
        }
    }

    if (direcao == Direcao::CIMA)
    {
        int newY = floorf((_y - dist) / TAM_PIXEL);
        const char *mapaLinha = fase.getMapa(newY);

        if (mapaLinha && newY >= 0 && tileX_left >= 0 && tileX_right < MAPA_COLUNAS)
        {
            return mapaLinha[tileX_left] != '0' || mapaLinha[tileX_right] != '0';
        }
    }

    if (direcao == Direcao::CAINDO)
    {
        int newY = floorf((_y + TAM_PIXEL + dist) / TAM_PIXEL);
        const char *mapaLinha = fase.getMapa(newY);

        if (mapaLinha && newY < MAPA_LINHAS && tileX_left >= 0 && tileX_right < MAPA_COLUNAS)
        {
            return mapaLinha[tileX_left] != '0' || mapaLinha[tileX_right] != '0';
        }
    }
    return false;
}

void Personagem::desenhar(sf::RenderWindow &window)
{
    window.draw(_sprite);
}