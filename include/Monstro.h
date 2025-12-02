#ifndef MONSTRO_H
#define MONSTRO_H

#include "Personagem.h"

class Jogador;
class Fase;

class Monstro : public Personagem
{
private:
	int _valorTempo;
	bool _capturado = false;

public:
	Monstro(float x, float y, float velocidade, std::string imagem, int tempo);
	int getValorTempo() const;
	void receberCaptura();
	void capturar();
	bool estaCapturado() const;

	void atualizar(float deltaTime) override;
	virtual void comportamento(Jogador &jogador, float dt) = 0;
};

class Perseguidor : public Monstro
{
public:
	Perseguidor(float x, float y, float velocidade, std::string imagem, int tempo);
	void comportamento(Jogador &jogador, float dt) override;
};

class Escondedor : public Monstro
{
private:
	bool _escondido = false;

public:
	Escondedor(float x, float y, float velocidade, std::string imagem, int tempo);
	void comportamento(Jogador &jogador, float dt) override;
};

#endif
