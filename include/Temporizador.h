#ifndef TEMPORIZADOR_H
#define TEMPORIZADOR_H

class Temporizador
{
private:
    int tempoRestante;

public:
    Temporizador(int tempoInicial); // Construtor da classe
    int getTempoRestante() const;
    void decrementarTempo(); // Decrementa o tempo a cada frame
    void aumentarTempo(int bonusTempo);
    bool tempoZerou() const; // Verifica se o jogo deve acabar
};

#endif