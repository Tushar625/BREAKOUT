#pragma once


void level_maker(int level, std::vector<brick_class>& bricks)
{
	// no. of bricks row and column wise

	int height = 3 + (rand() % 4);	//  3 -> 6

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