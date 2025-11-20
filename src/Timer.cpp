#include "../include/Timer.h"

Timer::Timer(int tempoInicial) : tempoRestante(tempoInicial) {}

int Timer::getTempoRestante() const
{
    return tempoRestante;
}

void Timer::decrementarTempo()
{
    if (tempoRestante > 0)
        tempoRestante--;
}

void Timer::aumentarTempo(int bonusTempo)
{
    if (bonusTempo > 0)
        tempoRestante += bonusTempo;
}

bool Timer::tempoZerou() const
{
    return tempoRestante <= 0;
}