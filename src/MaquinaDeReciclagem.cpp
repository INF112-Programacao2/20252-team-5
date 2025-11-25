#include "../include/MaquinaDeReciclagem.h"
#include "../include/Fase.h"   
#include "../include/Timer.h"  
#include "../include/Monstro.h"
#include <iostream>

MaquinaDeReciclagem::MaquinaDeReciclagem(int posX, int posY, Fase* _fase, Timer* _timer)
    : x(posX), 
      y(posY),
      fase(_fase),
      timer(_timer)
{
    // A Máquina está posicionada e conectada aos seus colaboradores
}

int MaquinaDeReciclagem::getPosicaoX() const 
{
    return x;
}

int MaquinaDeReciclagem::getPosicaoY() const 
{
    return y;
}


int MaquinaDeReciclagem::calcularBonusTempo(Monstro* inimigo) const
{
    if (inimigo)
    {
        return inimigo->getValorTempo(); // Só chama a get de tempo do monstro e retorna o valor
    }
    return 0;
}

void MaquinaDeReciclagem::receberInimigo(Monstro* inimigo)
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
            // Fase precisará de um método para remover o monstro do vetor de entidades 👍👍👍👍
            // fase->removerMonstro(inimigo); por exemplo
        }
    }
}