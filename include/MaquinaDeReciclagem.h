#ifndef MAQUINA_DE_RECICLAGEM_H
#define MAQUINA_DE_RECICLAGEM_H
#include <SFML/Graphics.hpp>
#include <string>

class Fase;
class Monstro;
class Timer;

class MaquinaDeReciclagem
{
private:
    int x;
    int y;

    Fase *fase;
    Timer *timer;

    sf::Sprite _sprite;
    sf::Texture _texture;

public:
    MaquinaDeReciclagem(int posX, int posY, Fase *_fase, Timer *_timer, std::string imagem);

    int getPosicaoX() const;
    int getPosicaoY() const;
    sf::Sprite getSprite() const;

    void desenhar(sf::RenderWindow &window);

    void receberInimigo(Monstro *inimigo);

    int calcularBonusTempo(Monstro *inimigo) const;
};

#endif
