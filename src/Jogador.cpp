#include "../include/Jogador.h"
#include "../include/VariaveisGlobais.h" // Se PowerUp foi removido, inclua VariaveisGlobais.h se ela contiver constantes importantes.
#include <cmath>                    // Para ceil e floorf
#include <iostream>                 // Para cout e endl
#include <SFML/Window/Keyboard.hpp> // Necessário para detectar teclas

// Construtor: Repassa os dados para a classe pai (Personagem)
// Note que usamos std::string para o caminho da imagem, igual ao Personagem.cpp
Jogador::Jogador(float x, float y, float velocidade, std::string imagem)
    : Personagem(x, y, velocidade, imagem)
{
    // Removido: powerUpAtivo = nullptr;
    monstroCarregado = nullptr;

    // Textura esquerda andando
    if (!_textureAndandoEsquerda.loadFromFile("assets/textures/player/andando2_esquerda.png"))
    {
        std::cerr << "ERRO FATAL: Nao foi possivel carregar a textura andando2_esquerda.png" << std::endl;
        throw std::runtime_error("Erro ao carregar \"" + imagem + "\".");
    }

    // Textura direita andando
    if (!_textureAndandoDireita.loadFromFile("assets/textures/player/andando2_direita.png"))
    {
        std::cerr << "ERRO FATAL: Nao foi possivel carregar a textura andando2_direita.png" << std::endl;
        throw std::runtime_error("Erro ao carregar \"" + imagem + "\".");
    }

    // Textura esquerda parado
    if (!_textureParadoEsquerda.loadFromFile("assets/textures/player/parado_esquerda.png"))
    {
        std::cerr << "ERRO FATAL: Nao foi possivel carregar a textura parado_esquerda.png" << std::endl;
        throw std::runtime_error("Erro ao carregar \"" + imagem + "\".");
    }

    // Textura direita parado
    if (!_textureParadoDireita.loadFromFile("assets/textures/player/parado_direita.png"))
    {
        std::cerr << "ERRO FATAL: Nao foi possivel carregar a textura parado_direita.png" << std::endl;
        throw std::runtime_error("Erro ao carregar \"" + imagem + "\".");
    }
}

Jogador::~Jogador()
{
}

// Método principal de controle do Jogador
void Jogador::atualizar(float deltaTime, const Fase &fase)
{

    tempoAcumulado += deltaTime;

    // Obtém a largura e altura do sprite
    float largura = _sprite.getLocalBounds().width;
    float altura = _sprite.getLocalBounds().height;

    // O deltaTime ajuda a manter a velocidade constante independente do FPS
    float dist = _velocidade * deltaTime * 50.0f; // Multiplicador para ajustar escala

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !_jump)
    {
        if (colisao(Direcao::CAINDO, 1.f, fase))
        {
            _jump = true;
            _velY = -FORCA_JUMP;
        }
    }

    // tirei o de ir para baixo porque existe gravidade, caso seja possível ele descer de uma plataforma para outra
    // é só adicionar de volta

    // else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    // {
    //     mudarPosicao(_x, _y + dist);
    // }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        // Agora 'fase' existe e pode ser usada na chamada
        mudarPosicao(Direcao::ESQUERDA, deltaTime, fase);

        if (tempoAcumulado >= tempoIntervalo)
        {
            _sprite.setOrigin(largura / 2.0f, (altura / 2.0f) - 15.0f);
            _sprite.setScale(0.8f,0.8f);

            if (movendoHorizontalmente)
            {
                // Usa a nova textura pré-carregada
                _sprite.setTexture(_textureAndandoEsquerda);
                movendoHorizontalmente = false;
            }
            else
            {
                _sprite.setTexture(_textureParadoEsquerda);
                movendoHorizontalmente = true;
            }
            tempoAcumulado = 0.0f;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        // Agora 'fase' existe e pode ser usada na chamada
        mudarPosicao(Direcao::DIREITA, deltaTime, fase);

        if (tempoAcumulado >= tempoIntervalo)
        {
            _sprite.setOrigin(largura / 2.0f, (altura / 2.0f) - 15.0f);
            _sprite.setScale(0.8f,0.8f);
            
            if (movendoHorizontalmente)
            {
                // Usa a nova textura pré-carregada
                _sprite.setTexture(_textureAndandoDireita);
                movendoHorizontalmente = false;
            }
            else
            {
                _sprite.setTexture(_textureParadoDireita);
                movendoHorizontalmente = true;
            }
            tempoAcumulado = 0.0f;
        }
    }

    /////// Pulo e queda (Corrigido para usar membros da classe e 'deltaTime') ////////
    float MovVert = _velY * deltaTime;

    if (MovVert < 0.f)
    { // se o jogador está subindo
        if (colisao(Direcao::CIMA, -MovVert, fase))
        { // Usando 'colisao' do Personagem
            int tileAcima = floorf((_y - (-MovVert)) / TAM_PIXEL);
            float novaY = (float(tileAcima * TAM_PIXEL)) + TAM_PIXEL;

            setY(novaY);
            _velY = 0.f;
            MovVert = 0.f;
        }
    }

    if (MovVert > 0.f)
    { // se o jogador está caindo
        if (colisao(Direcao::CAINDO, MovVert, fase))
        { // Usando 'colisao' do Personagem
            int tileAbaixo = floorf((_y + TAM_PIXEL + ceil(MovVert)) / TAM_PIXEL);
            // calcula o proximo bloco da matriz imediatamenta abaixo do personagem

            float novaY = (float(tileAbaixo * TAM_PIXEL)) - TAM_PIXEL;
            // define a nova coordenada y como o pixel acima do chão
            setY(novaY);

            _velY = 0.f;
            _jump = false;
            MovVert = 0.f;
            // zera as velocidades pois ele chegou ao chão
        }
    }

    if (MovVert != 0.f)
    {
    }
    if (MovVert != 0.f)
    {
        // caso não ocorra nenhuma das colisões acima listadas, a coordenada é atualizada
        setY(_y + MovVert);
    }

    _velY += GRAVITY * deltaTime; // atualiza a velocidade constantemente por conta da gravidade

    // Se estiver carregando um inimigo, move o monstro junto
    if (monstroCarregado != nullptr)
    {
        monstroCarregado->setX(_x);
        monstroCarregado->setY(_y);
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
