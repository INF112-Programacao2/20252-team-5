#include "../include/VariaveisGlobais.h"
#include "../include/Jogo.h"
#include "../include/Tela.h"
#include "../include/Fase.h" // Necessário para criar uma fase

#include <iostream>

// Inicializa a janela com o tamanho e título
Jogo::Jogo() : window(sf::VideoMode(LARGURA_JANELA, ALTURA_JANELA), "Recicla Mundo: ODS Game"),
               status(Status::MENU),
               faseAtual(nullptr)
{
    // Inicializa a primeira fase (Exemplo: 60 segundos, 5 monstros)
    faseAtual = new Fase(60, 5); // Temporário
}

Jogo::~Jogo()
{
    // Limpa a memória da Fase
    delete faseAtual;
}

// Game loop principal
void Jogo::executar()
{
    sf::Clock clock;

    while (window.isOpen())
    {
        // Tempo decorrido desde o último frame (em segundos)
        sf::Time elapsed = clock.restart();
        float deltaTime = elapsed.asSeconds();

        processarEventos();

        // Passa o deltaTime para a lógica de atualização
        atualizar(deltaTime);

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
                switch (opcao)
                {
                case 0: // Jogar
                    status = Status::JOGANDO;
                    break;
                case 1: // Créditos
                    status = Status::CREDITOS;
                    break;
                case 2: // Sair
                    window.close();
                    break;
                default:
                    break;
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
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
              //reinicia fase
                delete faseAtual;
                faseAtual = new Fase(60, 5); //recria a fase (lembrar de ajustar os valores

                status = Status::MENU;
                sf::sleep(sf::milliseconds(200));
            }
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
void Jogo::atualizar(float deltaTime)
{
    // Acumulador para decrementar o Timer a cada 1 segundo real
    static float acumuladorTempo = 0.0f;
    acumuladorTempo += deltaTime;

    if (status == Status::JOGANDO && faseAtual)
    {
        // Atualizar a lógica da Fase
        faseAtual->atualizar(deltaTime);

        // Decremento do tempo a cada 1 segundo
        if (acumuladorTempo >= 1.0f)
        {
            faseAtual->getTimer()->decrementarTempo();
            acumuladorTempo -= 1.0f; // Retira 1 para manter o resto do tempo
        }

        // Verificação do estado do jogo

        // VITORIA: Se o vetor de entidades contém apenas o Jogador (que está na posição 0)
        if (faseAtual->getEntidades().size() == 1)
        {
            status = Status::VITORIA;
            return;
        }

        // DERROTA: Se o Timer da Fase zerou
         if (faseAtual->verificarDerrota())
        {
            status = Status::DERROTA;
            return;
        }
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
