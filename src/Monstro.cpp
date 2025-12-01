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
	// calculando a distância entre o monstro e o jogador
	double dx = static_cast<double>(this->getPosicaoX() - jogador.getPosicaoX());
	double dy = static_cast<double>(this->getPosicaoY() - jogador.getPosicaoY());
	double dist = std::sqrt((dx * dx) + (dy * dy));

	if (dist < 128)
	{				// se o jogador estiver perto (Lógica de FUGA)
		if (dx > 0) // Jogador à esquerda
		{
			// Foge para a DIREITA
			this->mudarPosicao(Direcao::DIREITA, dt, fase);
		}
		else if (dx < 0) // Jogador à direita
		{
			// Foge para a ESQUERDA
			this->mudarPosicao(Direcao::ESQUERDA, dt, fase); // CORRIGIDO: Ponto e vírgula aqui
		}
		if (false /* verificação do tunel */)
		{
			// CORRIGIDO: setX/setY requerem argumentos. Comentado até a lógica de coordenadas estar pronta.
			// this->setX();
			// this->setY();
			// coordenadas da saída do tunel
		}
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
	double dx = this->getPosicaoX() - jogador.getPosicaoX();
	double dy = this->getPosicaoY() - jogador.getPosicaoY();
	double dist = std::sqrt((dx * dx) + (dy * dy));

	if (dist < 128)
	{				// se o jogador estiver perto (Lógica de FUGA)
		if (dx > 0) // Jogador à esquerda
		{
			// Foge para a DIREITA
			this->mudarPosicao(Direcao::DIREITA, dt, fase);
		}
		else if (dx < 0) // Jogador à direita
		{
			// Foge para a ESQUERDA
			this->mudarPosicao(Direcao::ESQUERDA, dt, fase);
		}
		if (false /* verificação do tunel */)
		{
			// CORRIGIDO: setX/setY requerem argumentos. Comentado até a lógica de coordenadas estar pronta.
			// this->setX(); 
			// this->setY(); 
			// coordenadas da saída do tunel
		}
		if (false /* verificação do esconderijo */)
		{
			_escondido = true;
		}
	}
}