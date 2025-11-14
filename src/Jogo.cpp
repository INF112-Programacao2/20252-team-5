#include "../include/Jogo.h"
#include <iostream>

// Tamanho qualquer para a janela
const unsigned int LARGURA_JANELA = 1280;
const unsigned int ALTURA_JANELA = 720;

// Inicializa a janela com o tamanho e título
Jogo::Jogo() : window(sf::VideoMode(LARGURA_JANELA, ALTURA_JANELA), "Recicla Mundo - ODS Game"),
               status(Status::MENU), 
               faseAtual(nullptr)    
{
}

// Game Loop Principal

void Jogo::executar()
{
    sf::Clock clock;

    while (window.isOpen())
    {
        // Processamento de Input e Eventos
        processarEventos();

        // Atualização da Lógica do Jogo
        atualizar();

        // Renderização e Desenho
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
        {
            window.close();
        }

        // Lógica de Transição de Estados
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
        // Tela::desenharFase(faseAtual, window)
    }
    else if (status == Status::MENU)
    {
        // Tela::exibirMenu(window);
    }
    else if (status == Status::PAUSA)
    {
        // Tela::exibirTelaPause(window);
    }

    window.display(); 
}

// Getters

Status Jogo::getStatus() 
{
    return status;
}

Fase* Jogo::getFase() 
{
    return faseAtual;
}