#ifndef VARIAVEIS_GLOBAIS_H
#define VARIAVEIS_GLOBAIS_H

const unsigned int LARGURA_JANELA = 1280;
const unsigned int ALTURA_JANELA = 720;
const int TAM_PIXEL = 32;
const float GRAVITY = 2400.f;

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

enum class Direcao {
    NENHUMA,
    CIMA,
    BAIXO,
    ESQUERDA,
    DIREITA,
    CAINDO
};
// auxilia na verificação de colisão

#endif
