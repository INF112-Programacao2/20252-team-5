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

void Perseguidor::comportamento(Jogador &jogador, float dt)
{
	// Calculando a distância entre o monstro e o jogador
	double dx = static_cast<double>(this->getPosicaoX() - jogador.getPosicaoX());
	double dy = static_cast<double>(this->getPosicaoY() - jogador.getPosicaoY());
	double dist = std::sqrt((dx * dx) + (dy * dy));

	// Calculando em qual pixel da matriz o monstro se encontra
	int tileX = static_cast<int>(this->getPosicaoX()) / TAM_PIXEL;
	int tileY = static_cast<int>(this->getPosicaoY()) / TAM_PIXEL;

	if (dist < 128)
	{ // Se o jogador estiver perto
		if (dx < 0)
		{
			this->mudarPosicao(Direcao::ESQUERDA, dt);
		}
		else
		{
			this->mudarPosicao(Direcao::DIREITA, dt);
		}
	}

	// Assumindo que o tunel seja representado por um 2 na matriz
	if (tileX == TUNEL1_COLUNA && tileY == TUNEL1_LINHA)
	{
		this->setX(TUNEL2_X + TAM_PIXEL);
		this->setY(TUNEL2_Y);
		return;
	}
	if (tileX == TUNEL2_COLUNA && tileY == TUNEL2_LINHA)
	{
		this->setX(TUNEL1_X + TAM_PIXEL);
		this->setY(TUNEL1_Y);
		return;
	}
}

///////// ESCONDEDOR /////////

Escondedor::Escondedor(float x, float y, float velocidade, std::string imagem, int tempo) : Monstro(x, y, velocidade, imagem, tempo)
{
}

void Escondedor::comportamento(Jogador &jogador, float dt)
{
	// Calculando a distância entre o monstro e o jogador
	double dx = static_cast<double>(this->getPosicaoX() - jogador.getPosicaoX());
	double dy = static_cast<double>(this->getPosicaoY() - jogador.getPosicaoY());
	double dist = std::sqrt((dx * dx) + (dy * dy));

	// Calculando em qual pixel da matriz o monstro se encontra
	int tileX = static_cast<int>(this->getPosicaoX()) / TAM_PIXEL;
	int tileY = static_cast<int>(this->getPosicaoY()) / TAM_PIXEL;

	if (dist < 128)
	{ // Se o jogador estiver perto
		if (dx < 0)
		{
			this->mudarPosicao(Direcao::ESQUERDA, dt);
		}
		else
		{
			this->mudarPosicao(Direcao::DIREITA, dt);
		}
	}

	// Assumindo que o tunel seja representado por um 2 na matriz
	if (tileX == TUNEL1_COLUNA && tileY == TUNEL1_LINHA)
	{
		this->setX(TUNEL2_X + TAM_PIXEL);
		this->setY(TUNEL2_Y);
		return;
	}
	if (tileX == TUNEL2_COLUNA && tileY == TUNEL2_LINHA)
	{
		this->setX(TUNEL1_X + TAM_PIXEL);
		this->setY(TUNEL1_Y);
		return;
	}

	// Assumindo que o esconderijo seja representado por um 3 na matriz
	// if (getLinhaDoMapa(tileY, NIVEL_ATUAL)[tileX] == '3' || getLinhaDoMapa(tileY + 1, NIVEL_ATUAL)[tileX] == '3')
	// {
	//	_escondido = true;
	// }
}