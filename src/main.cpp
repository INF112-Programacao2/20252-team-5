#include "../include/Jogo.h"
#include "../include/VariaveisGlobais.h"

#include <iostream>

int main()
{
    // Renderiza a janela ao instanciar a classe jogo
    Jogo jogo;
    NIVEL_ATUAL = 1;

    // Inicia o loop principal do jogo
    jogo.executar();
    return 0;
}