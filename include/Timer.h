#ifndef TIMER_H
#define TIMER_H

class Fase; // Novamente apenas definindo a class Fase para evitar importar a classe inteira

class Timer
{
private:
    int tempoRestante;

public:
    Timer(int tempoInicial); // Construtor da classe
    int getTempoRestante() const;
    void decrementarTempo(); // Decrementa o tempo a cada frame
    void aumentarTempo(int bonusTempo);
    bool tempoZerou() const; // Verifica se o jogo deve acabar
};

#endif