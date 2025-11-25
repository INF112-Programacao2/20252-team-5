#ifndef MAQUINA_DE_RECICLAGEM_H
#define MAQUINA_DE_RECICLAGEM_H

class Fase;
class Monstro;
class Timer;

class MaquinaDeReciclagem
{
    private:
    int x;
    int y;

    Fase* fase;
    Timer* timer;

    public:
    MaquinaDeReciclagem(int posX, int posY, Fase* _fase, Timer* _timer);

    int getPosicaoX() const;
    int getPosicaoY() const; 
    
    void receberInimigo(Monstro* inimigo); 

    int calcularBonusTempo(Monstro* inimigo) const;
};

#endif