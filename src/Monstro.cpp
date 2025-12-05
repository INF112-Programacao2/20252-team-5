#include <cmath>
#include <random>
#include <iostream>
#include "../include/Monstro.h"
#include "../include/Personagem.h"
#include "../include/Jogador.h"
#include "../include/Fase.h"

///////// MONSTRO - CLASSE MÃE //////////

Monstro::Monstro(float x, float y, float velocidade, std::string imagem, int tempo)
    : Personagem(x, y, velocidade, imagem), _valorTempo(tempo), _capturado(false)
{
    float escala = (float)TAM_PIXEL / _texture.getSize().x;
    _sprite.setScale(escala, escala);
}

int Monstro::getValorTempo() const
{
    return _valorTempo;
}

void Monstro::receberCaptura()
{
    _capturado = true;
}

void Monstro::capturar()
{
    receberCaptura();
}

bool Monstro::estaCapturado() const
{
    return _capturado;
}

void Monstro::atualizar(float deltaTime, const Fase &fase)
{
    // Placeholder: monstros não fazem nada por enquanto na atualização genérica.
    // Comportamentos específicos (perseguir, esconder) podem ser implementados
    // em comportamento(Jogador) quando integrado com a lógica do Jogador.
}

///////// PERSEGUIDOR /////////

Perseguidor::Perseguidor(float x, float y, float velocidade, std::string imagem, int tempo)
    : Monstro(x, y, velocidade, imagem, tempo)
{
    // Textura esquerda andando
    if (!_textureAndandoEsquerda.loadFromFile("../assets/textures/monstro1/andando2_esquerda.png"))
    {
        std::cerr << "ERRO FATAL: Nao foi possivel carregar a textura andando2_esquerda.png" << std::endl;
        throw std::runtime_error("Erro ao carregar \"" + imagem + "\".");
    }

    // Textura direita andando
    if (!_textureAndandoDireita.loadFromFile("../assets/textures/monstro1/andando2_direita.png"))
    {
        std::cerr << "ERRO FATAL: Nao foi possivel carregar a textura andando2_direita.png" << std::endl;
        throw std::runtime_error("Erro ao carregar \"" + imagem + "\".");
    }

    // Textura esquerda parado
    if (!_textureParadoEsquerda.loadFromFile("../assets/textures/monstro1/parado_esquerda.png"))
    {
        std::cerr << "ERRO FATAL: Nao foi possivel carregar a textura parado_esquerda.png" << std::endl;
        throw std::runtime_error("Erro ao carregar \"" + imagem + "\".");
    }

    // Textura direita parado
    if (!_textureParadoDireita.loadFromFile("../assets/textures/monstro1/parado_direita.png"))
    {
        std::cerr << "ERRO FATAL: Nao foi possivel carregar a textura parado_direita.png" << std::endl;
        throw std::runtime_error("Erro ao carregar \"" + imagem + "\".");
    }
}

void Perseguidor::comportamento(const Jogador &jogador, float dt, const Fase &fase)
{
    tempoAcumulado += dt;

    // Obtém a largura e altura do sprite
    float largura = _sprite.getLocalBounds().width;
    float altura = _sprite.getLocalBounds().height;

    float px = getPosicaoX();
    float py = getPosicaoY();

    float jx = jogador.getPosicaoX();
    float jy = jogador.getPosicaoY();

    float dx = px - jx;
    float dy = py - jy;
    float dist = std::sqrt(dx * dx + dy * dy); // distancia entre o player e o monstrinho

    int tileX = floorf(px / TAM_PIXEL); // posição no eixo x em relação à matriz
    int tileY = floorf(py / TAM_PIXEL); // posição no eixo y em relação à matriz

    // verifica se há parede ou queda a frente, se houver, muda a direção do movimento
    if (_direcao == Direcao::DIREITA)
    {
        if (colisao(_direcao, 1.f, fase) || fase.getMapa(tileY + 1)[tileX + 1] == '0')
        {
            _direcao = Direcao::ESQUERDA;
        }
        else
        {
            mudarPosicao(_direcao, dt, fase);

            if (tempoAcumulado >= tempoIntervalo)
            {
                if (movendoHorizontalmente)
                {
                    // Usa a nova textura pré-carregada
                    _sprite2.setTexture(_textureAndandoDireita);
                    _sprite2.setOrigin(largura / 2.0f, (altura / 2.0f) - 25.0f);
                    _sprite2.setScale(0.6f, 0.6f);
                    _sprite = _sprite2;
                    movendoHorizontalmente = false;
                }
                else
                {
                    _sprite2.setTexture(_textureParadoDireita);
                    _sprite2.setOrigin(largura / 2.0f, (altura / 2.0f) - 25.0f);
                    _sprite2.setScale(0.6f, 0.6f);
                    _sprite = _sprite2;
                    movendoHorizontalmente = true;
                }
                tempoAcumulado = 0.0f;
            }
        }
    }
    else if (_direcao == Direcao::ESQUERDA)
    {
        if (colisao(_direcao, 1.f, fase) || fase.getMapa(tileY + 1)[tileX - 1] == '0')
        {
            _direcao = Direcao::DIREITA;
        }
        else
        {
            mudarPosicao(_direcao, dt, fase);

            if (tempoAcumulado >= tempoIntervalo)
            {
                if (movendoHorizontalmente)
                {
                    // Usa a nova textura pré-carregada
                    _sprite2.setTexture(_textureAndandoEsquerda);
                    _sprite2.setOrigin(largura / 2.0f, (altura / 2.0f) - 25.0f);
                    _sprite2.setScale(0.6f, 0.6f);
                    _sprite = _sprite2;
                    movendoHorizontalmente = false;
                }
                else
                {
                    _sprite2.setTexture(_textureParadoEsquerda);
                    _sprite2.setOrigin(largura / 2.0f, (altura / 2.0f) - 25.0f);
                    _sprite2.setScale(0.6f, 0.6f);
                    _sprite = _sprite2;
                    movendoHorizontalmente = true;
                }
                tempoAcumulado = 0.0f;
            }
        }
    }

    if (dist < 150)
    { // se o jogador se aproximar, o monstro foge do player
        if (dx < 0)
            _direcao = Direcao::ESQUERDA;
        else
            _direcao = Direcao::DIREITA;
    }
}

///////// ESCONDEDOR /////////

Escondedor::Escondedor(float x, float y, float velocidade, std::string imagem, int tempo) : Monstro(x, y, velocidade, imagem, tempo)
{

    // Textura esquerda andando
    if (!_textureAndandoEsquerda.loadFromFile("../assets/textures/monstro1/andando2_esquerda.png"))
    {
        std::cerr << "ERRO FATAL: Nao foi possivel carregar a textura andando2_esquerda.png" << std::endl;
        throw std::runtime_error("Erro ao carregar \"" + imagem + "\".");
    }

    // Textura direita andando
    if (!_textureAndandoDireita.loadFromFile("../assets/textures/monstro1/andando2_direita.png"))
    {
        std::cerr << "ERRO FATAL: Nao foi possivel carregar a textura andando2_direita.png" << std::endl;
        throw std::runtime_error("Erro ao carregar \"" + imagem + "\".");
    }

    // Textura esquerda parado
    if (!_textureParadoEsquerda.loadFromFile("../assets/textures/monstro1/parado_esquerda.png"))
    {
        std::cerr << "ERRO FATAL: Nao foi possivel carregar a textura parado_esquerda.png" << std::endl;
        throw std::runtime_error("Erro ao carregar \"" + imagem + "\".");
    }

    // Textura direita parado
    if (!_textureParadoDireita.loadFromFile("../assets/textures/monstro1/parado_direita.png"))
    {
        std::cerr << "ERRO FATAL: Nao foi possivel carregar a textura parado_direita.png" << std::endl;
        throw std::runtime_error("Erro ao carregar \"" + imagem + "\".");
    }
}

void Escondedor::comportamento(const Jogador &jogador, float dt, const Fase &fase)
{
    tempoAcumulado += dt;

    // Obtém a largura e altura do sprite
    float largura = _sprite.getLocalBounds().width;
    float altura = _sprite.getLocalBounds().height;
    
    // calculando a distância entre o monstro e o jogador
    // CORRIGIDO: getQuantidadeMonstros é uma função e getX/getY usam _
    int qtd = fase.getQuantidadeMonstros();
    float dtt = dt;
    srand(time(nullptr));

    float jx = jogador.getPosicaoX();
    float jy = jogador.getPosicaoY();

    float dx = _x - jx;
    float dy = _y - jy;
    float dist = std::sqrt(dx * dx + dy * dy); // distancia entre o player e o monstrinho

    int tileX = floorf(_x / TAM_PIXEL); // posição no eixo x em relação à matriz
    int tileY = floorf(_y / TAM_PIXEL); // posição no eixo y em relação à matriz

    if (dist >= 150)
    {                                // se o player estiver distante
        _escondido = false;          // não está mais escondido
        _direcao = Direcao::DIREITA; // não importa a direção, o importante é que ela seja válida (direita ou esquerda)
        _y = _y - TAM_PIXEL;         // sai do esconderijo;
    }

    // verifica se há parede ou queda a frente, se houver, muda a direção do movimento
    if (_direcao == Direcao::DIREITA)
    {
        if (colisao(_direcao, 1.f, fase) || fase.getMapa(tileY + 1)[tileX + 1] == '0')
        {
            _direcao = Direcao::ESQUERDA;
        }
        else
        {
            mudarPosicao(_direcao, dt, fase);

            if (tempoAcumulado >= tempoIntervalo)
            {
                if (movendoHorizontalmente)
                {
                    // Usa a nova textura pré-carregada
                    _sprite2.setTexture(_textureAndandoDireita);
                    _sprite2.setOrigin(largura / 2.0f, (altura / 2.0f) - 25.0f);
                    _sprite2.setScale(0.6f, 0.6f);
                    _sprite = _sprite2;
                    movendoHorizontalmente = false;
                }
                else
                {
                    _sprite2.setTexture(_textureParadoDireita);
                    _sprite2.setOrigin(largura / 2.0f, (altura / 2.0f) - 25.0f);
                    _sprite2.setScale(0.6f, 0.6f);
                    _sprite = _sprite2;
                    movendoHorizontalmente = true;
                }
                tempoAcumulado = 0.0f;
            }
        }
    }
    else if (_direcao == Direcao::ESQUERDA)
    {
        if (colisao(_direcao, 1.f, fase) || fase.getMapa(tileY + 1)[tileX - 1] == '0')
        {
            _direcao = Direcao::DIREITA;
        }
        else
        {
            mudarPosicao(_direcao, dt, fase);

            if (tempoAcumulado >= tempoIntervalo)
            {
                if (movendoHorizontalmente)
                {
                    // Usa a nova textura pré-carregada
                    _sprite2.setTexture(_textureAndandoEsquerda);
                    _sprite2.setOrigin(largura / 2.0f, (altura / 2.0f) - 25.0f);
                    _sprite2.setScale(0.6f, 0.6f);
                    _sprite = _sprite2;
                    movendoHorizontalmente = false;
                }
                else
                {
                    _sprite2.setTexture(_textureParadoEsquerda);
                    _sprite2.setOrigin(largura / 2.0f, (altura / 2.0f) - 25.0f);
                    _sprite2.setScale(0.6f, 0.6f);
                    _sprite = _sprite2;
                    movendoHorizontalmente = true;
                }
                tempoAcumulado = 0.0f;
            }
        }
    }

    tileX = floorf(_x / TAM_PIXEL);
    tileY = floorf(_y / TAM_PIXEL);

    if (dist < 150)
    { // se o player se aproximar, verfica:
        if (fase.getMapa(tileY + 1)[tileX] == '3')
        {                                 // se abaixo do monstrinho houver um esconderijo
            _direcao = Direcao::NENHUMA;  // para de se mover
            _escondido = true;            // fica escondido
            _y = (tileY + 1) * TAM_PIXEL; // entra no esconderijo
        }
        else if (dx < 0)
            _direcao = Direcao::ESQUERDA; // se não houver, foge do player
        else
            _direcao = Direcao::DIREITA;
    }
}
