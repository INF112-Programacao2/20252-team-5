#ifndef FASE_H
#define FASE_H

#include "Personagem.h"
#include "MaquinaDeReciclagem.h"
#include "Timer.h"
#include "Monstro.h"
#include "VariaveisGlobais.h"

#include <vector>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>

class Fase
{
private:
    Timer *timer;
    MaquinaDeReciclagem *maquina;
    int tempoInicial;
    char mapa[MAPA_LINHAS][MAPA_COLUNAS + 1];
    int quantidadeMonstros;
    int nivel;
    std::vector<Personagem *> entidades;
    sf::Texture texturaTile;

public:
    Fase(int inicioTempo, int numMonstros);
    ~Fase();

    int getTempoInicial() const;          // + getTempo() int
    int getQuantidadeMonstros() const;    // + getQuantidade Monstros() int
    const char *getMapa(int linha) const; // + getMapa(): char[]

    std::vector<Personagem *> &getEntidades();  // Expõe o vetor Personagem para Jogo fazer a checagem de vitótia
    Timer *getTimer() const;                    // Expõe Timer para Jogo alterar o tempo
    void removerEntidade(Personagem *entidade); // Para a Máquina avisar a Fase para deletar um Monstro do vetor entidades

    void carregarMapa(int nivel); // Carrega o mapa do arquivo de texto
    void inicializarEntidades();
    void atualizar(float deltaTime);
    void desenhar(sf::RenderWindow &window); // Desenha a fase completa

    void detectarVitoria();        // + detectar Vitoria(): void
    bool verificarDerrota() const; // Checa o Timer (Responsabilidade da Fase)
};

#endif
