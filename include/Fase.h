#ifndef FASE_H
#define FASE_H

#include <vector>
#include <SFML/Graphics.hpp>

class Personagem;
class MaquinaDeReciclagem;
class Timer;

const int mapa_linhas = 15;
const int mapa_colunas = 27;

class Fase
{
private:
    Timer *timer;
    MaquinaDeReciclagem *maquina;
    int tempoInicial;
    char mapa[mapa_linhas][mapa_colunas];
    int quantidadeMonstros;
    int level;
    void carregarMapa(int level); // Carregar_mapa() ira preencher o conteudo do mapa da classe Fase

public:
    Fase(int inicioTempo, const char mapaData[mapa_linhas][mapa_colunas + 1], int numMonstros, int nivelDoMapa);
    ~Fase();

    int getTempoInicial() const;          // + getTempo() int
    const char *getMapa(int linha) const; // + getMapa(): char[]
    int getQuantidadeMonstros() const;    // + getQuantidade Monstros() int

    void detectarVitoria();        // + detectar Vitoria(): void
    bool verificarDerrota() const; // Checa o Timer (Responsabilidade da Fase)
};

#endif