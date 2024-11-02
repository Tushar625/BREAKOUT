#pragma once

class brick_class
{
	bool invisible;

	sf::Sound sound;

public:

	double x, y;

	int color, tier, score;

	brick_class(double xin, double yin, int color_in, int tier_in) : x(xin), y(yin), color(color_in), tier(tier_in), invisible(false)
	{
		// calculate the score while makin gthe brick

		score = (color + 1) * 10 + tier * 5;
	}

	int get_width()
	{
		return 32;
	}

	int get_height()
	{
		return 16;
	}

	// hit returns score and plays the sound

	int hit()
	{
		if(color == 0)
		{
			sound.setBuffer(sound_buffer[BRICK_HIT_2]);

			sound.play();

			invisible = true;

			return score;
		}
		
		sound.setBuffer(sound_buffer[BRICK_HIT_2]);

		sound.play();

		--color;

		return 0;
	}

	bool is_visible()
	{
		return !invisible;
	}

	void render()
	{
		if (invisible)
			return;

		auto& curr_brick = sprite[BRICK][tier + color * 4];

		curr_brick.setPosition(sf::Vector2f(x, y));

		bb::WINDOW.draw(curr_brick);
	}
};