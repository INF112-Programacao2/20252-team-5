#ifndef JOGO_H
#define JOGO_H

#include <SFML/Graphics.hpp>

#include "Enum.h"
#include "Fase.h"

class Jogo
{
private:
    sf::RenderWindow window;
    Status status;
    Fase *faseAtual; // Usar ponteiro ajuda muito para alocar um objeto Fase e depois deletar

    // Metodos para gameloop
    void processarEventos();
    void atualizar();
    void desenhar();

public:
    Jogo();

    void executar();
    Status getStatus() const;
    Fase *getFase() const;
};

#endif