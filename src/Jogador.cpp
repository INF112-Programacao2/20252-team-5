#include "../include/Jogador.h"
#include "../include/VariaveisGlobais.h"
#include <cmath>
#include <iostream>
#include <SFML/Window/Keyboard.hpp>

Jogador::Jogador(float x, float y, float velocidade, std::string imagem)
    : Personagem(x, y, velocidade, imagem)
{
    monstroCarregado = nullptr;

    if (!_textureAndandoEsquerda.loadFromFile("assets/textures/player/andando2_esquerda.png"))
    {
        std::cerr << "ERRO FATAL: Nao foi possivel carregar a textura andando2_esquerda.png" << std::endl;
        throw std::runtime_error("Erro ao carregar \"" + imagem + "\".");
    }

    if (!_textureAndandoDireita.loadFromFile("assets/textures/player/andando2_direita.png"))
    {
        std::cerr << "ERRO FATAL: Nao foi possivel carregar a textura andando2_direita.png" << std::endl;
        throw std::runtime_error("Erro ao carregar \"" + imagem + "\".");
    }

    if (!_textureParadoEsquerda.loadFromFile("assets/textures/player/parado_esquerda.png"))
    {
        std::cerr << "ERRO FATAL: Nao foi possivel carregar a textura parado_esquerda.png" << std::endl;
        throw std::runtime_error("Erro ao carregar \"" + imagem + "\".");
    }

    if (!_textureParadoDireita.loadFromFile("assets/textures/player/parado_direita.png"))
    {
        std::cerr << "ERRO FATAL: Nao foi possivel carregar a textura parado_direita.png" << std::endl;
        throw std::runtime_error("Erro ao carregar \"" + imagem + "\".");
    }
}

Jogador::~Jogador()
{
}

void Jogador::atualizar(float deltaTime, const Fase &fase)
{

    tempoAcumulado += deltaTime;

    float largura = _sprite.getLocalBounds().width;
    float altura = _sprite.getLocalBounds().height;

    float dist = _velocidade * deltaTime * 50.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !_jump)
    {
        if (colisao(Direcao::CAINDO, 1.f, fase))
        {
            _jump = true;
            _velY = -FORCA_JUMP;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        mudarPosicao(Direcao::ESQUERDA, deltaTime, fase);

        if (tempoAcumulado >= tempoIntervalo)
        {
            _sprite.setOrigin(largura / 2.0f, (altura / 2.0f) - 15.0f);
            _sprite.setScale(0.8f,0.8f);

            if (movendoHorizontalmente)
            {
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
        mudarPosicao(Direcao::DIREITA, deltaTime, fase);

        if (tempoAcumulado >= tempoIntervalo)
        {
            _sprite.setOrigin(largura / 2.0f, (altura / 2.0f) - 15.0f);
            _sprite.setScale(0.8f,0.8f);
            
            if (movendoHorizontalmente)
            {
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

    float MovVert = _velY * deltaTime;

    if (MovVert < 0.f)
    {
        if (colisao(Direcao::CIMA, -MovVert, fase))
        {
            int tileAcima = floorf((_y - (-MovVert)) / TAM_PIXEL);
            float novaY = (float(tileAcima * TAM_PIXEL)) + TAM_PIXEL;

            setY(novaY);
            _velY = 0.f;
            MovVert = 0.f;
        }
    }

    if (MovVert > 0.f)
    {
        if (colisao(Direcao::CAINDO, MovVert, fase))
        {
            int tileAbaixo = floorf((_y + TAM_PIXEL + ceil(MovVert)) / TAM_PIXEL);

            float novaY = (float(tileAbaixo * TAM_PIXEL)) - TAM_PIXEL;
            setY(novaY);

            _velY = 0.f;
            _jump = false;
            MovVert = 0.f;
        }
    }

    if (MovVert != 0.f)
    {
    }
    if (MovVert != 0.f)
    {
        setY(_y + MovVert);
    }

    _velY += GRAVITY * deltaTime;

    if (monstroCarregado != nullptr)
    {
        monstroCarregado->setX(_x);
        monstroCarregado->setY(_y);
    }
}

Monstro *Jogador::getMonstroCarregado() const
{
    return monstroCarregado;
}

void Jogador::setMonstroCarregado(Monstro *monstro)
{
    monstroCarregado = monstro;
}