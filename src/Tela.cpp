#include "../include/VariaveisGlobais.h"
#include "../include/Tela.h"
#include "../include/Fase.h"

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

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
    //sf::RenderWindow window(sf::VideoMode(800, 600), "Tela de Derrota - Teste");
    window.setFramerateLimit(60);

    // Carregar fonte PixelBook
    sf::Font font;
    if (!font.loadFromFile("../assets/fonts/PixelBook-Regular.ttf"))
    {
       std::cout << "Erro ao carregar PixelBook-Regular.ttf" << std::endl;
       return;
    }

    // Texto principal (fade-in)
    sf::Text titulo("VOCÊ GANHOU!!", font, 80);
    titulo.setFillColor(sf::Color(170, 200, 170));  // começa invisível

    sf::FloatRect tb = titulo.getLocalBounds();
    titulo.setOrigin(tb.left + tb.width / 2.f, tb.top + tb.height / 2.f);
    titulo.setPosition(800 / 2.f, 200);

    // Texto instruções (piscando)
    sf::Text instrucao("Pressione ENTER para ir para o MENU", font, 32);
    instrucao.setFillColor(sf::Color(215, 215, 215, 215));

    sf::FloatRect ib = instrucao.getLocalBounds();
    instrucao.setOrigin(ib.left + ib.width / 2.f, ib.top + ib.height / 2.f);
    instrucao.setPosition(800 / 2.f, 400);

    float fadeAlpha = 0;
    bool blinkOn = true;
    float blinkTimer = 0;

    float backgroundPulse = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                std::cout << "Simulando reinicio..." << std::endl;
        }

        // ---- Animação 1: Fade-in no texto principal ----
        if (fadeAlpha < 255)
            fadeAlpha += 0.25; // velocidade do fade-in
        titulo.setFillColor(sf::Color(255, 0, 0, fadeAlpha));

        // ---- Animação 2: Texto piscando ----
        blinkTimer += 0.05f;
        if (blinkTimer >= 1.0f)
        {
            blinkTimer = 0;
            blinkOn = !blinkOn;
        }
        instrucao.setFillColor(sf::Color(255, 255, 255, blinkOn ? 255 : 40));

        // ---- Animação 3: Fundo "respirando" ----
        backgroundPulse += 0.3f;
        int pulse = 20 + std::sin(backgroundPulse) * 20;
        window.clear(sf::Color(pulse, 200, 110));

        // Desenhar tudo
        window.draw(titulo);
        window.draw(instrucao);
        window.display();
    }

}

void Tela::exibirDerrota(sf::RenderWindow &window)
{
    //sf::RenderWindow window(sf::VideoMode(800, 600), "Tela de Derrota - Teste");
    window.setFramerateLimit(60);

    // Carregar fonte PixelBook
    sf::Font font;
    if (!font.loadFromFile("PixelBook-Regular.ttf"))
    {
      std::cout << "Erro ao carregar PixelBook-Regular.ttf" << std::endl;
       return;
    }

    // Texto principal (fade-in)
    sf::Text titulo("VOCÊ PERDEU", font, 80);
    titulo.setFillColor(sf::Color(255, 0, 0, 0));  // começa invisível

    sf::FloatRect tb = titulo.getLocalBounds();
    titulo.setOrigin(tb.left + tb.width / 2.f, tb.top + tb.height / 2.f);
    titulo.setPosition(800 / 2.f, 200);

    // Texto instruções (piscando)
    sf::Text instrucao("Pressione ENTER para tentar novamente", font, 32);
    instrucao.setFillColor(sf::Color(255, 255, 255, 255));

    sf::FloatRect ib = instrucao.getLocalBounds();
    instrucao.setOrigin(ib.left + ib.width / 2.f, ib.top + ib.height / 2.f);
    instrucao.setPosition(800 / 2.f, 400);

    float fadeAlpha = 0;
    bool blinkOn = true;
    float blinkTimer = 0;

    float backgroundPulse = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                std::cout << "Simulando reinicio..." << std::endl;
        }

        // ---- Animação 1: Fade-in no texto principal ----
        if (fadeAlpha < 255)
            fadeAlpha += 2; // velocidade do fade-in
        titulo.setFillColor(sf::Color(255, 0, 0, fadeAlpha));

        // ---- Animação 2: Texto piscando ----
        blinkTimer += 0.05f;
        if (blinkTimer >= 1.0f)
        {
            blinkTimer = 0;
            blinkOn = !blinkOn;
        }
        instrucao.setFillColor(sf::Color(255, 255, 255, blinkOn ? 255 : 40));

        // ---- Animação 3: Fundo "respirando" ----
        backgroundPulse += 0.3f;
        int pulse = 20 + std::sin(backgroundPulse) * 20;
        window.clear(sf::Color(pulse, 0, 0));

        // Desenhar tudo
        window.draw(titulo);
        window.draw(instrucao);
        window.display();
    }
    
}
