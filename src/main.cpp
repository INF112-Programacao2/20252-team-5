#include "../include/Jogo.h"

#include <iostream>

int main()
{
    std::cout << "DEBUG: Entrou na main." << std::endl;

    // Tente envolver a inicialização em um bloco try-catch, se possível, para diagnosticar exceções.
    try
    {
        Jogo jogo;
        std::cout << "DEBUG: Objeto Jogo criado com sucesso." << std::endl;
        jogo.executar();
    }
    catch (const std::exception &e)
    {
        std::cerr << "ERRO FATAL: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "ERRO FATAL DESCONHECIDO." << std::endl;
    }

    std::cout << "DEBUG: Main terminada." << std::endl;
    return 0;
}