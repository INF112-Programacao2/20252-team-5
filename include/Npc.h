#ifndef NPC_H
#define NPC_H

#include "PowerUp.h"

#include <string>

class Npc
{
private:
    std::string dialogo;
    PowerUp *powerUp;

public:
    Npc(const std::string &dialogo, PowerUp &powerUp);
    ~Npc();

    std::string getDialogo() const;
    PowerUp *getPowerUp() const;

    void interagir(Jogador &jogador);
};

#endif