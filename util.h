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

std::vector<sf::Sprite> get_ball_sprites()
{
	std::vector<sf::Sprite> balls(7, sf::Sprite{ texture[MAIN] });

	int counter = 0;

	int x = 96, y = 48;

	while(counter < 4)
	{
		balls[counter++].setTextureRect(sf::IntRect(x, y, 8, 8));

		x += 8;
	}

	x = 64;
	
	y = 56;

	while (counter < 7)
	{
		balls[counter++].setTextureRect(sf::IntRect(x, y, 8, 8));

		x += 8;
	}

	return balls;
}

std::vector<sf::Sprite> get_brick_sprites()
{
	std::vector<sf::Sprite> bricks(21, sf::Sprite{ texture[MAIN] });

	int counter = 0;

	int x = 0, y = 0;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			bricks[counter++].setTextureRect(sf::IntRect(x, y, 32, 16));

			x += 32;
		}

		x = 0;

		y += 16;
	}

	x = 0;

	y += 16;

	while (counter < 21)
	{
		bricks[counter++].setTextureRect(sf::IntRect(x, y, 32, 16));

		x += 8;
	}

	return bricks;
}