#include <cmath>
#include <random>
#include "../include/Monstro.h"
#include "../include/Personagem.h"
#include "../include/Jogador.h"
#include "../include/Fase.h"

///////// MONSTRO - CLASSE MÃE //////////

Monstro::Monstro(float x, float y, float velocidade, std::string imagem, int tempo)
	: Personagem(x, y, velocidade, imagem), _valorTempo(tempo), _capturado(false)
{
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

void Monstro::atualizar(float deltaTime)
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

void Perseguidor::comportamento(Jogador jogador, float dt, Fase fase) {
	// calculando a distância entre o monstro e o jogador
	double dx = static_cast<double>(this->getPosicaoX() - jogador.getPosicaoX());
	double dy = static_cast<double>(this->getPosicaoY() - jogador.getPosicaoY());
	double dist = std::sqrt((dx * dx) + (dy * dy));

	if (dist < 128) {	// se o jogador estiver perto
		if(dx < 0){
			this->mudarPosicao(Direcao::ESQUERDA, dt, fase);
		}else{
			this->mudarPosicao(Direcao::DIREITA, dt, fase)
		}
		if(/*verificação do tunel*/){
			this->setX();
			this->setY();
			// coordenadas da saída do tunel
		}
	}
}

///////// ESCONDEDOR /////////

Escondedor::Escondedor(float x, float y, float velocidade, std::string imagem, int tempo) : 
Personagem(x, y, velocidade, imagem), _valorTempo(tempo) {}

void Escondedor::comportamento(Jogador jogador) {
	// calculando a distância entre o monstro e o jogador
	double dx = this->getX() - jogador.getX();
	double dy = this->getY() - jogador.getY();
	double dist = std::sqrt((dx * dx) + (dy * dy));

	if (dist < 128) {	// se o jogador estiver perto
		if(dx < 0){
			this->mudarPosicao(Direcao::ESQUERDA, dt, fase);
		}else{
			this->mudarPosicao(Direcao::DIREITA, dt, fase);
		}
		if(/*verificação do tunel*/){
				this->setX();
				this->setY();
				// coordenadas da saída do tunel
		}
		if(/*verificação do esconderijo*/){
			_escondido = true;
		}
	}
}