#pragma once


void render_health(int health)
{
	auto heart_width = sprite[HEART][0].getLocalBounds().width;

	int x = VIRTUAL_WIDTH / 2.0 - MAX_HEALTH * heart_width / 2;

	// printing empty hearts

	for (int i = MAX_HEALTH - health; i > 0; i--)
	{
		sprite[HEART][1].setPosition(sf::Vector2f(x, 2));

		bb::WINDOW.draw(sprite[HEART][1]);

		x += heart_width;
	}

	for (int i = health; i > 0; i--)
	{
		sprite[HEART][0].setPosition(sf::Vector2f(x, 2));

		bb::WINDOW.draw(sprite[HEART][0]);

		x += heart_width;
	}
}