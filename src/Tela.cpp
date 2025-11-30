#include "../include/VariaveisGlobais.h"
#include "../include/Tela.h"
#include "../include/Fase.h"

#include <iostream>
#include <string>
#include <sstream>

int Tela::opcaoSelecionada = 0;
sf::Font Tela::font;

Tela::Tela() {}

int Tela::getOpcaoSelecionada()
{
    return opcaoSelecionada;
}

void Tela::proximaOpcao()
{
    opcaoSelecionada++;
    if (opcaoSelecionada > 2)
        opcaoSelecionada = 0;
}

void Tela::anteriorOpcao()
{
    opcaoSelecionada--;
    if (opcaoSelecionada < 0)
        opcaoSelecionada = 2;
}

void Tela::carregarFonte()
{
    static bool carregou = false;
    if (carregou)
        return;

    // Tentar caminho relativo quando executável roda em build (padrão)
    if (!font.loadFromFile("../assets/fonts/PixelBook-Regular.ttf"))
    {
        // Tentar caminho alternativo (quando executável é chamado da raiz do projeto)
        if (!font.loadFromFile("assets/fonts/PixelBook-Regular.ttf"))
        {
            std::cerr << "Erro ao carregar a fonte PixelBook-Regular.ttf (../assets/ ou assets/)" << std::endl;
        }
    }

    carregou = true;
}

void Tela::exibirMenu(sf::RenderWindow &window)
{
    carregarFonte();

    // Desenho do menu
    window.clear(sf::Color::Black);

    sf::Text titulo("Recicla Mundo: ODS Game", font, 50);
    titulo.setPosition((LARGURA_JANELA - titulo.getLocalBounds().width) / 2, 100);

    sf::Text opcoes[3];
    std::string textos[3] = {"Jogar", "Créditos", "Sair"};

    for (int i = 0; i < 3; i++)
    {
        opcoes[i].setFont(font);
        opcoes[i].setCharacterSize(36);
        opcoes[i].setString(sf::String::fromUtf8(textos[i].begin(), textos[i].end()));
        opcoes[i].setPosition(LARGURA_JANELA / 2 - opcoes[i].getLocalBounds().width / 2, 250 + i * 60);

        if (i == opcaoSelecionada)
            opcoes[i].setFillColor(sf::Color::Yellow);
        else
            opcoes[i].setFillColor(sf::Color::White);

        window.draw(opcoes[i]);
    }

    window.draw(titulo);
}

void Tela::exibirPause(sf::RenderWindow &window)
{
    carregarFonte();
    window.clear(sf::Color::Yellow);
    // Código para desenhar a tela de pausa
}

void Tela::exibirFase(class Fase *fase, sf::RenderWindow &window)
{
    carregarFonte();
    sf::Color color(72, 72, 72);
    window.clear(color);

    // Desenhar a fase
    if (fase)
        fase->desenhar(window);
    else
        std::cerr << "Erro ao exibir fase: ponteiro null!" << std::endl;
}

void Tela::exibirCreditos(sf::RenderWindow &window)
{
    carregarFonte();
    window.clear(sf::Color::Green);

    std::string creditosTexto =
        "Desenvolvido por:\n\n"
        "Arthur Fabri Resende\n"
        "Carlos Henrique de Oliveira Godinho\n"
        "Gabriel Araújo Silva\n"
        "Raiany Marta Souza Severino\n"
        "Valdinei da Silva Stampini\n\n\n"
        "Pressione ESC para voltar";

    // Desenhar linha a linha, centralizando cada linha individualmente
    unsigned int charSize = 36;
    float y = 100.f;
    float lineSpacing = font.getLineSpacing(charSize);

    std::istringstream iss(creditosTexto);
    std::string line;
    while (std::getline(iss, line))
    {
        if (line.empty())
        {
            y += lineSpacing;
            continue;
        }

        sf::Text t(sf::String::fromUtf8(line.begin(), line.end()), font, charSize);
        sf::FloatRect bounds = t.getLocalBounds();

        t.setOrigin(bounds.left + bounds.width / 2.f, bounds.top);
        t.setPosition(static_cast<float>(LARGURA_JANELA) / 2.f, y);
        window.draw(t);

        y += lineSpacing;
    }
}

void Tela::exibirVitoria(sf::RenderWindow &window)
{
    carregarFonte();
    window.clear(sf::Color::Magenta);
    // Código para desenhar a tela de vitória
}

void Tela::exibirDerrota(sf::RenderWindow &window)
{
    carregarFonte();
    window.clear(sf::Color::Red);
    // Código para desenhar a tela de derrota
}