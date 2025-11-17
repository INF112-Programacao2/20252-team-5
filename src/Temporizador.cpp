#include "../include/Temporizador.h"

Temporizador::Temporizador(int tempoInicial) : tempoRestante(tempoInicial) {}

int Temporizador::getTempoRestante() const
{
    return tempoRestante;
}

void Temporizador::decrementarTempo()
{
    if (tempoRestante > 0)
        tempoRestante--;
}

void Temporizador::aumentarTempo(int bonusTempo)
{
    if (bonusTempo > 0)
        tempoRestante += bonusTempo;
}

bool Temporizador::tempoZerou() const
{
    return tempoRestante <= 0;
}