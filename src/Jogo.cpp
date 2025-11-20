#include "../include/VariaveisGlobais.h"
#include "../include/Jogo.h"
#include "../include/Tela.h"

#include <iostream>

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

        switch (status)
        {
        // MENU
        case Status::MENU:
            // Navegação no menu (delegada para Tela)
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                Tela::anteriorOpcao();
                sf::sleep(sf::milliseconds(300));
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                Tela::proximaOpcao();
                sf::sleep(sf::milliseconds(300));
            }

            // Seleção no menu
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                int opcao = Tela::getOpcaoSelecionada();
                if (opcao == 0) // Jogar
                {
                    status = Status::JOGANDO;
                }
                else if (opcao == 1) // Créditos
                {
                    status = Status::CREDITOS;
                }
                else if (opcao == 2) // Sair
                {
                    window.close();
                }
            }
            break;

        // JOGANDO
        case Status::JOGANDO:
            // Pausar o jogo
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                status = Status::PAUSA;
            }
            break;

        // PAUSA
        case Status::PAUSA:
            // Retomar o jogo
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                status = Status::JOGANDO;
            }
            break;

        // VITORIA
        case Status::VITORIA:
            break;

        // DERROTA
        case Status::DERROTA:
            break;

        // CREDITOS
        case Status::CREDITOS:
            // Voltar ao menu principal
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                status = Status::MENU;
            }
            break;

        // Default case
        default:
            break;
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
    // Desenho é delegado à classe Tela
    switch (status)
    {
    case Status::JOGANDO:
        if (faseAtual)
            Tela::exibirFase(faseAtual, window);
        break;
    case Status::MENU:
        Tela::exibirMenu(window);
        break;
    case Status::PAUSA:
        Tela::exibirPause(window);
        break;
    case Status::VITORIA:
        Tela::exibirVitoria(window);
        break;
    case Status::DERROTA:
        Tela::exibirDerrota(window);
        break;
    case Status::CREDITOS:
        Tela::exibirCreditos(window);
        break;
    default:
        break;
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