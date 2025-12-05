#include "../include/Fase.h"
#include "../include/Timer.h"
#include "../include/Personagem.h"
#include "../include/MaquinaDeReciclagem.h"
#include "../include/Jogador.h"
#include "../include/Monstro.h"
#include "../include/VariaveisGlobais.h"

#include <cstring>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <random>
#include <ctime>

const float RAIO_INTERACAO = TAM_PIXEL * 2.0f;

Fase::Fase(int inicioTempo, int numMonstros)
    : tempoInicial(inicioTempo),
      quantidadeMonstros(numMonstros),
      timer(nullptr),
      maquina(nullptr)
{
    
    this->timer = new Timer(inicioTempo);

    std::string path = "assets/textures/block.png";
    if (!texturaTile.loadFromFile(path))
        std::cerr << "Erro ao carregar textura do tile: " << path << std::endl;
    else
        std::cout << "Textura carregada: " << texturaTile.getSize().x << "x" << texturaTile.getSize().y << std::endl;

    carregarMapa(1);

    inicializarEntidades();
}

Fase::~Fase()
{
    delete timer;
    delete maquina;

    for (Personagem *entidade : entidades)
        delete entidade;
    entidades.clear();
}

int Fase::getTempoInicial() const
{
    return tempoInicial;
}

int Fase::getQuantidadeMonstros() const
{
    return quantidadeMonstros;
}

const char *Fase::getMapa(int linha) const
{
    if (linha >= 0 && linha < MAPA_LINHAS)
    {
        return mapa[linha];
    }
    return nullptr;
}

std::vector<Personagem *> &Fase::getEntidades()
{
    return entidades;
}

Timer *Fase::getTimer() const
{
    return timer;
}

void Fase::carregarMapa(int nivel)
{
    std::string path = "assets/layout/nivel" + std::to_string(nivel) + ".txt";
    std::ifstream arquivo(path);

    if (!arquivo.is_open())
    {
        std::cerr << "Erro ao abrir arquivo de mapa: " << path << std::endl;
        return;
    }

    std::cout << "Arquivo de mapa aberto com sucesso!" << std::endl;

    std::string linha_coordenadas;
    if (std::getline(arquivo, linha_coordenadas))
    {
        std::cout << "Coordenadas brutas lidas: " << linha_coordenadas << std::endl;
    }
    else
    {
        std::cerr << "Erro: Falha na leitura da 2ª linha (coordenadas)." << std::endl;
        arquivo.close();
        return;
    }

    std::stringstream ss(linha_coordenadas);
    std::string par_str;

    while (std::getline(ss, par_str, ' '))
    {
        size_t pos_virgula = par_str.find(',');

        if (pos_virgula != std::string::npos)
        {
            try {
                std::string x_str = par_str.substr(0, pos_virgula);
                std::string y_str = par_str.substr(pos_virgula + 1);

                int x = std::stoi(x_str);
                int y = std::stoi(y_str);

                plataformas.emplace_back(x, y);

            } catch (const std::exception& e) {
                std::cerr << "Erro ao processar par de coordenadas: " << par_str << ". Ignorando." << std::endl;
            }
        }
    }

    std::string linha;
    int linhaAtual = 0;

    while (std::getline(arquivo, linha) && linhaAtual < MAPA_LINHAS)
    {
        int colunas = std::min((int)linha.length(), MAPA_COLUNAS);
        std::strncpy(mapa[linhaAtual], linha.c_str(), colunas);

        for (int j = colunas; j < MAPA_COLUNAS; ++j)
        {
            mapa[linhaAtual][j] = '0';
        }

        mapa[linhaAtual][MAPA_COLUNAS] = '\0';
        linhaAtual++;
    }

    for (int i = linhaAtual; i < MAPA_LINHAS; ++i)
    {
        std::memset(mapa[i], '0', MAPA_COLUNAS);
        mapa[i][MAPA_COLUNAS] = '\0';
    }

    arquivo.close();

    std::cout << "Mapa carregado com sucesso: " << path << std::endl;
}

void Fase::inicializarEntidades()
{
    float Maquina_x = plataformas[1].first * TAM_PIXEL;
    float Maquina_y = plataformas[1].second * TAM_PIXEL;
    this->maquina = new MaquinaDeReciclagem(Maquina_x, Maquina_y, this, timer, "assets/textures/MaquinaDeRec/Maquina.png");

    float jogador_x = plataformas[0].first * TAM_PIXEL;
    float jogador_y = plataformas[0].second * TAM_PIXEL;

    std::mt19937 gen(static_cast<unsigned int>(time(nullptr)));
    std::uniform_int_distribution<> dist(0, plataformas.size() - 1);

    try
    {
        // Criar Jogador (Posição X, Y, Velocidade, Caminho da Textura) sempre na 1a posição do vetor
        entidades.push_back(new Jogador(
            jogador_x, jogador_y, 300.0f,
            "assets/textures/player/andando2_direita.png"
            ));
        std::cout << "Jogador criado com sucesso." << std::endl;

        // Criar Monstros (adição simples por enquanto)
        for (int i = 0; i < quantidadeMonstros; i++)
        {
            int n;
            do {
                n = dist(gen);
            } while (n < 2);
            float x = plataformas[n].first * TAM_PIXEL;
            float y = plataformas[n].second * TAM_PIXEL;

            // Monstro concreto (Perseguidor) - Pos X, Pos Y, Velocidade, Textura, valorTempoBonus
            entidades.push_back(
                new Perseguidor(
                    x, y, 200.f,
                    "assets/textures/monstro1/andando1_direita.png",
                    10));
        }
        std::cout << "Monstros criados com sucesso: " << quantidadeMonstros << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Erro ao inicializar entidades: " << e.what() << std::endl;
    }
}

void Fase::removerEntidade(Personagem *entidade)
{
    auto iterador = std::remove(entidades.begin(), entidades.end(), entidade);
    if (iterador != entidades.end())
    {
        entidades.erase(iterador, entidades.end());
        delete entidade;
    }
}

void Fase::atualizar(float deltaTime)
{
    Jogador *jogador = dynamic_cast<Jogador *>(entidades[0]);

    if (jogador)
    {
        jogador->atualizar(deltaTime, *this);

        Monstro *monstroCarregado = jogador->getMonstroCarregado();

        if (monstroCarregado == nullptr)
        {
            for (size_t i = 1; i < entidades.size(); ++i)
            {
                Monstro *monstro = dynamic_cast<Monstro *>(entidades[i]);
                if (monstro && !monstro->estaCapturado())
                {
                    if (jogador->getSprite().getGlobalBounds().intersects(monstro->getSprite().getGlobalBounds()))
                    {
                        monstro->capturar();
                        jogador->setMonstroCarregado(monstro);
                        break;
                    }
                }
            }
        }
        else
        {
            float maquinaX = static_cast<float>(maquina->getPosicaoX());
            float maquinaY = static_cast<float>(maquina->getPosicaoY());
            float jogadorX = jogador->getPosicaoX();
            float jogadorY = jogador->getPosicaoY();

            float distancia = std::sqrt(std::pow(jogadorX - maquinaX, 2) + std::pow(jogadorY - maquinaY, 2));

            if (distancia < RAIO_INTERACAO)
            {
                if (monstroCarregado)
                {
                    maquina->receberInimigo(monstroCarregado);
                    jogador->setMonstroCarregado(nullptr);
                }
            }
        }
    }

    for (size_t i = 1; i < entidades.size(); ++i)
    {
        Monstro *monstro = dynamic_cast<Monstro *>(entidades[i]);
        if (monstro && !monstro->estaCapturado())
        {
            monstro->comportamento(*jogador, deltaTime, *this);
        }
    }

    if (verificarDerrota())
    {
        std::cout << "Tempo Esgotado!" << std::endl;
    }
}

void Fase::desenhar(sf::RenderWindow &window)
{
    try
    {
        for (int linha = 0; linha < MAPA_LINHAS; linha++)
        {
            for (int coluna = 0; coluna < MAPA_COLUNAS; coluna++)
            {
                char tile = mapa[linha][coluna];

                if (tile == '1')
                {
                    sf::Sprite sprite(texturaTile);
                    sprite.setPosition(coluna * TAM_PIXEL, linha * TAM_PIXEL);
                    sprite.setScale(static_cast<float>(TAM_PIXEL) / texturaTile.getSize().x,
                                    static_cast<float>(TAM_PIXEL) / texturaTile.getSize().y);
                    window.draw(sprite);
                }
                else if (tile == '3')
                {
                    sf::Sprite sprite(texturaTile);
                    sprite.setColor(sf::Color(255, 255, 255, 127));
                    sprite.setPosition(coluna * TAM_PIXEL, linha * TAM_PIXEL);
                    sprite.setScale(static_cast<float>(TAM_PIXEL) / texturaTile.getSize().x,
                                    static_cast<float>(TAM_PIXEL) / texturaTile.getSize().y);
                    window.draw(sprite);
                }
            }
        }

        if (maquina)
        {
            maquina->desenhar(window);
        }

        for (Personagem *entidade : entidades)
        {
            entidade->desenhar(window);
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Erro ao desenhar fase: " << e.what() << std::endl;
    }
}

void Fase::detectarVitoria()
{
}

bool Fase::verificarDerrota() const
{
    if (timer)
        return timer->tempoZerou();
    return false;
}