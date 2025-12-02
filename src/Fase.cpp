#include "../include/Fase.h"
#include "../include/Timer.h"
#include "../include/Personagem.h"
#include "../include/MaquinaDeReciclagem.h"
#include "../include/Jogador.h"          // <--- NECESSÁRIO para criar Jogador
#include "../include/Monstro.h"          // <--- NECESSÁRIO para criar o vetor de entidades
#include "../include/VariaveisGlobais.h" // Para TAM_PIXEL

#include <cstring>
#include <iostream>
#include <fstream>
#include <algorithm> // Para usar std::remove e std::erase
#include <cmath>     // Para calcular o raio de interação

// Coordenadas fixas para a máquina (ajuste conforme seu mapa)
const float MAQUINA_X = 100.0f;
const float MAQUINA_Y = 100.0f;

// Raio de interação para interagir com a máquina de reciclagem
const float RAIO_INTERACAO = TAM_PIXEL * 2.0f;

Fase::Fase(int inicioTempo, int numMonstros)
    : tempoInicial(inicioTempo),
      quantidadeMonstros(numMonstros),
      timer(nullptr),
      maquina(nullptr)
{
    this->timer = new Timer(inicioTempo);

    this->maquina = new MaquinaDeReciclagem(MAQUINA_X, MAQUINA_Y, this, timer, "../assets/textures/MaquinaDeRec/Maquina.png");

    // 3. Carregar textura do tile
    std::string path = "../assets/textures/block.png";
    if (!texturaTile.loadFromFile(path))
        std::cerr << "Erro ao carregar textura do tile: " << path << std::endl;
    else
        std::cout << "Textura carregada: " << texturaTile.getSize().x << "x" << texturaTile.getSize().y << std::endl;

    carregarMapa(1); // Provisório: sempre carrega o nível 1

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

// Getters
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
    std::string path = "../assets/layout/nivel" + std::to_string(nivel) + ".txt";
    std::ifstream arquivo(path);

    if (!arquivo.is_open())
    {
        std::cerr << "Erro ao abrir arquivo de mapa: " << path << std::endl;
        return;
    }

    std::cout << "Arquivo de mapa aberto com sucesso!" << std::endl;
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

    /*while (std::getline(arquivo, linha) && linhaAtual < MAPA_LINHAS)
    {
        int colunas = std::min((int)linha.length(), MAPA_COLUNAS);
        std::strncpy(mapa[linhaAtual], linha.c_str(), colunas);

        mapa[linhaAtual][MAPA_COLUNAS] = '\0';
        linhaAtual++;
    }

    arquivo.close();*/
    std::cout << "Mapa carregado com sucesso: " << path << std::endl;
}

void Fase::inicializarEntidades()
{
    try
    {
        // Criar Jogador (Posição X, Y, Velocidade, Caminho da Textura) sempre na 1a posição do vetor
        entidades.push_back(new Jogador(
            50.0f, 50.0f, 300.0f,
            "../assets/textures/player/andando2_direita.png" // Provisório, já que ainda não tem animação
            ));
        std::cout << "Jogador criado com sucesso." << std::endl;

        // Criar Monstros (adição simples por enquanto)
        for (int i = 0; i < quantidadeMonstros / 2; i++)
        {
            // Monstro concreto (Perseguidor) - Pos X, Pos Y, Velocidade, Textura, valorTempoBonus
            entidades.push_back(
                new Perseguidor(
                    800.f + i * 50.0f, 640.f, 300.f,
                    "../assets/textures/monstro1/andando1_direita.png", // Provisório, já que ainda não tem animação
                    10));
        }
        for (int i = quantidadeMonstros / 2; i < quantidadeMonstros; i++)
        {
            // Monstro concreto (Perseguidor) - Pos X, Pos Y, Velocidade, Textura, valorTempoBonus
            entidades.push_back(
                new Perseguidor(
                    200.f + i * 50.0f, 640.f, 300.f,
                    "../assets/textures/monstro1/andando1_direita.png", // Provisório, já que ainda não tem animação
                    10));
        }
        std::cout << "Monstros criados com sucesso: " << quantidadeMonstros << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Erro ao inicializar entidades: " << e.what() << std::endl;
    }
}

// Nova função: Remove a entidade (Monstro) do vetor e libera a memória
void Fase::removerEntidade(Personagem *entidade)
{
    // Usa std::remove para mover o elemento para o final e erase para remover
    auto iterador = std::remove(entidades.begin(), entidades.end(), entidade);
    if (iterador != entidades.end())
    {
        // Erase para remover
        entidades.erase(iterador, entidades.end());
        delete entidade; // Liberar a memória alocada
    }
}
// Nova função: Remove a entidade (Monstro) do vetor e libera a memória
void Fase::removerEntidade(Personagem *entidade)
{
    // Usa std::remove para mover o elemento para o final e erase para remover
    auto iterador = std::remove(entidades.begin(), entidades.end(), entidade);
    if (iterador != entidades.end())
    {
        // Erase para remover
        entidades.erase(iterador, entidades.end());
        delete entidade; // Liberar a memória alocada
    }
}

void Fase::atualizar(float deltaTime)
{
    Jogador *jogador = dynamic_cast<Jogador *>(entidades[0]);

    if (jogador)
    {
        // Atualiza a posição do jogador (e do monstro carregado, se houver)
        jogador->atualizar(deltaTime, *this);

        Monstro *monstroCarregado = jogador->getMonstroCarregado();

        if (monstroCarregado == nullptr)
        {
            // Tentar capturar um monstro, se não estiver carregando um
            for (size_t i = 1; i < entidades.size(); ++i)
            {
                Monstro *monstro = dynamic_cast<Monstro *>(entidades[i]);
                if (monstro && !monstro->estaCapturado())
                {
                    // Checagem de colisão usando o GlobalBounds do SFML
                    if (jogador->getSprite().getGlobalBounds().intersects(monstro->getSprite().getGlobalBounds()))
                    {
                        // Ação da captura
                        monstro->capturar();
                        jogador->setMonstroCarregado(monstro);
                        break;
                    }
                }
            }
        }
        else
        {
            // Lógica de entrega na Máquina, se estiver carregando um monstro
            float maquinaX = static_cast<float>(maquina->getPosicaoX());
            float maquinaY = static_cast<float>(maquina->getPosicaoY());
            float jogadorX = jogador->getPosicaoX();
            float jogadorY = jogador->getPosicaoY();

            // Simulando a proximidade da máquina
            float distancia = std::sqrt(std::pow(jogadorX - maquinaX, 2) + std::pow(jogadorY - maquinaY, 2));

            if (distancia < RAIO_INTERACAO)
            {
                if (monstroCarregado)
                {
                    maquina->receberInimigo(monstroCarregado); // A Máquina interaje com Timer e chama a remoção
                    jogador->setMonstroCarregado(nullptr);     // Jogador não carrega mais
                }
            }
        }
    }

    // Atualizar Monstros que não estão capturados
    for (size_t i = 1; i < entidades.size(); ++i)
    {
        Monstro *monstro = dynamic_cast<Monstro *>(entidades[i]);
        if (monstro && !monstro->estaCapturado())
        {
            // Método com polimorfismo (futuramente)
            monstro->comportamento(*jogador, deltaTime, *this);
        }
    }

    // Verificação de Derrota ou Vitória (o Jogo fará a mudança de Status)
    if (verificarDerrota())
    {
        // Logica de derrota
        std::cout << "Tempo Esgotado!" << std::endl;
        // A fase apenas notifica a condição, o Jogo muda o Status
    }
}

void Fase::desenhar(sf::RenderWindow &window)
{
    try
    {
        // Desenhar Mapa com sprites da textura
        for (int linha = 0; linha < MAPA_LINHAS; linha++)
        {
            for (int coluna = 0; coluna < MAPA_COLUNAS; coluna++)
            {
                char tile = mapa[linha][coluna];

                // Se o tile é '1', desenha sprite do block
                if (tile == '1')
                {
                    sf::Sprite sprite(texturaTile);
                    sprite.setPosition(coluna * TAM_PIXEL, linha * TAM_PIXEL);
                    sprite.setScale(static_cast<float>(TAM_PIXEL) / texturaTile.getSize().x,
                                    static_cast<float>(TAM_PIXEL) / texturaTile.getSize().y);
                    window.draw(sprite);
                }
                else if (tile == '2')
                {
                    sf::Sprite sprite(texturaTile);
                    sprite.setColor(sf::Color(64, 224, 208, 127));
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

        // Desenhar Máquina
        if (maquina)
        {
            maquina->desenhar(window);
        }

        // Desenhar Todas as Entidades
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
    // Lógica de vitória
}

bool Fase::verificarDerrota() const
{
    if (timer)
        return timer->tempoZerou();
    return false;
}
