#include "../include/Npc.h"
#include "../include/Jogador.h"
#include <iostream>

Npc::Npc(const std::string &dialogo, PowerUp &powerUp)
    : dialogo(dialogo),
      powerUp(&powerUp)
{
}

Npc::~Npc()
{
    // Se o NPC for o "dono" do PowerUp, deveria deletar aqui.
    // Se quisermos que o NPC gerencie, deveríamos clonar o PowerUp ou usar unique_ptr.
}

std::string Npc::getDialogo() const
{
    return dialogo;
}

PowerUp *Npc::getPowerUp() const
{
    return powerUp;
}

void Npc::interagir(Jogador &jogador)
{
    std::cout << "[NPC]: " << dialogo << std::endl;

    if (powerUp != nullptr)
    {
        std::cout << "[NPC] Entregou um PowerUp!" << std::endl;
        powerUp->aplicarEfeito(jogador);
    }
}