#ifndef VARIAVEIS_GLOBAIS_H
#define VARIAVEIS_GLOBAIS_H

const unsigned int LARGURA_JANELA = 1280;
const unsigned int ALTURA_JANELA = 720;
const float TAM_PIXEL = 32.f;

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

enum Direcao
{
    Cima, 
    Caindo,
    Esquerda,
    Direita
};
// auxilia na verificação de colisão

#endif