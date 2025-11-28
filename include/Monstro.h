#ifndef MONSTRO_H
#define MONSTRO_H

#include "Personagem.h"

class Monstro : public Personagem {
private:
    int valorTempo; // tempo do bõnus
    bool capturado; // Novo estado
public:
    // Construtor simples para compilar
    Monstro(float x, float y, float vel, std::string img, int valorTempoBonus) 
        : Personagem(x, y, vel, img), valorTempo(valorTempoBonus), capturado(false) {}
        
    // Implementação obrigatória do método virtual puro
    void atualizar(float deltaTime) override { /* Lógica futura */ }

    // Método necessário para a Máquina de Reciclagem
    int getValorTempo() const { return valorTempo; } // Retorna o tempo em segundos de bônus

    // Métodos para a mecânica de jogo
    void capturar() { capturado = true; } // Muda o estado
    bool estaCapturado() const { return capturado; } // Checa o estado
};

#endif
