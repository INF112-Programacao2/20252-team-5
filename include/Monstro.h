#ifndef MONSTRO_H_
#define MONSTRO_H_

#include "Personagem.h"
#include "VariaveisGlobais.h"
class Jogador;

class Monstro : public Personagem{
protected:
	int _valorTempo;
	bool _capturado = false;
	Direcao _direcao = Direcao::DIREITA;

	sf::Texture _textureParadoDireita; 
    sf::Texture _textureParadoEsquerda;
    sf::Texture _textureAndandoDireita;
    sf::Texture _textureAndandoEsquerda;
    sf::Sprite _sprite2;

    bool movendoHorizontalmente = true;
    
    float tempoAcumulado = 0.0f;
    const float tempoIntervalo = 0.2f;
	
public:
	Monstro(float x, float y, float velocidade, std::string imagem, int tempo);
	int getValorTempo() const;
	void receberCaptura();

	void capturar();
	bool estaCapturado() const;

	void atualizar(float deltaTime, const Fase& fase) override;
	virtual void comportamento(const Jogador& jogador, float dt, const Fase& fase) = 0;
};

class Perseguidor : public Monstro
{
public:
	Perseguidor(float x, float y, float velocidade, std::string imagem, int tempo);
	void comportamento(const Jogador& jogador, float dt, const Fase& fase) override;
};

class Escondedor : public Monstro
{
private:
	bool _escondido = false;

public:
	Escondedor(float x, float y, float velocidade, std::string imagem, int tempo);
	void comportamento(const Jogador& jogador, float dt, const Fase& fase) override;
};

#endif
