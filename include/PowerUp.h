#ifndef POWERUP_H
#define POWERUP_H

#include "VariaveisGlobais.h"

class Jogador;

class PowerUp
{
private:
    int duracao;
    Condicao condicao;

public:
    PowerUp(Condicao condicao, int duracao);
    Condicao getCondicao() const;
    int getDuracao() const;

    void aplicarEfeito(Jogador &jogador);
};

#endif