#ifndef FASE_H
#define FASE_H

#include "Personagem.h"
#include "MaquinaDeReciclagem.h"
#include "Timer.h"
#include "Monstro.h"

#include <vector>
#include <SFML/Graphics.hpp>

const int MAPA_LINHAS = 15;
const int MAPA_COLUNAS = 27;

class Fase
{
private:
    Timer *timer;
    MaquinaDeReciclagem *maquina;
    int tempoInicial;
    char mapa[MAPA_LINHAS][MAPA_COLUNAS + 1];
    int quantidadeMonstros;
    //int level;
    void carregarMapa(int level); // Carregar_mapa() ira preencher o conteudo do mapa da classe Fase
    std::vector<Personagem*> entidades;

public:
    Fase(int inicioTempo, int numMonstros);
    ~Fase();

    int getTempoInicial() const;          // + getTempo() int
    int getQuantidadeMonstros() const;    // + getQuantidade Monstros() int
    const char *getMapa(int linha) const; // + getMapa(): char[]

    std::vector<Personagem*>& getEntidades();// Expõe o vetor Personagem para Jogo fazer a checagem de vitótia
    Timer* getTimer() const; // Expõe Timer para Jogo alterar o tempo
    void removerEntidade(Personagem *entidade); // Para a Máquina avisar a Fase para deletar um Monstro do vetor entidades

    void inicializarEntidades();
    void atualizar(float deltaTime);
    void desenhar(sf::RenderWindow &window);

    void detectarVitoria();        // + detectar Vitoria(): void
    bool verificarDerrota() const; // Checa o Timer (Responsabilidade da Fase)
};

#endif
