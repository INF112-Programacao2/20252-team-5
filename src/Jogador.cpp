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
        _jump = true;
        
    }

    //tirei o de ir para baixo porque existe gravidade, caso seja possível ele descer de uma plataforma para outra
    //é só adicionar de volta

    // else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    // {
    //     mudarPosicao(_x, _y + dist);
    // }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        mudarPosicao(Direcao::ESQUERDA, deltaTime, fase);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        mudarPosicao(Direcao::DIREITA, deltaTime, fase);
    }

    // Se estiver carregando um inimigo, move o monstro junto
    if (monstroCarregado != nullptr)
    {
        monstroCarregado->mudarPosicao(_x, _y); 
    }
}

// Métodos set e get de MonstroCarregado
Monstro *Jogador::getMonstroCarregado() const
{
    return monstroCarregado;
}

void Jogador::setMonstroCarregado(Monstro *monstro)
{
    monstroCarregado = monstro;
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
