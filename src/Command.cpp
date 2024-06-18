#include "Command.h"

void MoveLeftCommand::execute(Player& player, float playerSpeed) {
    player.setVelocity(-playerSpeed, 0);
}

void MoveRightCommand::execute(Player& player, float playerSpeed) {
    player.setVelocity(playerSpeed, 0);
}

void JumpCommand::execute(Player& player, float playerSpeed) {
    player.getBody()->SetGravityScale(0.5);
    player.setVelocity(0, playerSpeed * 4.0f);
}