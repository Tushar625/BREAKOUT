#pragma once

class level_maker1
{
	std::vector<brick_class> bricks;

	sf::Sound sound;

	//int height, width;

	public:

	void set_level(int level = 0)
	{
		// no. of bricks row and column wise

		int height = 4 + (rand() % 5);	//  4 -> 8

		int width = 5 + 2 * (rand() % 4);	// odds 5 -> 11

		// max color and tier
		
		int max_color = std::min(level, 4);		// increase 1 max_color per level

		int max_tier = std::min(level / 3, 4);	// increase 1 max_tier per 3 levels

		// the matrix

		bricks.reserve(static_cast<size_t>(height * width));	// reserve enough storage for all the bricks

		// from center of the matrix we get the top left corners

		int xout, yout;

		bb::to_top_left(xout, yout, VIRTUAL_WIDTH / 2, 70, height * (/*bricks[0].get_height()*/ 16), width * (/*bricks[0].get_width()*/ 32), bb::CENTER);

		// setting positions for each bricks
		
		do
		{
			for (int r = 0; r < height; r++)
			{
				if (!(rand() % 5))
				{
					// no row

					yout += 16;

					continue;
				}


				bool skip = rand() % 2;

				bool alt = rand() % 2;

				bool skip_front = skip ? rand() % 2 : 0;

				bool alt_front = alt ? rand() % 2 : 0;

				
				int color = rand() % (max_color + 1);

				int tier = rand() % (max_tier + 1);

				int alt_color = alt ? (rand() % (max_color + 1)) : 0;

				int alt_tier = skip ? (rand() % (max_tier + 1)) : 0;


				int tempx = (skip_front) ? xout + 32 : xout;
				
				int col_inc = skip ? 2 : 1;

				int x_inc = skip ? 64 : 32;

				//std::cout << "\nr: " << r << " alt: " << alt << " skip: " << skip << " tempx: " << tempx << " color: " << color << " tier: " << tier << " alt_color: " << alt_color << " alt_tier: " << alt_tier;

				for (int c = skip_front ? 1 : 0; c < width; c += col_inc)
				{
					if (alt)
					{
						bricks.push_back(brick_class(tempx, yout, (alt_front ? alt_color : color), (alt_front ? alt_tier : tier)));

						alt_front = !alt_front;
					}
					else
					{
						bricks.push_back(brick_class(tempx, yout, color, tier));
					}

					tempx += x_inc;
				}

				yout += 16;
			}
		} while (bricks.size() == 0);

		bricks.shrink_to_fit();
	}

	void clear_level()
	{
		bricks = {};
	}

	void update()
	{
		for (auto& brick : bricks)
		{
			// xout and yout gets the point of collision on the brick

			double xout, yout;

			if (brick.is_visible() && ball.collids(xout, yout, brick.x, brick.y, brick.get_width(), brick.get_height()))
			{
				// a brick is visible and collids with the ball

				/*
					as floating point numbers are not very precise we cannot check for equality
					instead we check for the difference
				*/

				auto side = bb::circle_aabb_collision_side(ball.x, ball.y, ball.get_width(), xout, yout, brick.x, brick.y, brick.get_width(), brick.get_height());

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
				}

				sound.setBuffer(sound_buffer[BRICK_HIT_2]);

				sound.play();

				brick.hit();
			}
		}
	}

	void render()
	{
		for (auto& brick : bricks)
		{
			brick.render();
		}
	}
};


void level_maker(int level, std::vector<brick_class> bricks)
{
	// no. of bricks row and column wise

	int height = 4 + (rand() % 5);	//  4 -> 8

	int width = 5 + 2 * (rand() % 4);	// odds 5 -> 11

	// max color and tier

	int max_color = std::min(level, 4);		// increase 1 max_color per level

	int max_tier = std::min(level / 3, 4);	// increase 1 max_tier per 3 levels

	// reserving space for the bricks

	bricks.reserve(static_cast<size_t>(height * width));	// reserve enough storage for all the bricks

	// from center of the matrix we get the top left corners

	int xout, yout;

	bb::to_top_left(xout, yout, VIRTUAL_WIDTH / 2, 70, height * (/*bricks height*/ 16), width * (/*bricks width*/ 32), bb::CENTER);

	// setting positions for each bricks

	do
	{
		for (int r = 0; r < height; r++)
		{
			if (!(rand() % 5))
			{
				// no row

				yout += 16;

				continue;
			}


			bool skip = rand() % 2;

			bool alt = rand() % 2;

			bool skip_front = skip ? rand() % 2 : 0;

			bool alt_front = alt ? rand() % 2 : 0;


			int color = rand() % (max_color + 1);

			int tier = rand() % (max_tier + 1);

			int alt_color = alt ? (rand() % (max_color + 1)) : 0;

			int alt_tier = skip ? (rand() % (max_tier + 1)) : 0;


			int tempx = (skip_front) ? xout + 32 : xout;

			int col_inc = skip ? 2 : 1;

			int x_inc = skip ? 64 : 32;

			//std::cout << "\nr: " << r << " alt: " << alt << " skip: " << skip << " tempx: " << tempx << " color: " << color << " tier: " << tier << " alt_color: " << alt_color << " alt_tier: " << alt_tier;

			for (int c = skip_front ? 1 : 0; c < width; c += col_inc)
			{
				if (alt)
				{
					bricks.push_back(brick_class(tempx, yout, (alt_front ? alt_color : color), (alt_front ? alt_tier : tier)));

					alt_front = !alt_front;
				}
				else
				{
					bricks.push_back(brick_class(tempx, yout, color, tier));
				}

				tempx += x_inc;
			}

			yout += 16;
		}
	} while (bricks.size() == 0);

	bricks.shrink_to_fit();
}