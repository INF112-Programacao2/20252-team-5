#ifndef MONSTRO_H_
#define MONSTRO_H_

#include "Personagem.h"
#include "Jogador.h
#include "Fase.h"

class Monstro : public Personagem {
private:
	int _valorTempo;
	bool _capturado = false;
public:
	Monstro(float x, float y, float velocidade, std::string imagem, int tempo);
	int getValorTempo() const;
	void receberCaptura();
	virtual void comportamento();
};


class Perseguidor : public Monstro {
public:
	Perseguidor(float x, float y, float velocidade, std::string imagem, int tempo);
	void comportamento(Jogador jogador, float dt, Fase fase) override;
};

class Escondedor : public Monstro {
private:
	_escondido = false;
public:
	Escondedor(float x, float y, float velocidade, std::string imagem, int tempo);
	void comportamento(Jogador jogador) override;
};
#endif