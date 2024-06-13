#include "Player.h"


void Player::Render(sf::RenderTarget& window) const {
	sf::RectangleShape block;
	block.setPosition(sf::Vector2f(playerBody->GetPosition().x, playerBody->GetPosition().y));
	block.setSize(sf::Vector2f(50, 50));
	block.setFillColor(sf::Color::Red);
	window.draw(block);
}

b2Vec2 Player::getPosition() const {
	return playerBody->GetPosition();
}