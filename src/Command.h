#pragma once
#include "Player.h"

class Command {
public:
    virtual void execute(Player& player, float playerSpeed) = 0;
};

class MoveLeftCommand : public Command {
public:
    void execute(Player& player, float playerSpeed) override;
};

class MoveRightCommand : public Command {
public:
    void execute(Player& player, float playerSpeed) override;
};

class JumpCommand : public Command {
public:
    void execute(Player& player, float playerSpeed) override;
};
