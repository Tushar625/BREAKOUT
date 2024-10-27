#pragma once

#include"utility/collision.h"

class level_maker
{
	std::vector<brick_class> brick_matrix;

	sf::Sound sound;

	//int height, width;

	public:

	void set_level()
	{
		// no. of bricks row and column wise

		int height = 3;

		int width = 6;

		// the matrix

		brick_matrix = std::vector<brick_class>{ static_cast<size_t>(height * width) };

		// from center of the matrix we get the top left corners

		int xout, yout;

		to_top_left(xout, yout, VIRTUAL_WIDTH / 2, 50, height * (brick_matrix[0].get_height() + 8), width * (brick_matrix[0].get_width() + 8), CENTER);

		// setting positions for each bricks
		
		for (int r = 0; r < height; r++)
		{
			int tempx = xout;

			for (int c = 0; c < width; c++)
			{
				brick_matrix[c + r * width].x = tempx + 4;

				brick_matrix[c + r * width].y = yout + 4;

				tempx += 32 + 8;
			}

			yout += 16 + 8;
		}
	}

	void clear_level()
	{
		brick_matrix = {};
	}

	void update()
	{
		for (auto& brick : brick_matrix)
		{
			// xout and yout gets the point of collision on the brick

			double xout, yout;

			if (brick.is_visible() && ball.collids(xout, yout, brick.x, brick.y, brick.get_width(), brick.get_height()))
			{
				// a brick is visible and collids with the ball

				auto side = circle_aabb_collision_side(xout, yout, brick.x, brick.y, brick.get_width(), brick.get_height());

				/*
					as floating point numbers are not very precise we cannot check for equality
					instead we check for the difference
				*/

				if (side.left)
				{
					if (ball.dx > 0)
					{
						// coming from left

						ball.dx = -ball.dx;
					}
					else
					{
						// hitting top left or bottom left corner

						ball.dy /= 1.05;
					}

					ball.x = brick.x - ball.get_width();
				}

				if (side.right)
				{
					if (ball.dx < 0)
					{
						// coming from right

						ball.dx = -ball.dx;
					}
					else
					{
						// hitting top right or bottom right corner

						ball.dy /= 1.05;
					}

					ball.x = brick.x + brick.get_width();
				}

				if (side.top)
				{
					if (ball.dy > 0)
					{
						// coming from top

						ball.dy = -ball.dy;
					}
					else
					{
						// hitting top left or top right corner

						ball.dx /= 1.05;
					}

					ball.y = brick.y - ball.get_height();
				}
				
				if (side.bottom)
				{
					if (ball.dy < 0)
					{
						// coming from bottom

						ball.dy = -ball.dy;
					}
					else
					{
						// hitting bottom left or bottom right corner

						ball.dx /= 1.05;
					}

					ball.y = brick.y + brick.get_height();
				}

				sound.setBuffer(sound_buffer[BRICK_HIT_2]);

				sound.play();

				brick.hit();
			}
		}
	}

	void render()
	{
		for (auto& brick : brick_matrix)
		{
			brick.render();
		}
	}
};