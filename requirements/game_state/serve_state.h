
// serve state of the game it represent the time when the ball is ready to serve

#pragma once



extern class play_state play;

void set_play_state(game_data_type* i_data, level_data_type* s_data);



class serve_state : public bb::BASE_STATE
{
	public:
	
	// the data it receives from initial state

	game_data_type* i_data;

	serve_state() : i_data(nullptr)
	{
		// msg used to print score and level

		msg = small_text;

		msg.setFillColor(sf::Color::Cyan);

		// this semi-transparent instruction will be displayed in the middle of the screen

		instructions = small_text;
		
		instructions.setString("Home (ESC) Start (ENTER)");

		instructions.setPosition(sf::Vector2f(VIRTUAL_WIDTH / 2.0 - instructions.getLocalBounds().width / 2, VIRTUAL_HEIGHT - 80));

		sf::Color cyan = sf::Color::Cyan;

		cyan.a = 100;

		instructions.setFillColor(cyan);
	}

	private:

	level_data_type s_data;	// level data created here 

	sf::Text msg, instructions;

	sf::Sound sound;

	void Enter()
	{
		// place the paddle in the middle

		s_data.paddle.x = VIRTUAL_WIDTH / 2.0 - s_data.paddle.get_width() / 2.0;

		s_data.paddle.y = VIRTUAL_HEIGHT - 20;

		// place the ball on top the paddle with dx, dy set to random

		s_data.ball.reset(
			VIRTUAL_WIDTH / 2.0 - s_data.ball.get_width() / 2.0,
			s_data.paddle.y - s_data.ball.get_width()
		);

		// if bricks array is empty create a new one and set level score to 0

		if (s_data.is_new_level())
		{
			s_data.start_level(i_data -> level);
		}
	}

	int Update(double dt)
	{
		s_data.explo.update(dt);

		if (bb::INPUT.isPressed(sf::Keyboard::Scan::Enter))
		{
			// serve the ball

			sound.setBuffer(sound_buffer[PADDLE_HIT]);

			sound.play();

			set_play_state(i_data, &s_data);

			game_state.change_to(play);
		}

		if (bb::INPUT.isPressed(sf::Keyboard::Scan::Escape))
		{
			// goto home

			sound.setBuffer(sound_buffer[PAUSE]);

			sound.play();

			game_state.change_to(initial);
		}

		// move paddle and ball left or right

		auto dir = s_data.paddle.update(dt);

		if (dir)
		{
			s_data.ball.x += dir * s_data.paddle.dx * dt;
		}

		return -1;
	}

	void Render()
	{
		// score hearts and level

		msg.setString("Score: " + std::to_string(i_data->score_till_last_level + s_data.current_level_score));

		msg.setPosition(sf::Vector2f(VIRTUAL_WIDTH / 2.0 - VIRTUAL_WIDTH / 3.0, 0));

		bb::WINDOW.draw(msg);

		render_health(i_data -> health);

		msg.setString("Level: " + std::to_string(i_data->level));

		msg.setPosition(sf::Vector2f(VIRTUAL_WIDTH / 2.0 + VIRTUAL_WIDTH / 3.0 - msg.getLocalBounds().width, 0));

		bb::WINDOW.draw(msg);

		// ball paddle and bricks

		s_data.ball.render();

		s_data.paddle.render();

		s_data.render_bricks_explosions();

		// instructions

		bb::WINDOW.draw(instructions);
	}

}serve;

// following functions are used to send data to serve state from initial state

void set_serve_state(game_data_type* i_data)
{
	serve.i_data = i_data;
}