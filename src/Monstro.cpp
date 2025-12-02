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
	
	// calculando em qual pixel da matriz o monstro se encontra
	int tileX_right = floorf((_x + TAM_PIXEL - 1.f) / TAM_PIXEL);
    int tileX_left = floorf(_x / TAM_PIXEL);
    int tileY_top = floorf(_y / TAM_PIXEL);
    int tileY_bottom = floorf((_y + TAM_PIXEL - 1.f) / TAM_PIXEL);

	if (dist < 128)
	{				// se o jogador estiver perto (Lógica de FUGA)
		if (dx > 0) // Jogador à esquerda
		{
			// Foge para a DIREITA
			this->mudarPosicao(Direcao::DIREITA, dt, fase);
		}

		// tunel na direita
		if(fase.getMapa(tileY_top)[tileX_right + 1] == '2' && dx > 0){	// assumindo que o tunel seja representado por um 2 na matriz
			this->setX(_x);	//MUDAR
			this->setY(_y);
			// coordenadas da saída do tunel
		}	// tunel na esquerda
		else if (fase.getMapa(tileY_top)[tileX_left - 1] == '2' && dx < 0){
			this->setX(_x); //MUDAR
			this->setY(_y);
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

	// calculando em qual pixel da matriz o monstro se encontra
	int tileX_right = floorf((_x + TAM_PIXEL - 1.f) / TAM_PIXEL);
    int tileX_left = floorf(_x / TAM_PIXEL);
    int tileY_top = floorf(_y / TAM_PIXEL);
    int tileY_bottom = floorf((_y + TAM_PIXEL - 1.f) / TAM_PIXEL);

	if (dist < 128) {	// se o jogador estiver perto
		if(dx < 0){
			this->mudarPosicao(Direcao::ESQUERDA, dt, fase);
		}else{
			this->mudarPosicao(Direcao::DIREITA, dt, fase);
		}
		
		// tunel na direita
		if(fase.getMapa(tileY_top)[tileX_right + 1] == '2' && dx > 0){
			this->setX(_x);	//////////// MUDAR
			this->setY(_y);
			// coordenadas da saída do tunel
		} // tunel na esquerda
		else if (fase.getMapa(tileY_top)[tileX_left - 1] == '2' && dx < 0){
			this->setX(_x);
			this->setY(_y);
		}
		if(fase.getMapa(tileY_top + 1)[tileX_left] == '3' || fase.getMapa(tileY_top)[tileX_right] == '3'){
		// assumindo que o esconderijo seja representado por um 3 na matriz
			_escondido = true;
		}
	}
}