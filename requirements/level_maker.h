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


class BrickMap : public sf::Drawable
{
public:

	BrickMap() : m_texture(texture[MAIN]), m_brickW(32), m_brickH(16), m_brickN(6)
	{}

	void clear()
	{
		bricks.clear();

		bricks_data.clear();
	}

	bool empty() const
	{
		return bricks.empty();
	}

	void level_maker(int level = 10)
	{
		// no. of bricks row and column wise

		int height = 3 + (rand() % 4);	//  3 -> 6

		int width = 5 + 2 * (rand() % 4);	// odds 5 -> 11

		// max color and tier

		int max_color = std::min(level, 4);		// increase 1 max_color per level

		int max_tier = std::min(level / 3, 4);	// increase 1 max_tier per 3 levels

		// reserving space for the bricks

		bricks.clear();

		bricks_data.clear();

		bricks.reserve(static_cast<size_t>(height * width * 6));	// reserve enough storage for all the bricks

		bricks_data.reserve(static_cast<size_t>(height * width));

		/*
			we use two triangles to represent each brick,

			vertex 0, 1, 2 = triangle 1

			vertex 3, 4, 5 = triangle 2

			vertex 0    = top left

			vertex 2, 4 = top right

			vertex 1, 3 = bottom left

			vertex 5    = bottom right
		*/

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
						auto vertex = make_brick_vertex(tempx, yout, (alt_front ? alt_color : color), (alt_front ? alt_tier : tier));

						bricks.push_back(vertex[0]);

						bricks.push_back(vertex[1]);

						bricks.push_back(vertex[2]);

						bricks.push_back(vertex[3]);

						bricks.push_back(vertex[4]);

						bricks.push_back(vertex[5]);

						// storing the score color tier data alongside bricks

						bricks_data.push_back({ ((color + 1) * 10 + tier * 5), (alt_front ? alt_color : color), (alt_front ? alt_tier : tier) });
						
						alt_front = !alt_front;
					}
					else
					{
						auto vertex = make_brick_vertex(tempx, yout, color, tier);

						bricks.push_back(vertex[0]);

						bricks.push_back(vertex[1]);

						bricks.push_back(vertex[2]);

						bricks.push_back(vertex[3]);

						bricks.push_back(vertex[4]);

						bricks.push_back(vertex[5]);

						// storing the score color tier data alongside bricks

						bricks_data.push_back({ ((color + 1) * 10 + tier * 5), color, tier });
					}

					tempx += x_inc;
				}

				//std::cout << "\n";

				yout += 16;
			}
		} while (bricks.size() == 0);

		bricks.shrink_to_fit();

		bricks_data.shrink_to_fit();
	}

	void collision(ball_class& ball, int &score)
	{
		for(int i = 0; i < bricks_data.size();)
		{
			int ib = i * 6;

			// xout and yout gets the point of collision on the brick

			auto brick_x = bricks[ib].position.x, brick_y = bricks[ib].position.y;

			double xout, yout;

			if (ball.collids(xout, yout, brick_x, brick_y, m_brickW, m_brickH))
			{
				// a brick is visible and collids with the ball

				// play the sound

				sound.setBuffer(sound_buffer[BRICK_HIT_2]);

				sound.play();
				
				// setting explosion

				//explo.create(sf::Vector2f(brick.x + brick.get_width() / 2.0, brick.y + brick.get_height() / 2.0));

				/*
					as floating point numbers are not very precise we cannot check for equality
					instead we check for the difference
				*/

				auto side = bb::circle_aabb_collision_side(ball.x, ball.y, ball.get_width(), xout, yout, brick_x, brick_y, m_brickW, m_brickH);

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

				if (bricks_data[i].color == 0)
				{
					score += bricks_data[i].score;	// updating the brick after collision, playing sound and returning score

					// destroy the brick and its data and don't update ibrick

					/*auto newIter = ibrick;*/

					bricks.erase(std::cbegin(bricks) + ib, std::cbegin(bricks) + ib + 6);

					bricks_data.erase(std::begin(bricks_data) + i);
				}
				else
				{
					// upgrade the brick

					auto vertex = make_brick_vertex(brick_x, brick_y, --bricks_data[i].color, bricks_data[i].tier);

					bricks[ib++] = vertex[0];

					bricks[ib++] = vertex[1];

					bricks[ib++] = vertex[2];

					bricks[ib++] = vertex[3];

					bricks[ib++] = vertex[4];

					bricks[ib] = vertex[5];
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

	std::vector<sf::Vertex> make_brick_vertex(int brickx, int bricky, int color, int tier)
	{
		std::vector<sf::Vertex> vertex(6);

		// generating top left position of the brick on the texture

		int x = (color * 4 /*no of tiers*/ + tier) % m_brickN * m_brickW;

		int y = (color * 4 /*no of tiers*/ + tier) / m_brickN * m_brickH;

		//std::cout << "(" << color << ", " << tier << ") -> " << "(" << x << ", " << y << ") ";

		vertex[0] = { sf::Vector2f(brickx, bricky), sf::Vector2f(x, y) };

		vertex[1] = { sf::Vector2f(brickx, bricky + m_brickH), sf::Vector2f(x, y + m_brickH) };

		vertex[2] = { sf::Vector2f(brickx + m_brickW, bricky), sf::Vector2f(x + m_brickW, y) };

		vertex[3] = { sf::Vector2f(brickx, bricky + m_brickH), sf::Vector2f(x, y + m_brickH) };

		vertex[4] = { sf::Vector2f(brickx + m_brickW, bricky), sf::Vector2f(x + m_brickW, y) };

		vertex[5] = { sf::Vector2f(brickx + m_brickW, bricky + m_brickH), sf::Vector2f(x + m_brickW, y + m_brickH) };

		return vertex;
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