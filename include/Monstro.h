#ifndef MONSTRO_H
#define MONSTRO_H

#include "Personagem.h"

class Monstro : public Personagem {
public:
    // Construtor simples para compilar
    Monstro(float x, float y, float vel, std::string img) 
        : Personagem(x, y, vel, img) {}
        
    // Implementação obrigatória do método virtual puro
    void atualizar(float deltaTime) override { /* Lógica futura */ }

    // Método necessário para a Máquina de Reciclagem
    int getValorTempo() const { return 10; } // Retorna 10 segundos de bônus, por exemplo
};

#endif