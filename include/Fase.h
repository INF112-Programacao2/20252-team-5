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
    std::vector<std::pair<int, int>> plataformas;
public:
    Fase(int inicioTempo, int numMonstros);
    ~Fase();

    int getTempoInicial() const;          
    int getQuantidadeMonstros() const;    
    const char *getMapa(int linha) const; 

    std::vector<Personagem *> &getEntidades();  
    std::vector<std::pair<int, int>> getPlataformas();
    Timer *getTimer() const;                    
    void removerEntidade(Personagem *entidade); 

    void carregarMapa(int nivel);
    void inicializarEntidades();
    void atualizar(float deltaTime);
    void desenhar(sf::RenderWindow &window); 

    void detectarVitoria();       
    bool verificarDerrota() const; 
};

#endif
