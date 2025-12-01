#ifndef MONSTRO_H_
#define MONSTRO_H_

#include "Personagem.h"
// #include "Jogador.h"
class Jogador;

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

	// Implementação de atualização genérica para monstros
	void atualizar(float deltaTime) override;
	virtual void comportamento(Jogador jogador, float dt, Fase fase) = 0;
};

class Perseguidor : public Monstro
{
public:
	Perseguidor(float x, float y, float velocidade, std::string imagem, int tempo);
	void comportamento(Jogador jogador, float dt, Fase fase) override;
};

class Escondedor : public Monstro
{
private:
	bool _escondido = false;

public:
	Escondedor(float x, float y, float velocidade, std::string imagem, int tempo);
	void comportamento(Jogador jogador, float dt, Fase fase) override;
};

#endif