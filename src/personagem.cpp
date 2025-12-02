#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <exception>
#include "../include/Personagem.h"
#include "../include/Fase.h"
#include "../include/VariaveisGlobais.h"
#include "../include/Fase.h"

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

<<<<<<< HEAD
void Personagem::setX(float x)
{
=======
void Personagem::setX(float x) {
>>>>>>> 242dd9d33ccf35c2a9c2f0865606d185ca7cf9cb
    _x = x;
    _sprite.setPosition(sf::Vector2f(_x, _y));
}

<<<<<<< HEAD
void Personagem::setY(float y)
{
=======
void Personagem::setY(float y) {
>>>>>>> 242dd9d33ccf35c2a9c2f0865606d185ca7cf9cb
    _y = y;
    _sprite.setPosition(sf::Vector2f(_x, _y));
}

void Personagem::setVelocidade(float novaVelocidade)
{
    _velocidade = novaVelocidade;
}

void Personagem::mudarPosicao(Direcao direcao, float dt, const Fase &fase)
{
<<<<<<< HEAD
    float Mov = _velocidade * dt; // velocidade horizontal
=======
    float Mov = getVelocidade() * dt;   // velocidade horizontal
>>>>>>> 242dd9d33ccf35c2a9c2f0865606d185ca7cf9cb

    /////////// Movimento Horizontal ////////
    if (colisao(direcao, Mov, fase))
    {
        int parede;
        float novoX;
        if (direcao == Direcao::ESQUERDA)
        {
            parede = floorf((_x - Mov) / TAM_PIXEL);
            novoX = (float(parede) * TAM_PIXEL) + TAM_PIXEL;
<<<<<<< HEAD
            setX(novoX);
        }
        else if (direcao == Direcao::DIREITA)
        {
=======
        }
        else if (direcao == Direcao::DIREITA) {
>>>>>>> 242dd9d33ccf35c2a9c2f0865606d185ca7cf9cb
            parede = floorf((_x + Mov + TAM_PIXEL) / TAM_PIXEL);
            // Ajuste o novoX para a lateral do tile + uma pequena margem
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
<<<<<<< HEAD
        // Proteção: Checa se coluna e linhas são válidas e se o mapa não é nullptr
        if (newX >= 0 && tileY_top >= 0 && tileY_bottom < MAPA_LINHAS)
        {
            const char *mapaLinhaTop = fase.getMapa(tileY_top);
            const char *mapaLinhaBottom = fase.getMapa(tileY_bottom);

            if (mapaLinhaTop && mapaLinhaBottom)
            {
                return mapaLinhaBottom[newX] != '0' || mapaLinhaTop[newX] != '0';
            }
        }
=======
        return (fase.getMapa(tileY_bottom)[newX] != '0' || fase.getMapa(tileY_top)[newX] != '0');
>>>>>>> 242dd9d33ccf35c2a9c2f0865606d185ca7cf9cb
    }

    // --- Colisão Direita ---
    if (direcao == Direcao::DIREITA)
    {
        int newX = floorf((_x + TAM_PIXEL + dist) / TAM_PIXEL);
<<<<<<< HEAD
        // Proteção: Checa se coluna e linhas são válidas e se o mapa não é nullptr
        if (newX < MAPA_COLUNAS && tileY_top >= 0 && tileY_bottom < MAPA_LINHAS)
        {
            const char *mapaLinhaTop = fase.getMapa(tileY_top);
            const char *mapaLinhaBottom = fase.getMapa(tileY_bottom);

            if (mapaLinhaTop && mapaLinhaBottom)
            {
                return mapaLinhaBottom[newX] != '0' || mapaLinhaTop[newX] != '0';
            }
        }
=======
        return (fase.getMapa(tileY_bottom)[newX] != '0' || fase.getMapa(tileY_top)[newX] != '0');
>>>>>>> 242dd9d33ccf35c2a9c2f0865606d185ca7cf9cb
    }

    // --- Colisão Cima ---
    if (direcao == Direcao::CIMA)
    {
        int newY = floorf((_y - dist) / TAM_PIXEL);
<<<<<<< HEAD
        const char *mapaLinha = fase.getMapa(newY);

        // Proteção: Checa se newY e colunas são válidas e se o mapa não é nullptr
        if (mapaLinha && newY >= 0 && tileX_left >= 0 && tileX_right < MAPA_COLUNAS)
        {
            return mapaLinha[tileX_left] != '0' || mapaLinha[tileX_right] != '0';
        }
=======
        return (fase.getMapa(newY)[tileX_left] != '0' || fase.getMapa(newY)[tileX_right] != '0');
>>>>>>> 242dd9d33ccf35c2a9c2f0865606d185ca7cf9cb
    }

    // --- Colisão Caindo (BOTTOM) ---
    if (direcao == Direcao::CAINDO)
    {
        int newY = floorf((_y + TAM_PIXEL + dist) / TAM_PIXEL);
<<<<<<< HEAD
        const char *mapaLinha = fase.getMapa(newY);

        // Proteção: Checa se newY está dentro do limite e se o mapa não é nullptr
        if (mapaLinha && newY < MAPA_LINHAS && tileX_left >= 0 && tileX_right < MAPA_COLUNAS)
        {
            return mapaLinha[tileX_left] != '0' || mapaLinha[tileX_right] != '0';
        }
=======
        return (fase.getMapa(newY)[tileX_left] != '0' || fase.getMapa(newY)[tileX_right] != '0');
>>>>>>> 242dd9d33ccf35c2a9c2f0865606d185ca7cf9cb
    }
    return false;
}

void Personagem::desenhar(sf::RenderWindow &window)
{
    window.draw(_sprite);
}