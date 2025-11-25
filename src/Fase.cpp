#include "../include/Fase.h"
#include "../include/Timer.h"
#include "../include/Personagem.h"
#include "../include/MaquinaDeReciclagem.h"
#include "../include/Jogador.h" // <--- NECESSÁRIO para criar Jogador
// #include "../include/Monstro.h" // <--- Descomente quando criar a classe Monstro

#include <cstring>
#include <iostream>

// Coordenadas fixas para a máquina (ajuste conforme seu mapa)
const float MAQUINA_X = 100.0f;
const float MAQUINA_Y = 100.0f;

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

// Lógica
void Fase::inicializarEntidades()
{
    // CORREÇÃO: Adicionar diretamente ao vetor da classe 'entidades'
    // Usamos 'new' porque seu vetor é vector<Personagem*>

    // 1. Criar Jogador (Posição X, Y, Velocidade, Caminho da Textura)
    // Certifique-se de que a imagem existe em assets/
    entidades.push_back(new Jogador(50.0f, 50.0f, 2.0f, "assets/textures/player.png"));

    // 2. Criar Monstros (Exemplo futuro)
    // for(int i = 0; i < quantidadeMonstros; i++) {
    //     entidades.push_back(new Monstro(...));
    // }
}

void Fase::atualizar(float deltaTime)
{
    // 1. Atualizar Timer
    // timer->atualizar(deltaTime);

    // 2. Atualizar Entidades (Polimorfismo)
    // Percorre todas as entidades (Jogador, Monstros) e chama atualizar()
    for (Personagem *entidade : entidades)
    {
        // Precisamos fazer o cast do mapa se o atualizar pedir (ou mudar a assinatura)
        // Por enquanto, assumindo que atualizar recebe o mapa:
        // entidade->atualizar(mapa);
    }

    // 3. Verificar Derrota
    if (verificarDerrota())
    {
        // Logica de derrota
        std::cout << "Tempo Esgotado!" << std::endl;
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