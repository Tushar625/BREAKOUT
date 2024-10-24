#pragma once

std::vector<sf::Sprite> get_paddle_sprites()
{
	std::vector<sf::Sprite> paddles(16, sf::Sprite{ texture[MAIN]});

	int x = 0, y = 64;

	for (int i = 0; i < 4; i++)
	{
		paddles[i * 4 + 0].setTextureRect(sf::IntRect(x, y, 32, 16));

		paddles[i * 4 + 1].setTextureRect(sf::IntRect(x + 32, y, 64, 16));

		paddles[i * 4 + 2].setTextureRect(sf::IntRect(x + 96, y, 96, 16));

		paddles[i * 4 + 3].setTextureRect(sf::IntRect(x, y + 16, 128, 16));

		x = 0;

		y += 32;
	}

	return paddles;
}