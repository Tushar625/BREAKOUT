#pragma once

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
			double xout, yout;

			if (brick.is_visible() && ball.collids(xout, yout, brick.x, brick.y, brick.get_width(), brick.get_height()))
			{
				// a brick is visible and collids with the ball

				if (ball.dx >= 0 && ball.x + 2 < brick.x)
				{
					// left collision

					ball.dx = -ball.dx;

					ball.x = brick.x - ball.get_width();
				}
				else if (ball.dx < 0 && ball.x + ball.get_width() - 2 < brick.x + brick.get_width())
				{
					// right collision

					ball.dx = -ball.dx;

					ball.x = brick.x + brick.get_width();
				}
				else if (ball.y < brick.y)
				{
					// top collision

					ball.dy = -ball.dy;

					ball.y = brick.y - ball.get_height();
				}
				else
				{
					// bottom collision

					ball.dy = -ball.dy;

					ball.y = brick.y + brick.get_height();
				}

				/*auto x1 = ball.x + ball.get_width() / 2.0;

				auto y1 = ball.y + ball.get_height() / 2.0;

				// increasing the size of the brick bounding box to get a more convincing result

				auto x = brick.x - ball.get_width() / 3.0;

				auto y = brick.y - ball.get_height() / 3.0;

				auto x_w = brick.x + brick.get_width() + ball.get_width() / 3.0;

				auto y_h = brick.y + brick.get_height() + ball.get_height() / 3.0;

				if ( x < x1 && x1 < x_w )
				{
					// top bottom collision

					if (ball.dy > 0)
					{
						// top

						ball.y = brick.y - ball.get_height();
					}
					else
					{
						// bottom

						ball.y = brick.y + brick.get_height();
					}

					ball.dy = -ball.dy;
				}
				else if ( y < y1 && y1 < y_h )
				{
					// left right collision

					if (ball.dx > 0)
					{
						// left

						ball.x = brick.x - ball.get_width();
					}
					else
					{
						// right

						ball.x = brick.x + brick.get_width();
					}

					ball.dx = -ball.dx;
				}
				else
				{
					if(ball.dx > 0)
					{
						if(x1 > x)
						{
							// top or bottom left corner

							ball.dx = -ball.dx;

							ball.x = brick.x - ball.get_width();
						}
						else
						{
							// top or bottom right corner
							
							ball.dy = -ball.dy;

							ball.x = brick.x + brick.get_width();
						}
					}
					else
					{
						if(x1 > x_w)
						{
							// top or bottom right corner

							ball.dx = -ball.dx;

							ball.x = brick.x + brick.get_width();
						}
						else
						{
							// top or bottom left corner
							
							ball.dy = -ball.dy;

							ball.x = brick.x - ball.get_width();
						}
					}
				}*/

				sound.setBuffer(sound_buffer[BRICK_HIT_1]);

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