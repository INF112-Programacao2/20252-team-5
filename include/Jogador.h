#ifndef JOGADOR_H
#define JOGADOR_H

#include "Personagem.h"
class Monstro;
class PowerUp;

class Jogador : public Personagem
{
private:
    PowerUp *powerUpAtivo;
    Monstro *monstroCarregado;

public:
    Jogador(float x, float y, float velocidade, std::string imagem);

    ~Jogador();

    void atualizar(float deltaTime) override;

    void ativarPowerUp(PowerUp &powerUp);
    void desativarPowerUp();
    PowerUp *getPowerUpAtivo() const;

    // Métodos para "capturar" Monstro
    Monstro *getMonstroCarregado() const;
    void setMonstroCarregado(Monstro *monstro);
};

#endif