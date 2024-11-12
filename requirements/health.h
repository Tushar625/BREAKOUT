#pragma once


/*
	print the hearts at certain position
*/

inline void render_health(int health)
{
	auto& heart = sprite[HEART][0];

	auto& empty_heart = sprite[HEART][1];

	auto heart_width = heart.getLocalBounds().width;

	// center of heart is at VIRTUAL_WIDTH / 2.0 and it's placed 2 pixels below the top

	int x = VIRTUAL_WIDTH / 2.0 - MAX_HEALTH * heart_width / 2;

	// printing empty hearts

	for (int i = MAX_HEALTH - health; i > 0; i--)
	{
		empty_heart.setPosition(sf::Vector2f(x, 2));

		bb::WINDOW.draw(empty_heart);

		x += heart_width;
	}

	// now printing the hearts

	for (int i = health; i > 0; i--)
	{
		heart.setPosition(sf::Vector2f(x, 2));

		bb::WINDOW.draw(heart);

		x += heart_width;
	}
}