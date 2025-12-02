#include <cmath>
#include <random>
#include <iostream>
#include "../include/Monstro.h"
#include "../include/Personagem.h"
#include "../include/Jogador.h"
#include "../include/Fase.h"

///////// MONSTRO - CLASSE MÃE //////////

Monstro::Monstro(float x, float y, float velocidade, std::string imagem, int tempo)
    : Personagem(x, y, velocidade, imagem), _valorTempo(tempo), _capturado(false)
{
    float escala = (float)TAM_PIXEL / _texture.getSize().x;
    _sprite.setScale(escala, escala);
}

int Monstro::getValorTempo() const
{
    return _valorTempo;
}

void Monstro::receberCaptura()
{
    _capturado = true;
}

void Monstro::capturar()
{
    receberCaptura();
}

bool Monstro::estaCapturado() const
{
    return _capturado;
}

void Monstro::atualizar(float deltaTime, const Fase &fase)
{
    // Placeholder: monstros não fazem nada por enquanto na atualização genérica.
    // Comportamentos específicos (perseguir, esconder) podem ser implementados
    // em comportamento(Jogador) quando integrado com a lógica do Jogador.
}

///////// PERSEGUIDOR /////////

Perseguidor::Perseguidor(float x, float y, float velocidade, std::string imagem, int tempo)
    : Monstro(x, y, velocidade, imagem, tempo)
{
}

void Perseguidor::comportamento(const Jogador &jogador, float dt, const Fase &fase)
{
    float px = getPosicaoX();
    float py = getPosicaoY();

    float jx = jogador.getPosicaoX();
    float jy = jogador.getPosicaoY();

    // ----------------------
    // 1. Detecta distância
    // ----------------------
    float dx = px - jx;
    float dy = py - jy;
    float dist = std::sqrt(dx * dx + dy * dy);

    int tileX_right = floorf((_x + TAM_PIXEL - 1.f) / TAM_PIXEL);
    int tileX_left = floorf(_x / TAM_PIXEL);
    int tileY_top = floorf(_y / TAM_PIXEL);
    int tileY_bottom = floorf((_y + TAM_PIXEL - 1.f) / TAM_PIXEL);

    // Só foge se o jogador estiver perto
    if (dist < 150)
    {

        if (dx < 0)
        {
            // jogador está à direita -> foge para esquerda
            mudarPosicao(Direcao::ESQUERDA, dt, fase);
        }
        else
        {
            // jogador à esquerda -> foge para direita
            mudarPosicao(Direcao::DIREITA, dt, fase);
        }

        // tunel na direita
        if (fase.getMapa(tileY_top)[tileX_right + 1] == '2' && dx > 0)
        { // assumindo que o tunel seja representado por um 2 na matriz
            this->setX(1 * TAM_PIXEL);
            this->setY(20 * TAM_PIXEL);
            // coordenadas da saída do tunel
        } // tunel na esquerda
        else if (fase.getMapa(tileY_top)[tileX_left - 1] == '2' && dx < 0)
        {
            this->setX(35 * TAM_PIXEL);
            this->setY(20 * TAM_PIXEL);
        }
        return;
    }

    std::random_device rd;

    // std::mt19937 é o popular algoritmo Mersenne Twister
    // Inicializado com a semente da random_device
    std::mt19937 gen(rd());

    // Definimos o intervalo (incluindo o início e o fim)
    int min_val = 1;
    int max_val = 100;

    // 2. A Distribuição
    // Cria um objeto que uniformemente mapeia a saída de 'gen' para o intervalo [min_val, max_val]
    std::uniform_int_distribution<> distrib(0, 2);

    static float tempoTroca = 0.0f;
    static int direcaoAtual = 0; // 0=nada, 1=esquerda, 2=direita

    tempoTroca -= dt;

    if (tempoTroca <= 0)
    {
        tempoTroca = 0.8f;
        int r = distrib(gen); // 0, 1 ou 2

        if (r == 0)
            direcaoAtual = 0; // parado
        else if (r == 1)
            direcaoAtual = 1; // esquerda
        else if (r == 2)
            direcaoAtual = 2; // direita
    }

    // Executa movimento escolhido
    if (direcaoAtual == 1)
        mudarPosicao(Direcao::ESQUERDA, dt, fase);
    else if (direcaoAtual == 2)
        mudarPosicao(Direcao::DIREITA, dt, fase);
}

///////// ESCONDEDOR /////////

Escondedor::Escondedor(float x, float y, float velocidade, std::string imagem, int tempo) : Monstro(x, y, velocidade, imagem, tempo) {}

void Escondedor::comportamento(const Jogador &jogador, float dt, const Fase &fase)
{
    // calculando a distância entre o monstro e o jogador
    // CORRIGIDO: getQuantidadeMonstros é uma função e getX/getY usam _
    int qtd = fase.getQuantidadeMonstros();
    float dtt = dt;
    srand(time(nullptr));
    float px = getPosicaoX();
    float py = getPosicaoY();

    float jx = jogador.getPosicaoX();
    float jy = jogador.getPosicaoY();

    float dx = px - jx;
    float dy = py - jy;
    float dist = std::sqrt(dx * dx + dy * dy);

    int tileX_right = floorf((_x + TAM_PIXEL - 1.f) / TAM_PIXEL);
    int tileX_left = floorf(_x / TAM_PIXEL);
    int tileY_top = floorf(_y / TAM_PIXEL);
    int tileY_bottom = floorf((_y + TAM_PIXEL - 1.f) / TAM_PIXEL);

    // Só foge se o jogador estiver perto

    if (_escondido)
    {
        // Ele SÓ deve sair do esconderijo se o jogador estiver LONGE.
        if (dist >= 150)
        {
            _escondido = false;
            // Move para a tile acima (saindo do esconderijo)
            this->setY((tileY_top - 1) * TAM_PIXEL); // tileY_top é a tile atual, se ele se escondeu em tileY_bottom, use tileY_bottom para sair.
        }
        // Se o jogador estiver perto, ele FICA aqui e NÃO EXECUTA NADA mais.
        return; // Monstro permanece escondido, termina a função.
    }

    if (dist < 150)
    {
        int tileAbaixo = tileY_bottom + 1;
        if (fase.getMapa(tileAbaixo)[tileX_right] == '3')
        { //o esconderijo é representado por um 3 na matriz
            int r = rand() % 2;
            if (r == 0)
            {
                _escondido = true;
                this->setY((tileY_top + 1) * TAM_PIXEL);
            }
            return;
        }

        if (dx < 0)
        {
            // jogador está à direita -> foge para esquerda
            mudarPosicao(Direcao::ESQUERDA, dt, fase);
        }
        else
        {
            // jogador à esquerda -> foge para direita
            mudarPosicao(Direcao::DIREITA, dt, fase);
        }

        // tunel na direita
        if (fase.getMapa(tileY_top)[tileX_right + 1] == '2' && dx > 0)
        { // assumindo que o tunel seja representado por um 2 na matriz
            this->setX(1 * TAM_PIXEL);
            this->setY(20 * TAM_PIXEL);
            return;
            // coordenadas da saída do tunel
        } // tunel na esquerda
        else if (fase.getMapa(tileY_bottom)[tileX_left - 1] == '2' && dx < 0)
        {
            this->setX(35 * TAM_PIXEL);
            this->setY(20 * TAM_PIXEL);
            return;
        }
    }
    else
    {
        static float tempoTroca = 0.0f;
        static int direcaoAtual = 0; // 0=nada, 1=esquerda, 2=direita

        tempoTroca -= dt;

        if (tempoTroca <= 0)
        {
            tempoTroca = 1.0f;  // 1.0 a 3.0 segundos
            int r = rand() % 3; // 0, 1 ou 2

            if (r == 0)
                direcaoAtual = 0; // parado
            else if (r == 1)
                direcaoAtual = 1; // esquerda
            else if (r == 2)
                direcaoAtual = 2; // direita
        }

        // Executa movimento escolhido
        if (direcaoAtual == 1)
            mudarPosicao(Direcao::ESQUERDA, dt, fase);
        else if (direcaoAtual == 2)
            mudarPosicao(Direcao::DIREITA, dt, fase);
    }
}
