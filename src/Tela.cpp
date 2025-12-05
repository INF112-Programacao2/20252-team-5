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

void Tela::carregarBackground()
{
    if (backgroundCarregado)
        return;

    if (!backgroundTexture.loadFromFile("../assets/textures/background-menu.png"))
    {
        std::cerr << "Erro ao carregar o background do menu." << std::endl;
    }
    backgroundCarregado = true;
}

void Tela::carregarGameBackground()
{
    if (gameBackgroundCarregado)
        return;

    if (!gameBackgroundTexture.loadFromFile("../assets/textures/background-jogando.png"))
    {
        std::cerr << "Erro ao carregar o background da fase (game_bg.png)." << std::endl;
    }
    gameBackgroundCarregado = true;
}

void Tela::desenharScrollingBackground(class Fase *fase, sf::RenderWindow &window)
{
    carregarGameBackground(); // Garante que a textura esteja carregada

    if (!fase || !fase->getEntidades().size())
        return; // Verifica se a fase está ok

    // 1. Obter a posição de referência (Assumindo que o Jogador é a primeira entidade)
    // ATENÇÃO: Você pode precisar ajustar o método para obter a posição X do Jogador
    float playerX = fase->getEntidades()[0]->getPosicaoX();
    const float PARALLAX_FACTOR = 0.02f;
    float cameraOffset = playerX - (LARGURA_JANELA / 2.0f);
    float parallaxOffset = cameraOffset * PARALLAX_FACTOR;
    sf::Sprite backgroundSprite(gameBackgroundTexture);
    sf::Vector2u textureSize = gameBackgroundTexture.getSize();
    float scaleX = (float)LARGURA_JANELA / textureSize.x;
    float scaleY = (float)ALTURA_JANELA / textureSize.y;

    // Aplica a escala para esticar a imagem
    backgroundSprite.setScale(scaleX, scaleY);

    // A posição Y é sempre 0, mas a posição X é corrigida pelo Parallax
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

    // 2. Configurar o sf::Text
    sf::Text timerText(tempoStr, font, 36); // Usando o membro estático Tela::font
    timerText.setFillColor(sf::Color::White);

    // 3. Posição: Canto superior direito
    // LARGURA_JANELA vem de VariaveisGlobais.h
    float padding = 20.0f;
    float posX = LARGURA_JANELA - timerText.getLocalBounds().width - padding;
    float posY = padding;

    timerText.setPosition(posX, posY);

    // 4. Desenhar
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
    window.setFramerateLimit(60);

    carregarFonte();

    // Texto principal (fade-in)
    sf::Text titulo("PAUSADO", font, 80);
    titulo.setFillColor(sf::Color(255, 255, 255, 0));

    sf::FloatRect tb = titulo.getLocalBounds();
    titulo.setOrigin(tb.left + tb.width / 2.f, tb.top + tb.height / 2.f);
    titulo.setPosition(800 / 2.f, 200);

    // Texto instruções (piscando)
    sf::Text instrucao("Pressione ENTER para continuar", font, 35);
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

            // ---- VOLTAR PARA O JOGO ----
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                return;
        }

        // Fade-in do texto principal
        if (fadeAlpha < 255)
            fadeAlpha += 0.35f;
        titulo.setFillColor(sf::Color(255, 255, 255, fadeAlpha));

        // Animação 2: Texto piscando
        blinkTimer += 0.05f;
        if (blinkTimer >= 1.f)
        {
            blinkTimer = 0;
            blinkOn = !blinkOn;
        }
        instrucao.setFillColor(sf::Color(255, 255, 255, blinkOn ? 255 : 40));

        // Animação 3: Fundo respirando
        backgroundPulse += 0.25f;
        int pulse = 40 + std::sin(backgroundPulse) * 20;
        window.clear(sf::Color(pulse, 80, 130)); // roxo-azulado

        // Render
        window.draw(titulo);
        window.draw(instrucao);
        window.display();
    }
}

void Tela::exibirFase(class Fase *fase, sf::RenderWindow &window)
{
    carregarFonte();

    window.clear(sf::Color::Black);
    desenharScrollingBackground(fase, window);

    // Desenhar a fase
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
    window.setFramerateLimit(60);

    carregarFonte();

    // Texto principal (fade-in)
    sf::Text titulo("VOCÊ GANHOU!!", font, 80);
    titulo.setFillColor(sf::Color(170, 200, 170));

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
    window.setFramerateLimit(60);

    carregarFonte();

    sf::Text titulo("VOCÊ PERDEU", font, 80);
    titulo.setFillColor(sf::Color(255, 0, 0, 0));

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