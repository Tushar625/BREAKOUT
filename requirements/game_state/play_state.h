
// represent the play state, the actual gameplay is managed here



#pragma once



extern class message_state message;

void set_message_state(const std::string& main_message, const std::string& complimentary_message, const std::string& next_button_text, int score);



class play_state : public bb::BASE_STATE
{
	public:

	// data received from serve state

	game_data_type* i_data;

	level_data_type* s_data;

	play_state() : i_data(nullptr), s_data(nullptr)
	{
		// msg used to print score and level

		msg = small_text;

		msg.setFillColor(sf::Color::Cyan);

		// this semi-transparent instruction will be displayed in the middle of the screen

		instructions = small_text;

		instructions.setString("Pause (ESC, P)");

		instructions.setPosition(sf::Vector2f(VIRTUAL_WIDTH / 2.0 - instructions.getLocalBounds().width / 2, VIRTUAL_HEIGHT - 80));

		sf::Color cyan = sf::Color::Cyan;

		cyan.a = 100;

		instructions.setFillColor(cyan);
	}

	private:

	sf::Text msg, instructions;

	sf::Sound sound;

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

		int dir = paddle.update(dt);

		//================================
		// detecting collision with paddle
		//================================

		double xout, yout;

		// paddle must not collide with a ball that is going up

		if (ball.dy > 0 && ball.collids(xout, yout, paddle))
		{
			const bb::collision_box_side_metric& side = bb::circle_aabb_collision_side(ball.x, ball.y, ball.get_width(), xout, yout, paddle.x, paddle.y, paddle.get_width(), paddle.get_height());

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
				ball.dx = -(std::abs(ball.dx)) - ((dir == -1) ? 35 : 0);	// always goes left
			}
			
			if (side.right)
			{
				ball.dx = std::abs(ball.dx) + ((dir == 1) ? 35 : 0);	// always goes right
			}

			if (!side.bottom)
			{
				ball.dy = -ball.dy;	// always goes up if not bottom
			}
		}

		//==========================================================
		// ball goes below the screen before all bricks are finished
		//==========================================================

		if (ball.y > VIRTUAL_HEIGHT && !s_data->bricks.empty())
		{
			sound.setBuffer(sound_buffer[HURT]);

			sound.play();

			if (i_data->health > 0)
			{
				--i_data->health;

				game_state.change_to(serve);
			}
			else
			{
				// defeat

				s_data->end_level();

				// prepare next state data

				std::string main_message = "GAME OVER";

				std::string next_button_text = "RESET";

				int score = (s_data->current_level_score + i_data->score_till_last_level);

				std::string complimentary_message = (score > i_data->highest_score) ? "NEW RECORD" : ("HIGHEST: " + std::to_string(i_data->highest_score));

				// reset i_data

				i_data->reset(s_data->current_level_score);

				set_message_state(main_message, complimentary_message, next_button_text, score);

				game_state.change_to(message);
			}

			return -1;
		}

		//======================
		//all bricks are crushed
		//======================

		if (s_data->all_bricks_explosions_finished())
		{
			// victory

			sound.setBuffer(sound_buffer[VICTORY]);

			sound.play();

			s_data->end_level();

			// update i_data

			i_data->next_level(s_data->current_level_score);

			// prepare data to send to message state

			std::string main_message = "LEVEL UP!";

			std::string complimentary_message = "HEALTH +1";

			std::string next_button_text = "LEVEL " + std::to_string(i_data->level);

			int score = i_data->score_till_last_level;

			set_message_state(main_message, complimentary_message, next_button_text, score);

			game_state.change_to(message);

			return -1;
		}

		//=====
		//pause
		//=====

		if (bb::INPUT.isPressed(sf::Keyboard::Scan::Escape) || bb::INPUT.isPressed(sf::Keyboard::Scan::P))
		{
			sound.setBuffer(sound_buffer[PAUSE]);

			sound.play();

			game_state.change_to(serve);
		}

		return -1;
	}

	void Render()
	{
		bb::WINDOW.draw(instructions);

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

}play;

// following functions are used to send data to play state from serve state

void set_play_state(game_data_type* i_data, level_data_type* s_data)
{
	play.i_data = i_data;

	play.s_data = s_data;
}