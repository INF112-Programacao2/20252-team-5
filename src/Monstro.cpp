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

    float dx = px - jx;
    float dy = py - jy;
    float dist = std::sqrt(dx * dx + dy * dy);  // distancia entre o player e o monstrinho

    int tileX = floorf(px / TAM_PIXEL); // posição no eixo x em relação à matriz
    int tileY = floorf(py / TAM_PIXEL); // posição no eixo y em relação à matriz

    // verifica se há parede ou queda a frente, se houver, muda a direção do movimento
    if(_direcao == Direcao::DIREITA){
        if(colisao(_direcao, 1.f, fase) || fase.getMapa(tileY + 1)[tileX + 1] == '0'){
            _direcao = Direcao::ESQUERDA;
        } else {
            mudarPosicao(_direcao, dt, fase);
        }
    }else if(_direcao == Direcao::ESQUERDA){
        if(colisao(_direcao, 1.f, fase) || fase.getMapa(tileY + 1)[tileX - 1] == '0'){
            _direcao = Direcao::DIREITA;
        } else {
            mudarPosicao(_direcao, dt, fase);
        }
    }

    if(dist < 150){
        if(dx < 0) _direcao = Direcao::ESQUERDA;
        else _direcao = Direcao::DIREITA;
    }
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

    float jx = jogador.getPosicaoX();
    float jy = jogador.getPosicaoY();

    float dx = _x - jx;
    float dy = _y - jy;
    float dist = std::sqrt(dx * dx + dy * dy);  // distancia entre o player e o monstrinho

    int tileX = floorf(_x / TAM_PIXEL); // posição no eixo x em relação à matriz
    int tileY = floorf(_y / TAM_PIXEL); // posição no eixo y em relação à matriz

    // verifica se há parede ou queda a frente, se houver, muda a direção do movimento
    if(_direcao == Direcao::DIREITA){
        if(colisao(_direcao, 1.f, fase) || fase.getMapa(tileY + 1)[tileX + 1] == '0'){
            _direcao = Direcao::ESQUERDA;
        } else {
            mudarPosicao(_direcao, dt, fase);
        }
    }else if(_direcao == Direcao::ESQUERDA){
        if(colisao(_direcao, 1.f, fase) || fase.getMapa(tileY + 1)[tileX - 1] == '0'){
            _direcao = Direcao::DIREITA;
        } else {
            mudarPosicao(_direcao, dt, fase);
        }
    }

    if(dist < 150){
        if(dx < 0) _direcao = Direcao::ESQUERDA;
        else _direcao = Direcao::DIREITA;
    }
}
