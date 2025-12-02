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
    // A Máquina está posicionada e conectada aos seus colaboradores
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
        return inimigo->getValorTempo(); // Só chama a get de tempo do monstro e retorna o valor
    }
    return 0;
}

void MaquinaDeReciclagem::receberInimigo(Monstro *inimigo)
{
    if (inimigo) // isso verifica se ha um inimigo capturado no momento q a função é chamada
    {
        int bonus = calcularBonusTempo(inimigo); // primeiro pego o bonus do monstro

        if (timer)
        {
            timer->aumentarTempo(bonus); // e ja passo para aumentar o tempo
        }

        if (fase)
        {
            // CORREÇÃO: Chama o método da fase para remover o Monstro
            fase->removerEntidade(inimigo);
        }
    }
}
