#ifndef JOGADOR_H
#define JOGADOR_H

#include <SFML/Graphics.hpp>
#include "Personagem.h"
#include "Monstro.h"

class Jogador : public Personagem
{
private:
    Monstro *monstroCarregado;

    sf::Texture _textureParadoDireita; 
    sf::Texture _textureParadoEsquerda; 
    sf::Texture _textureAndandoDireita;
    sf::Texture _textureAndandoEsquerda;
    sf::Sprite _sprite2;

    bool movendoHorizontalmente = true;
    
    float tempoAcumulado = 0.0f;
    const float tempoIntervalo = 0.2f;

public:
    Jogador(float x, float y, float velocidade, std::string imagem);

    ~Jogador();

    void atualizar(float deltaTime, const Fase &fase) override;

    Monstro *getMonstroCarregado() const;
    void setMonstroCarregado(Monstro *monstro);
};

#endif

