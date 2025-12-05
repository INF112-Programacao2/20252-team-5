#ifndef JOGO_H
#define JOGO_H

#include <SFML/Graphics.hpp> // Para sf::RenderWindow, sf::VideoMode, sf::Clock, sf::Time
#include "Fase.h"            // Para Fase* e Fase
#include "VariaveisGlobais.h"

class Jogo {
private:
    sf::RenderWindow window; 
    Status status;           
    Fase *faseAtual;         
    
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

#endif // JOGO_H