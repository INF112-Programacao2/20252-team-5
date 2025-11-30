#include <cmath>
#include <random>
#include "../include/Monstro.h"
#include "../include/Personagem.h"
#include "../include/Jogador.h"

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

void Perseguidor::comportamento(Jogador jogador)
{
	// calculando a distância entre o monstro e o jogador
	double dx = static_cast<double>(this->getPosicaoX() - jogador.getPosicaoX());
	double dy = static_cast<double>(this->getPosicaoY() - jogador.getPosicaoY());
	double dist = std::sqrt((dx * dx) + (dy * dy));

	if (dist < 128)
	{ // se o jogador estiver perto
	}
}

///////// ESCONDEDOR /////////

Escondedor::Escondedor(float x, float y, float velocidade, std::string imagem, int tempo)
	: Monstro(x, y, velocidade, imagem, tempo)
{
}

void Escondedor::comportamento(Jogador jogador)
{
	// comportamento simples placeholder
}