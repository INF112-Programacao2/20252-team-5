#include "../include/VariaveisGlobais.h"
#include "../include/Jogo.h"
#include "../include/Tela.h"
#include "../include/Fase.h"

#include <iostream>

Jogo::Jogo() : window(sf::VideoMode(LARGURA_JANELA, ALTURA_JANELA), "Recicla Mundo: ODS Game"),
               status(Status::MENU),
               faseAtual(nullptr)
{
    faseAtual = new Fase(60, 4);
}

Jogo::~Jogo()
{
    delete faseAtual;
}

void Jogo::executar()
{
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        float deltaTime = elapsed.asSeconds();

        processarEventos();

        atualizar(deltaTime);

        desenhar();
    }
}

void Jogo::processarEventos()
{
    sf::Event event;

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                if (status == Status::JOGANDO)
                {
                    status = Status::PAUSA;
                }
                else if (status == Status::PAUSA)
                {
                    status = Status::JOGANDO;
                }

                else if (status == Status::CREDITOS)
                {
                    status = Status::MENU;
                }
            }

            if (event.key.code == sf::Keyboard::Enter)
            {
                if (status == Status::MENU)
                {
                    int opcao = Tela::getOpcaoSelecionada();
                    switch (opcao)
                    {
                    case 0:
                        status = Status::JOGANDO;
                        break;
                    case 1:
                        status = Status::CREDITOS;
                        break;
                    case 2:
                        window.close();
                        break;
                    default:
                        break;
                    }
                }
                else if (status == Status::DERROTA)
                {
                    delete faseAtual;
                    faseAtual = new Fase(60, 5);
                    status = Status::MENU;
                }
            }
        }
        
        if (status == Status::MENU)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                Tela::anteriorOpcao();
                sf::sleep(sf::milliseconds(200));
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                Tela::proximaOpcao();
                sf::sleep(sf::milliseconds(200));
            }
        }
    }
}

void Jogo::atualizar(float deltaTime)
{
    static float acumuladorTempo = 0.0f;

    if (status == Status::JOGANDO && faseAtual)
    {
        acumuladorTempo += deltaTime;
        faseAtual->atualizar(deltaTime);

        if (acumuladorTempo >= 1.0f)
        {
            faseAtual->getTimer()->decrementarTempo();
            acumuladorTempo -= 1.0f;
        }

        if (faseAtual->getEntidades().size() == 1)
        {
            status = Status::VITORIA;
            return;
        }

        if (faseAtual->verificarDerrota())
        {
            status = Status::DERROTA;
            return;
        }
    }
    else if (status == Status::MENU)
    {
    }
}

void Jogo::desenhar()
{
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

Status Jogo::getStatus() const
{
    return status;
}

Fase *Jogo::getFase() const
{
    return faseAtual;
}