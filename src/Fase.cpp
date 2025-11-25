#include "../include/Fase.h"
#include "../include/Timer.h"               // Necessário para 'new Timer()' e 'timer->tempoZerou()'
#include "../include/Personagem.h"          // Necessário para deletar as entidades
#include "../include/MaquinaDeReciclagem.h" // Necessário para a composição

#include <string>
#include <iostream>
#include <memory>
#include <vector>

Fase::Fase(int inicioTempo, int numMonstros)
    : tempoInicial(inicioTempo),
      quantidadeMonstros(numMonstros),
      timer(nullptr), // Inicializa os ponteiros como nulos
      maquina(nullptr),
      level(nivelDomapa)
{
    this->timer = new Timer(inicioTempo); // Agora nosso ponteiro para Timer aponta para um objeto Timer

    this->maquina = new MaquinaDeReciclagem(posicaoX, posicaoY, this, timer);
    
    // Na sua implementação final, o mapa deve ser carregado de um arquivo
    /*for (int i = 0; i < MAPA_LINHAS; ++i)
    {
        std::memset(mapa[i], '0', MAPA_COLUNAS);
        mapa[i][MAPA_COLUNAS] = '\0'; // Adiciona terminador de string
    }*/
}

// Destrutor: Limpa a memória alocada dinamicamente
Fase::~Fase()
{
    // Deleta o Timer
    delete timer;
    timer = nullptr;

    // Deleta a Máquina
    delete maquina;
    maquina = nullptr;

    // Deleta todas as entidades alocadas dinamicamente
    /*for (Personagem *entidade : entidades)
    {
        delete entidade;
    }
    entidades.clear();*/
}

int Fase::getTempoInicial() const
{
    return tempoInicial;
}

int Fase::getQuantidadeMonstros() const
{
    return quantidadeMonstros;
}

const char *Fase::getMapa(int linha) const
{
    if (linha >= 0 && linha < MAPA_LINHAS)
    {
        return mapa[linha];
    }
    return nullptr;
}

void Fase::inicializarEntidades()
{
    // Cria os personagens e adiciona ao vetor 'entidades'.
    switch (level)
    {
    case 1:
    {
        // Array de ponteiros inteligentes para entidades
        std::vector<std::unique_ptr<Personagem>> entidades;

        // Inserção de entidades no vetor
        Personagem.push_back(std::make_unique</*aqui coloca as classes filhas de Personagem*/>());
        // mais elementos...

        // Caso precise configurar as entidades: for(std::unique_ptr<Personagem> &p : entidades) {...}

        break;
    }
    case 2:
    {
        // repete case 1
        break;
    }
    case 3:
    {
        // repete case 1
        break;
    }

    default:
        break;
    }
}

void Fase::atualizar(float deltaTime)
{
    // Lógica futura: a Fase usará o deltaTime e será chamada a cada frame do jogo

    if (verificarDerrota())
    {
        // Jogo::setStatus(Status::DERROTA);
    }
}

void Fase::desenhar(sf::RenderWindow &window)
{
    // Lógica futura: Desenha o mapa, a máquina, e todas as entidades.
}

void Fase::detectarVitoria()
{
    // Lógica futura:
    // if (monstros_capturados == quantidadeMonstros)
    // Jogo::setStatus(Status::VITORIA);
}

bool Fase::verificarDerrota() const
{
    return timer->tempoZerou(); // Usa o ponteiro para acessar o objeto Timer e utilizar o método da classe
}