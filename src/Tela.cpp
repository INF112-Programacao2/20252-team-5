#include "../include/VariaveisGlobais.h"
#include "../include/Tela.h"
#include "../include/Fase.h"

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

int Tela::opcaoSelecionada = 0;
sf::Font Tela::font;
sf::Texture Tela::backgroundTexture;
bool Tela::backgroundCarregado = false;
sf::Texture Tela::gameBackgroundTexture;
bool Tela::gameBackgroundCarregado = false;

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
    if (!font.loadFromFile("assets/fonts/PixelBook-Regular.ttf"))
    {
        if (!font.loadFromFile("assets/fonts/PixelBook-Regular.ttf"))
        {
            std::cerr << "Erro ao carregar a fonte PixelBook-Regular.ttf (../assets/ ou assets/)" << std::endl;
        }
    }

    carregou = true;
}

void Tela::carregarBackground()
{
    if (backgroundCarregado)
        return;

    if (!backgroundTexture.loadFromFile("assets/textures/background-menu.png"))
    {
        std::cerr << "Erro ao carregar o background do menu." << std::endl;
    }
    backgroundCarregado = true;
}

void Tela::carregarGameBackground()
{
    if (gameBackgroundCarregado)
        return;

    if (!gameBackgroundTexture.loadFromFile("assets/textures/background-jogando.png"))
    {
        std::cerr << "Erro ao carregar o background da fase (game_bg.png)." << std::endl;
    }
    gameBackgroundCarregado = true;
}

void Tela::desenharScrollingBackground(class Fase *fase, sf::RenderWindow &window)
{
    carregarGameBackground();

    if (!fase || !fase->getEntidades().size())
        return;

    float playerX = fase->getEntidades()[0]->getPosicaoX();
    const float PARALLAX_FACTOR = 0.02f;
    float cameraOffset = playerX - (LARGURA_JANELA / 2.0f);
    float parallaxOffset = cameraOffset * PARALLAX_FACTOR;
    sf::Sprite backgroundSprite(gameBackgroundTexture);
    sf::Vector2u textureSize = gameBackgroundTexture.getSize();
    float scaleX = (float)LARGURA_JANELA / textureSize.x;
    float scaleY = (float)ALTURA_JANELA / textureSize.y;

    backgroundSprite.setScale(scaleX, scaleY);

    backgroundSprite.setPosition(-parallaxOffset, 0.0f);

    window.draw(backgroundSprite);
}

void Tela::desenharHUD(class Fase *fase, sf::RenderWindow &window)
{
    carregarFonte();

    if (!fase || !fase->getTimer())
        return;

    int tempoTotal = fase->getTimer()->getTempoRestante();

    int minutos = tempoTotal / 60;
    int segundos = tempoTotal % 60;

    std::string segundos_str = (segundos < 10) ? ("0" + std::to_string(segundos)) : std::to_string(segundos);
    std::string minutos_str = (minutos < 10) ? ("0" + std::to_string(minutos)) : std::to_string(minutos);
    std::string tempoStr = "TEMPO: " + minutos_str + ":" + segundos_str;

    sf::Text timerText(tempoStr, font, 36);
    timerText.setFillColor(sf::Color::White);

    float padding = 20.0f;
    float posX = LARGURA_JANELA - timerText.getLocalBounds().width - padding;
    float posY = padding;

    timerText.setPosition(posX, posY);

    window.draw(timerText);
}

void Tela::exibirMenu(sf::RenderWindow &window)
{
    carregarFonte();
    carregarBackground();

    window.clear(sf::Color::Black);

    sf::Sprite background(backgroundTexture);
    float escalaX = (float)LARGURA_JANELA / backgroundTexture.getSize().x;
    float escalaY = (float)ALTURA_JANELA / backgroundTexture.getSize().y;
    background.setScale(escalaX, escalaY);

    window.draw(background);

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

    sf::RectangleShape overlay(sf::Vector2f(LARGURA_JANELA, ALTURA_JANELA));
    overlay.setFillColor(sf::Color(0, 0, 0, 180));
    window.draw(overlay);

    sf::Text titulo("PAUSADO", font, 60);
    titulo.setFillColor(sf::Color::White);

    titulo.setPosition(
        (LARGURA_JANELA - titulo.getLocalBounds().width) / 2,
        (ALTURA_JANELA / 3.0f)
    );
    window.draw(titulo);

    sf::Text instrucao("Pressione ESC para continuar", font, 24);
    instrucao.setFillColor(sf::Color(200, 200, 200));

    instrucao.setPosition(
        (LARGURA_JANELA - instrucao.getLocalBounds().width) / 2,
        (ALTURA_JANELA / 3.0f) + 100
    );
    window.draw(instrucao);
}

void Tela::exibirFase(class Fase *fase, sf::RenderWindow &window)
{
    carregarFonte();

    window.clear(sf::Color::Black);
    desenharScrollingBackground(fase, window);

    if (fase)
        fase->desenhar(window);
    else
        std::cerr << "Erro ao exibir fase: ponteiro null!" << std::endl;

    Tela::desenharHUD(fase, window);
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
    window.setFramerateLimit(60);

    carregarFonte();

    sf::Text titulo("VOCÊ GANHOU!!", font, 80);
    titulo.setFillColor(sf::Color(170, 200, 170));

    sf::FloatRect tb = titulo.getLocalBounds();
    titulo.setOrigin(tb.left + tb.width / 2.f, tb.top + tb.height / 2.f); 
    titulo.setPosition(LARGURA_JANELA / 2.f, ALTURA_JANELA * 0.35f);

    sf::Text instrucao("Pressione ENTER para ir para o MENU", font, 32);
    instrucao.setFillColor(sf::Color(215, 215, 215, 215));

    sf::FloatRect ib = instrucao.getLocalBounds();
    instrucao.setOrigin(ib.left + ib.width / 2.f, ib.top + ib.height / 2.f);
    instrucao.setPosition(LARGURA_JANELA / 2.f, ALTURA_JANELA * 0.55f);

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

        if (fadeAlpha < 255)
            fadeAlpha += 0.25;
        titulo.setFillColor(sf::Color(255, 0, 0, fadeAlpha));

        blinkTimer += 0.05f;
        if (blinkTimer >= 1.0f)
        {
            blinkTimer = 0;
            blinkOn = !blinkOn;
        }
        instrucao.setFillColor(sf::Color(255, 255, 255, blinkOn ? 255 : 40));

        backgroundPulse += 0.3f;
        int pulse = 20 + std::sin(backgroundPulse) * 20;
        window.clear(sf::Color(pulse, 200, 110));

        window.draw(titulo);
        window.draw(instrucao);
        window.display();
    }
}

void Tela::exibirDerrota(sf::RenderWindow &window)
{
    window.setFramerateLimit(60);

    carregarFonte();

    sf::Text titulo("VOCÊ PERDEU", font, 80);
    titulo.setFillColor(sf::Color(255, 0, 0, 0));

    sf::FloatRect tb = titulo.getLocalBounds();
    titulo.setOrigin(tb.left + tb.width / 2.f, tb.top + tb.height / 2.f);
    titulo.setPosition(LARGURA_JANELA / 2.f, ALTURA_JANELA * 0.35f);

    sf::Text instrucao("Pressione ENTER para tentar novamente", font, 32);
    instrucao.setFillColor(sf::Color(255, 255, 255, 255));

    sf::FloatRect ib = instrucao.getLocalBounds();
    instrucao.setOrigin(ib.left + ib.width / 2.f, ib.top + ib.height / 2.f);
    instrucao.setPosition(LARGURA_JANELA / 2.f, ALTURA_JANELA * 0.55f);

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

        if (fadeAlpha < 255)
            fadeAlpha += 2;
        titulo.setFillColor(sf::Color(255, 0, 0, fadeAlpha));

        blinkTimer += 0.05f;
        if (blinkTimer >= 1.0f)
        {
            blinkTimer = 0;
            blinkOn = !blinkOn;
        }
        instrucao.setFillColor(sf::Color(255, 255, 255, blinkOn ? 255 : 40));

        backgroundPulse += 0.3f;
        int pulse = 20 + std::sin(backgroundPulse) * 20;
        window.clear(sf::Color(pulse, 0, 0));

        window.draw(titulo);
        window.draw(instrucao);
        window.display();
    }
}