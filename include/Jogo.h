#ifndef JOGO_H
#define JOGO_H

#include <SFML/Graphics.hpp>

#include "VariaveisGlobais.h"
#include "Fase.h"

class Jogo
{
private:
    sf::RenderWindow window;
    Status status;
    Fase *faseAtual;

    // Metodos para gameloop
    void processarEventos();
    void atualizar(float deltaTime);
    void desenhar();

public:
    Jogo();
    ~Jogo();

    void executar();
    Status getStatus() const;
    Fase *getFase() const;
};

#endif
