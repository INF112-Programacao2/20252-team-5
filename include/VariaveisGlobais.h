#ifndef VARIAVEIS_GLOBAIS_H
#define VARIAVEIS_GLOBAIS_H

const unsigned int LARGURA_JANELA = 1280;
const unsigned int ALTURA_JANELA = 720;

const int TAM_PIXEL = 32;
const float GRAVITY = 2400.f;

const int MAPA_LINHAS = 22;
const int MAPA_COLUNAS = 40;

extern unsigned int NIVEL_ATUAL;

#define TUNEL1_LINHA 1
#define TUNEL1_COLUNA 0

#define TUNEL2_LINHA 21
#define TUNEL2_COLUNA 39

#define TUNEL1_X (TUNEL1_COLUNA * TAM_PIXEL)
#define TUNEL1_Y (TUNEL1_LINHA * TAM_PIXEL)

#define TUNEL2_X (TUNEL2_COLUNA * TAM_PIXEL)
#define TUNEL2_Y (TUNEL2_LINHA * TAM_PIXEL)

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
