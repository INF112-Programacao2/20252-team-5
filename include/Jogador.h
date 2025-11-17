#ifndef JOGADOR_H
#define JOGADOR_H

#include "Personagem.h"
#include "PowerUp.h"

class Jogador : public Personagem
{
private:
    PowerUp *powerUpAtivo;

public:
    Jogador(int x, int y, int velocidade, const sf::Texture &textura);
    void ativarPowerUp(PowerUp &powerUp);
    void desativarPowerUp();
    PowerUp *getPowerUpAtivo() const;

    void capturarMonstro(Monstro *monstro);
};

#endif