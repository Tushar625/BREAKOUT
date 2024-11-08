#pragma once

class play_state : public bb::BASE_STATE
{
	public:

	game_data_type* i_data;

	level_data_type* s_data;

	play_state() : i_data(nullptr), s_data(nullptr)
	{
		msg = small_text;

		msg.setFillColor(sf::Color::Cyan);
	}

	private:

	sf::Text msg;

	sf::Sound sound;

	bb::Firecracker explo;

	void Enter()
	{}

	int Update(double dt)
	{
		auto& ball = s_data->ball;

		auto& paddle = s_data->paddle;

		//===================
		// firecracker effect
		//===================

		explo.update(dt);

		//================================
		// detecting collision with bricks
		//================================

		for (auto& brick : s_data->bricks)
		{
			// xout and yout gets the point of collision on the brick

			double xout, yout;

			if (brick.is_visible() && ball.collids(xout, yout, brick.x, brick.y, brick.get_width(), brick.get_height()))
			{
				// a brick is visible and collids with the ball

				// setting explosion

				explo.create(sf::Vector2f(brick.x + brick.get_width() / 2.0, brick.y + brick.get_height() / 2.0));

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

				s_data -> current_level_score += brick.hit();	// updating the brick after collision, playing sound and returning score
			}
		}

		//================================
		// update ball and paddle position
		//================================

		s_data->ball.update(dt);

		auto dir = paddle.update(dt);

		//================================
		// detecting collision with paddle
		//================================

		double xout, yout;

		// paddle must not collide with a ball that is going up

		if (ball.dy > 0 && ball.collids(xout, yout, paddle.x, paddle.y, paddle.get_width(), paddle.get_height()))
		{
			auto side = bb::circle_aabb_collision_side(ball.x, ball.y, ball.get_width(), xout, yout, paddle.x, paddle.y, paddle.get_width(), paddle.get_height());

			sound.setBuffer(sound_buffer[PADDLE_HIT]);

			sound.play();

			// moving left and ball hits in the left

			if (dir == -1 && (ball.x + ball.get_width() / 2.0) < (paddle.x + paddle.get_width() / 2.0))
			{
				ball.dx += -35 - ((paddle.x + paddle.get_width() / 2.0) - (ball.x + ball.get_width() / 2.0));
			}

			// moving right and ball hits in the right

			if (dir == 1 && (ball.x + ball.get_width() / 2.0) > (paddle.x + paddle.get_width() / 2.0))
			{
				ball.dx += 35 + ((ball.x + ball.get_width() / 2.0) - (paddle.x + paddle.get_width() / 2.0));
			}

			if (side.left)
			{
				ball.dx = -(std::abs(ball.dx));	// always goes left
			}
			
			if (side.right)
			{
				ball.dx = std::abs(ball.dx);	// always goes right
			}

			if (!side.bottom)
			{
				ball.dy = -ball.dy;	// always goes up if not bottom
			}
		}

		//===========================
		// ball goes below the screen
		//===========================

		if (ball.y > VIRTUAL_HEIGHT)
		{
			if (i_data->health > 0)
			{
				i_data->health--;

				game_state.change_to(serve);
			}
			else
			{
				// defeat

				s_data->end_level();

				int total_score = (s_data->current_level_score + i_data->score_till_last_level);

				bool is_highest_score = (total_score > i_data->highest_score);

				i_data->reset();

				game_state.change_to(initial);
			}

			return -1;
		}

		//======================
		//all bricks are crushed
		//======================

		if (s_data->all_bricks_crushed())
		{
			// victory

			s_data->end_level();

			int total_score = (s_data->current_level_score + i_data->score_till_last_level);

			bool is_highest_score = (total_score > i_data->highest_score);

			i_data->score_till_last_level += s_data->current_level_score;

			if (i_data->health < MAX_HEALTH)
				++(i_data->health);

			++(i_data->level);

			game_state.change_to(serve);

			return -1;
		}

		//=====
		//pause
		//=====

		if (bb::INPUT.isPressed(sf::Keyboard::Scan::Escape) || bb::INPUT.isPressed(sf::Keyboard::Scan::P))
		{
			game_state.change_to(serve);
		}

		return -1;
	}

	void Render()
	{
		// firecracker, score hearts and level

		bb::WINDOW.draw(explo);

		msg.setString("Score: " + std::to_string(i_data->score_till_last_level + s_data->current_level_score));

		msg.setPosition(sf::Vector2f(VIRTUAL_WIDTH / 2.0 - VIRTUAL_WIDTH / 3.0, 0));

		bb::WINDOW.draw(msg);

		render_health(i_data->health);

		msg.setString("Level: " + std::to_string(i_data->level));

		msg.setPosition(sf::Vector2f(VIRTUAL_WIDTH / 2.0 + VIRTUAL_WIDTH / 3.0 - msg.getLocalBounds().width, 0));

		bb::WINDOW.draw(msg);

		// ball paddle and bricks

		s_data -> ball.render();

		s_data->paddle.render();

		s_data->render_bricks();
	}

	/*void Exit()
	{
		level.clear_level();
	}*/
}play;

// following functions are used to send data to serve state from other states

void set_play_state(game_data_type* i_data, level_data_type* s_data)
{
	play.i_data = i_data;

	play.s_data = s_data;
}