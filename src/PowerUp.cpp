#include "../include/PowerUp.h"
#include "../include/Jogador.h" 

PowerUp::PowerUp(Condicao condicao, int duracao)
    : condicao(condicao), duracao(duracao)
{
}

Condicao PowerUp::getCondicao() const
{
    return condicao;
}

int PowerUp::getDuracao() const
{
    return duracao;
}

void PowerUp::aplicarEfeito(Jogador &jogador)
{
    jogador.ativarPowerUp(*this);
}