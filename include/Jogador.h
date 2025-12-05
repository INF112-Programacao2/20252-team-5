#ifndef JOGADOR_H
#define JOGADOR_H

#include <SFML/Graphics.hpp>
#include "Personagem.h"
#include "Monstro.h"

class Jogador : public Personagem
{
private:
    Monstro *monstroCarregado; // NOVO: ponteiro para identificar o monstro capturado

    sf::Texture _textureParadoDireita; // Textura de parado para direita
    sf::Texture _textureParadoEsquerda; // Textura de parado para esquerda
    sf::Texture _textureAndandoDireita; // Textura de movendo para direita
    sf::Texture _textureAndandoEsquerda; // Textura de movendo para esquerda
    sf::Sprite _sprite2;

    bool movendoHorizontalmente = true;
    
    float tempoAcumulado = 0.0f;
    const float tempoIntervalo = 0.2f;

public:
    // CORREÇÃO 1 & 2: Usar float e std::string para bater com Personagem
    Jogador(float x, float y, float velocidade, std::string imagem);

    ~Jogador();

    // CORREÇÃO 3: Adicionar o método de atualização (movimento)
    // O mapa é necessário para colisão (use o tamanho que definimos)
    void atualizar(float deltaTime, const Fase &fase) override;

    // Métodos para "capturar" Monstro
    Monstro *getMonstroCarregado() const;
    void setMonstroCarregado(Monstro *monstro);
};

#endif

