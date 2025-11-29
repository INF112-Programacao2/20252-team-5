#ifndef MONSTRO_H_
#define MONSTRO_H_

#include "Personagem.h"

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
	void comportamento(Jogador jogador) override;
};

class Escondedor : public Monstro {
public:
	Escondedor(float x, float y, float velocidade, std::string imagem, int tempo);
	void comportamento(Jogador jogador) override;
};
#endif