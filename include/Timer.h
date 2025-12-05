#ifndef TIMER_H
#define TIMER_H

class Timer
{
private:
    int tempoRestante;

public:
    Timer(int tempoInicial);
    int getTempoRestante() const;
    void decrementarTempo();
    void aumentarTempo(int bonusTempo);
    bool tempoZerou() const;
};

#endif