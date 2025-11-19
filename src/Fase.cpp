#include "../include/Fase.h"
#include "../include/Timer.h"               // Necessário para 'new Timer()' e 'timer->tempoZerou()'
#include "../include/Personagem.h"          //Necessário para deletar as entidades
#include "../include/MaquinaDeReciclagem.h" //Necessário para a composição

#include <cstring>
#include <iostream>
#include <memory>
#include <vector>

void Fase::carregarMapa(int level)
{
    switch (level) // Escolha de um mapa modelo de acordo com o level
    {
    case 1:
    {
        // Mapa modelo pre-definido em array
        char mapa_modelo_1[mapa_linhas][mapa_colunas] = {"111111111111111111",
                                                         "100000000000000001",
                                                         "100000000000000001",
                                                         "100000000000000001",
                                                         "100000000100000001",
                                                         "100000000000000001",
                                                         "100000000000000001",
                                                         "100000000000000001",
                                                         "100000000000000001",
                                                         "111111111111111111"};
        for (int i = 0; i < mapa_linhas; i++)
        {
            std::strcmp(this->mapa[i], mapa_modelo_1[i], mapa_colunas); // Copia cada linha do mapa modelo para o mapa da Fase
            this->mapa[i][mapa_colunas] = '\0';                         // Garante um terminador no final de cada linha
        }
        break;
    }
    case 2:
    {
        // Mapa modelo pre-definido em array
        char mapa_modelo_2[mapa_linhas][mapa_colunas] = {"111111111111111111",
                                                         "100000000000000001",
                                                         "100000000000000001",
                                                         "100000000000000001",
                                                         "100000000200000001",
                                                         "100000000000000001",
                                                         "100000000000000001",
                                                         "100000000000000001",
                                                         "100000000000000001",
                                                         "111111111111111111"};
        for (int i = 0; i < mapa_linhas; i++)
        {
            std::strcmp(this->mapa[i], mapa_modelo_2[i], mapa_colunas);
            this->mapa[i][mapa_colunas] = '\0';
        }
        break;
    }
    case 3:
    {
        // Mapa modelo pre-definido em array
        char mapa_modelo_3[mapa_linhas][mapa_colunas] = {"111111111111111111",
                                                         "100000000000000001",
                                                         "100000000000000001",
                                                         "100000000000000001",
                                                         "100000000300000001",
                                                         "100000000000000001",
                                                         "100000000000000001",
                                                         "100000000000000001",
                                                         "100000000000000001",
                                                         "111111111111111111"};
        for (int i = 0; i < mapa_linhas; i++)
        {
            std::strcmp(this->mapa[i], mapa_modelo_3[i], mapa_colunas);
            this->mapa[i][mapa_colunas] = '\0';
        }
        break;
    }

    default:
        break;
    }
}

Fase::Fase(int inicioTempo, int numMonstros, int nivelDoMapa)
    : tempoInicial(inicioTempo),
      quantidadeMonstros(numMonstros),
      timer(nullptr), // Inicializa os ponteiros como nulos
      maquina(nullptr),
      level(nivelDomapa)
{
    this->timer = new Timer(inicioTempo); // Agora nosso ponteiro para Timer aponta para um objeto Timer

    // this->maquina = new MaquinaDeReciclagem(posicaoX, posicaoY); ---> quando criarmos a classe MaquinaDeReciclagem
    this->maquina = nullptr; // Temporariamente nulo, até a classe Maquina ser criada👍

    Fase::carregarMapa(level);
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
    for (Personagem *entidade : entidades)
    {
        delete entidade;
    }
    entidades.clear();
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