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

	void Enter()
	{}

	int Update(double dt)
	{
		auto& ball = s_data->ball;

		auto& paddle = s_data->paddle;

		//===================
		// firecracker effect
		//===================

		s_data -> explo.update(dt);

		//================================
		// detecting and resolving collision with bricks
		//================================

		s_data->bricks.collision(s_data->ball, s_data->current_level_score, s_data->explo);

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

		//==========================================================
		// ball goes below the screen before all bricks are finished
		//==========================================================

		if (!s_data->bricks.empty() && ball.y > VIRTUAL_HEIGHT)
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

		if (s_data->all_bricks_explosions_left())
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

		s_data->render_bricks_explosions();
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