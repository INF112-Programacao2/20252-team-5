#include "../include/MaquinaDeReciclagem.h"
#include "../include/Fase.h"
#include "../include/Timer.h"
#include "../include/Monstro.h"
#include <iostream>

MaquinaDeReciclagem::MaquinaDeReciclagem(int posX, int posY, Fase *_fase, Timer *_timer, std::string imagem)
    : x(posX),
      y(posY),
      fase(_fase),
      timer(_timer)
{
    if (!_texture.loadFromFile(imagem))
    {
        std::cerr << "Erro ao carregar \"" << imagem << "\"" << std::endl;
        throw std::runtime_error("Erro ao carregar \"" + imagem + "\".");
    }

    _sprite.setTexture(_texture);
    _sprite.setPosition(x, y);
}

int MaquinaDeReciclagem::getPosicaoX() const
{
    return x;
}

int MaquinaDeReciclagem::getPosicaoY() const
{
    return y;
}

sf::Sprite MaquinaDeReciclagem::getSprite() const
{
    return _sprite;
}

void MaquinaDeReciclagem::desenhar(sf::RenderWindow &window)
{
    window.draw(_sprite);
}

int MaquinaDeReciclagem::calcularBonusTempo(Monstro *inimigo) const
{
    if (inimigo)
    {
        return inimigo->getValorTempo();
    }
    return 0;
}

void MaquinaDeReciclagem::receberInimigo(Monstro *inimigo)
{
    if (inimigo)
    {
        int bonus = calcularBonusTempo(inimigo);

        if (timer)
        {
            timer->aumentarTempo(bonus);
        }

        if (fase)
        {
            fase->removerEntidade(inimigo);
        }
    }
}