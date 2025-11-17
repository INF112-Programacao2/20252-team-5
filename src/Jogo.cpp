#include "../include/Jogo.h"
#include "../include/Tela.h"

#include <iostream>

// Tamanho qualquer para a janela
const unsigned int LARGURA_JANELA = 1280;
const unsigned int ALTURA_JANELA = 720;

// Inicializa a janela com o tamanho e título
Jogo::Jogo() : window(sf::VideoMode(LARGURA_JANELA, ALTURA_JANELA), "Recicla Mundo: ODS Game"),
               status(Status::MENU),
               faseAtual(nullptr) {}

// Game loop principal
void Jogo::executar()
{
    sf::Clock clock;

    while (window.isOpen())
    {
        // Processamento de input e eventos
        processarEventos();

        // Atualização da lógica do jogo
        atualizar();

        // Renderização e desenho
        desenhar();
    }
}

// Input/Eventos
void Jogo::processarEventos()
{
    sf::Event event;

    // O pollEvent retorna 'true' se um evento ocorreu
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        // Lógica de transição de estados
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::P)
            {
                if (status == Status::JOGANDO)
                {
                    status = Status::PAUSA;
                }
                else if (status == Status::PAUSA)
                {
                    status = Status::JOGANDO;
                }
            }
        }
    }
}

// Atualização da Lógica
void Jogo::atualizar()
{
    if (status == Status::JOGANDO)
    {
        // Aqui vai ter a logica da fase
    }
    else if (status == Status::MENU)
    {
        // Logica do menu
    }
}

// Renderização
void Jogo::desenhar()
{
    window.clear(sf::Color::Black);

    // Desenho é delegado à classe Tela
    if (status == Status::JOGANDO && faseAtual)
    {
        Tela::exibirFase(faseAtual, window);
    }
    else if (status == Status::MENU)
    {
        Tela::exibirMenu(window);
    }
    else if (status == Status::PAUSA)
    {
        Tela::exibirPause(window);
    }

    window.display();
}

// Getters
Status Jogo::getStatus() const
{
    return status;
}

Fase *Jogo::getFase() const
{
    return faseAtual;
}