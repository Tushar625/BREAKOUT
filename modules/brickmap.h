
/*
	This class repersents the entire brick map, it is created by inheriting sfml
	drawable class so that the entire brick map can be drawn with one WINDOW.draw()
	call, which is very efficient
*/

#pragma once


class BrickMap : public sf::Drawable
{
public:

	BrickMap() : m_texture(texture[MAIN]), m_brickW(32), m_brickH(16), m_brickN(6)/*6 bricks per row in the spritesheet*/
	{}

	void clear()
	{
		bricks.clear();

		bricks_data.clear();
	}

	// all bricks are destroyed or not

	bool empty() const
	{
		return bricks.empty();
	}

	// create the brickmap according to level

	/*
		how I make the brickmap:

		start with a solid matrix,
		
		**********
		**********
		**********
		**********
		
		effect 1: remove a row,
		
		**********
		
		**********
		**********
		
		effect 2: alternate the colors of bricks in a row,
		
		#*#*#*#*#*
		*#*#*#*#*#

		effect 3: skip bricks alternatively in a row,
		
		* * * * * 
		 * * * * *

		effect 4: do the both of last two effects

		 * # * # *
		* # * # * 
		 # * # * #
		# * # * #

		we randomly apply an effect on each row to generate our master piece pattern
	*/

	void level_maker(int level = 0)
	{
		// no. of bricks row and column wise

		int height = 3 + (rand() % 4);	//  3 -> 6

		int width = 5 + 2 * (rand() % 4);	// odds 5 -> 11

		// max color and tier

		int max_color = std::min(level, 4);		// increase 1 max_color per level

		int max_tier = std::min(level / 3, 3);	// increase 1 max_tier per 3 levels

		// reserving space for the bricks

		bricks.clear();

		bricks_data.clear();

		int index = 0;

		// allocate space for all the bricks

		bricks.resize(static_cast<size_t>(height * width * 6));

		bricks_data.resize(static_cast<size_t>(height * width));

		/*
			we use two triangles to represent each brick,

			vertex 0, 1, 2 = triangle 1

			vertex 3, 4, 5 = triangle 2

			vertex 0    = top left

			vertex 2, 4 = top right

			vertex 1, 3 = bottom left

			vertex 5    = bottom right
		*/

		// center of the matrix placed at (VIRTUAL_WIDTH / 2, 70)
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


				bool skip = rand() % 2;	// skip every next brick

				bool alt = rand() % 2;	// alternative colouring

				bool skip_front = skip ? rand() % 2 : 0;	// skip the first brick or not

				bool alt_front = alt ? rand() % 2 : 0;	// should the first brick get alternate colour or not


				// randomly select the color and tier

				int color = rand() % (max_color + 1);

				int tier = rand() % (max_tier + 1);

				int alt_color = alt ? (rand() % (max_color + 1)) : 0;

				int alt_tier = skip ? (rand() % (max_tier + 1)) : 0;


				int tempx = (skip_front) ? xout + 32 : xout;	// x coordinate of first brick in the row

				// if skipping is enabled we increment the column index by 2 to get the effect

				int col_inc = skip ? 2 : 1;

				int x_inc = skip ? 64 : 32;

				//std::cout << "\nr: " << r << " alt: " << alt << " skip: " << skip << " tempx: " << tempx << " color: " << color << " tier: " << tier << " alt_color: " << alt_color << " alt_tier: " << alt_tier;

				for (int c = skip_front ? 1 : 0; c < width; c += col_inc)
				{
					if (alt)
					{
						make_brick_vertex(index * 6, tempx, yout, (alt_front ? alt_color : color), (alt_front ? alt_tier : tier));

						// storing the score color tier data alongside bricks

						bricks_data[index] = { ((color + 1) * 10 + tier * 5), (alt_front ? alt_color : color), (alt_front ? alt_tier : tier) };
						
						alt_front = !alt_front;
					}
					else
					{
						make_brick_vertex(index * 6, tempx, yout, color, tier);

						// storing the score color tier data alongside bricks

						bricks_data[index] = { ((color + 1) * 10 + tier * 5), color, tier };
					}

					index++;

					tempx += x_inc;
				}

				//std::cout << "\n";

				yout += 16;
			}
		} while (bricks.size() == 0);

		// trim out excess allocated space

		bricks.resize(index * 6);

		bricks_data.resize(index);
	}

	/*
		must call it from update of play state  for collision detection and resolution
		and setting off an exlosion

		it must also check if all the bricks are broken and empty the bricks array after
		all bricks are briken
	*/

	inline void collision(ball_class& ball, int &score, bb::Firecracker& explo) noexcept
	{
		for(int i = 0; i < bricks_data.size();)
		{
			int ib = i * 6;	// 6 vertices represent a brick

			// xout and yout gets the point of collision on the brick

			double brick_x = bricks[ib].position.x, brick_y = bricks[ib].position.y;

			bricks_data_structure& brick_data = bricks_data[i];

			double xout, yout;	// gets the point of collision on the brick

			if (ball.collids(xout, yout, sf::FloatRect(brick_x, brick_y, m_brickW, m_brickH)))
			{
				// a brick is visible and collids with the ball

				// play the sound

				sound.setBuffer(sound_buffer[BRICK_HIT_2]);

				sound.play();
				
				// setting explosion

				explo.create(sf::Vector2f(brick_x + m_brickW / 2.0, brick_y + m_brickH / 2.0), BRICK_COLOR[brick_data.color], 2000);

				// from point of impact we get the point where we should put the ball after collision

				const bb::collision_box_side_metric& side = bb::circle_aabb_collision_side(ball.x, ball.y, ball.get_width(), xout, yout, brick_x, brick_y, m_brickW, m_brickH);

				// calculate the changes in balls speed

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

				// check whether we update or delete the brick

				if (brick_data.color == 0)
				{
					// updating score

					score += brick_data.score;

					// destroy the brick and its data

					bricks.erase(std::cbegin(bricks) + ib, std::cbegin(bricks) + ib + 6);

					bricks_data.erase(std::begin(bricks_data) + i);
				}
				else
				{
					// upgrade the brick

					make_brick_vertex(ib, brick_x, brick_y, --brick_data.color, brick_data.tier);
				}
			}
			else
			{
				// no collision

				++i;
			}
		}
	}

private:

	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.texture = &m_texture;

		// drawing the vertex array with triangles Primitive

		if (!bricks.empty())
		{
			target.draw(&bricks[0], bricks.size(), sf::Triangles, states);
		}
	}

	void make_brick_vertex(int index, int brickx, int bricky, int color, int tier)
	{
		// generating top left position of the brick on the texture

		/*
			start with a position in a matrix where row = color and col = tier

			convert that to an array, then convert that to a position in another matrix
			with m_brickN no. of columns,
			
			then multiply the row position with brick width and col position with brick
			height to get the top left (x, y) of the brick
		*/

		int x = (color * 4 /*no of tiers*/ + tier) % m_brickN * m_brickW;

		int y = (color * 4 /*no of tiers*/ + tier) / m_brickN * m_brickH;

		//std::cout << "(" << color << ", " << tier << ") -> " << "(" << x << ", " << y << ") ";

		bricks[index + 0] = { sf::Vector2f(brickx, bricky), sf::Vector2f(x, y) };

		bricks[index + 1] = { sf::Vector2f(brickx, bricky + m_brickH), sf::Vector2f(x, y + m_brickH) };

		bricks[index + 2] = { sf::Vector2f(brickx + m_brickW, bricky), sf::Vector2f(x + m_brickW, y) };

		bricks[index + 3] = { sf::Vector2f(brickx, bricky + m_brickH), sf::Vector2f(x, y + m_brickH) };

		bricks[index + 4] = { sf::Vector2f(brickx + m_brickW, bricky), sf::Vector2f(x + m_brickW, y) };

		bricks[index + 5] = { sf::Vector2f(brickx + m_brickW, bricky + m_brickH), sf::Vector2f(x + m_brickW, y + m_brickH) };
	}

	const sf::Texture& m_texture;

	const int m_brickW, m_brickH;	// height and width of individual bricks

	const int m_brickN;	// no. of bricks per row in the texture

	std::vector<sf::Vertex> bricks;

	struct bricks_data_structure
	{
		int score, color, tier;
	};

	std::vector<bricks_data_structure> bricks_data;

	sf::Sound sound;
};