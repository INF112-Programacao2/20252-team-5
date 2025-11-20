#ifndef VARIAVEIS_GLOBAIS_H
#define VARIAVEIS_GLOBAIS_H

const unsigned int LARGURA_JANELA = 1280;
const unsigned int ALTURA_JANELA = 720;

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

#endif