#include "../include/Jogador.h"
#include <SFML/Window/Keyboard.hpp> // Necessário para detectar teclas

// Construtor: Repassa os dados para a classe pai (Personagem)
// Note que usamos std::string para o caminho da imagem, igual ao Personagem.cpp
Jogador::Jogador(float x, float y, float velocidade, std::string imagem)
    : Personagem(x, y, velocidade, imagem)
{
    // Inicializações específicas do Jogador (se houver) podem vir aqui
    // Ex: powerUpAtivo = nullptr;
}

// Destrutor
Jogador::~Jogador()
{
    // Limpeza se necessário
}

// Método principal de controle do Jogador
void Jogador::atualizar(float deltaTime)
{
    // O deltaTime ajuda a manter a velocidade constante independente do FPS
    float dist = _velocidade * deltaTime * 100.0f; // Multiplicador para ajustar escala

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        // mudarPosicao(_x, _y - dist); // Implementação direta sem colisão por enquanto
        // Se quiser colisão: if (!colisao(CIMA, dist, mapa)) ... (Precisamos trazer o mapa pra cá depois)
        mudarPosicao(_x, _y - dist);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        mudarPosicao(_x, _y + dist);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        mudarPosicao(_x - dist, _y);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        mudarPosicao(_x + dist, _y);
    }
}

// Métodos de PowerUp (Mantenha vazios ou com lógica básica se ainda não tiver a classe PowerUp pronta)
/*
void Jogador::ativarPowerUp(PowerUp &powerUp) {
    // Lógica futura
}

void Jogador::desativarPowerUp() {
    // Lógica futura
}

PowerUp* Jogador::getPowerUpAtivo() const {
    return powerUpAtivo;
}
*/