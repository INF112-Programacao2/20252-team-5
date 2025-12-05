#ifndef JOGADOR_H
#define JOGADOR_H

#include <SFML/Graphics.hpp>
#include "Personagem.h"
#include "Monstro.h"
// #include "PowerUp.h" // Descomente quando tiver a classe PowerUp pronta
class PowerUp; // Forward declaration para evitar erro de compilação agora

// Herança: Jogador É UM Personagem
class Jogador : public Personagem
{
private:
    PowerUp *powerUpAtivo;
    Monstro *monstroCarregado; // NOVO: ponteiro para identificar o monstro capturado

    sf::Texture _textureParadoDireita; // Textura de parado/movendo para direita
    sf::Texture _textureParadoEsquerda; // Textura de parado/movendo para esquerda
    
    enum class ultimaDirecao { DIREITA, ESQUERDA };
    ultimaDirecao _ultimaDirecao = ultimaDirecao::DIREITA;

public:
    // CORREÇÃO 1 & 2: Usar float e std::string para bater com Personagem
    Jogador(float x, float y, float velocidade, std::string imagem);

    ~Jogador();

    // CORREÇÃO 3: Adicionar o método de atualização (movimento)
    // O mapa é necessário para colisão (use o tamanho que definimos)
    void atualizar(float deltaTime, const Fase &fase) override;

    // Seus métodos de PowerUp (mantenha se for usar depois)
    void ativarPowerUp(PowerUp &powerUp);
    void desativarPowerUp();
    PowerUp *getPowerUpAtivo() const;

    // Métodos para "capturar" Monstro
    Monstro *getMonstroCarregado() const;
    void setMonstroCarregado(Monstro *monstro);
};

#endif

