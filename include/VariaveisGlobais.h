#ifndef VARIAVEIS_GLOBAIS_H
#define VARIAVEIS_GLOBAIS_H

const unsigned int LARGURA_JANELA = 1280;
const unsigned int ALTURA_JANELA = 720;

const int TAM_PIXEL = 32;
const float GRAVITY = 2400.f;

const int MAPA_LINHAS = 22;
const int MAPA_COLUNAS = 40;

enum Status
{
    MENU,
    JOGANDO,
    PAUSA,
    VITORIA,
    DERROTA,
    CREDITOS
};

enum Condicao
{
    NORMAL,
    INVISIVEL,
    RAPIDO
};

// Auxilia na verificação de colisão
enum class Direcao
{
    NENHUMA,
    CIMA,
    BAIXO,
    ESQUERDA,
    DIREITA,
    CAINDO
};

#endif