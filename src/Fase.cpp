#include "../include/Fase.h"
#include "../include/Timer.h"
#include "../include/Personagem.h"
#include "../include/MaquinaDeReciclagem.h"
#include "../include/Jogador.h" // <--- NECESSÁRIO para criar Jogador
#include "../include/Monstro.h"  // <--- NECESSÁRIO para criar o vetor de entidades
#include "../include/VariaveisGlobais.h" // Para TAM_PIXEL

#include <cstring>
#include <iostream>
#include <algorithm> // Para usar std::remove e std::erase
#include <cmath> // Para calcular o raio de interação

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
    // 1. Inicializar o Timer
    this->timer = new Timer(inicioTempo);

    // 2. Inicializar a Máquina (usando as constantes definidas acima)
    this->maquina = new MaquinaDeReciclagem(MAQUINA_X, MAQUINA_Y, this, timer);

    // 3. Inicializar o Mapa
    for (int i = 0; i < MAPA_LINHAS; ++i)
    {
        std::memset(mapa[i], '0', MAPA_COLUNAS);
        mapa[i][MAPA_COLUNAS] = '\0';
    }

    // 4. Inicializar Entidades
    inicializarEntidades();
}

Fase::~Fase()
{
    delete timer;
    delete maquina;

    // Limpeza correta do vetor de ponteiros
    for (Personagem *entidade : entidades)
    {
        delete entidade;
    }
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

std::vector<Personagem*>& Fase::getEntidades() 
{ 
    return entidades; 
} 

Timer* Fase::getTimer() const 
{ 
    return timer; 
} 

// Lógica
void Fase::inicializarEntidades()
{
    // 1. Criar Jogador (Posição X, Y, Velocidade, Caminho da Textura) sempre na 1a posição do vetor
    entidades.push_back(new Jogador(50.0f, 50.0f, 2.0f, "assets/textures/player.png")); 

    // 2. Criar Monstros (adição simples por enquanto)
    for(int i = 0; i < quantidadeMonstros; i++) {
        // Monstro(Posição X, Y, Velocidade, Caminho da Textura, valorTempoBonus)
        entidades.push_back(new Monstro(500.0f + i * 50.0f, 300.0f, 1.5f, "assets/textures/monster.png", 10)); 
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
Jogador *jogador = dynamic_cast<Jogador*>(entidades[0]);

    if (jogador)
    {
        // Atualiza a posição do jogador (e do monstro carregado, se houver)
        jogador->atualizar(deltaTime);

        Monstro *monstroCarregado = jogador->getMonstroCarregado();

        if (monstroCarregado == nullptr)
        {
            // Tentar capturar um monstro, se não estiver carregando um
            for (size_t i = 1; i < entidades.size(); ++i) 
            {
                Monstro *monstro = dynamic_cast<Monstro*>(entidades[i]);
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
        Monstro *monstro = dynamic_cast<Monstro*>(entidades[i]);
        if (monstro && !monstro->estaCapturado())
        {
            // Método com polimorfismo (futuramente)
            monstro->atualizar(deltaTime); 
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
    // Desenhar Mapa (futuro)

    // Desenhar Máquina
    if (maquina)
    {
        // maquina->desenhar(window); // Se a máquina tiver sprite
    }

    // Desenhar Todas as Entidades
    for (Personagem *entidade : entidades)
    {
        entidade->desenhar(window);
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
