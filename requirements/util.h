#pragma once

// functions needed to load assests

sf::Sprite get_background_sprite(const sf::Texture& texture)
{
	sf::Sprite bg_sprite;

	bg_sprite.setTexture(texture);

	auto bg_size = texture.getSize();

	bg_sprite.setScale(sf::Vector2f(VIRTUAL_WIDTH / (float)(bg_size.x - 1), VIRTUAL_HEIGHT / (float)(bg_size.y - 1)));

	return bg_sprite;
}

std::vector<sf::Sprite> get_paddle_sprites(const sf::Texture& texture)
{
	std::vector<sf::Sprite> paddles(16, sf::Sprite{ texture });

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

std::vector<sf::Sprite> get_ball_sprites(const sf::Texture& texture)
{
	std::vector<sf::Sprite> balls(7, sf::Sprite{ texture });

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

std::vector<sf::Sprite> get_brick_sprites(const sf::Texture& texture)
{
	std::vector<sf::Sprite> bricks(21, sf::Sprite{ texture });

	int counter = 0;

	int x = 0, y = 0;

	for (int i = 0; i < 3; i++)
	{
		x = 0;

		for (int j = 0; j < 6; j++)
		{
			bricks[counter++].setTextureRect(sf::IntRect(x, y, 32, 16));

			x += 32;
		}

		y += 16;
	}

	// collecting last three bricks

	x = 0;

	while (counter < 21)
	{
		bricks[counter++].setTextureRect(sf::IntRect(x, y, 32, 16));

		x += 32;
	}

	return bricks;
}

std::vector<sf::Sprite> get_heart_sprites(const sf::Texture& texture)
{
	std::vector<sf::Sprite> hearts(2, sf::Sprite{ texture });

	hearts[0].setTextureRect(sf::IntRect(128, 48, 10, 9));

	hearts[1].setTextureRect(sf::IntRect(138, 48, 10, 9));

	return hearts;
}