#pragma once

class play_state : public BASE_STATE
{
	sf::Sound sound;

	level_maker level;

	void Enter()
	{
		level.set_level();

		paddle.x = VIRTUAL_WIDTH / 2.0 - paddle.get_width() / 2.0;

		paddle.y = VIRTUAL_HEIGHT - 20;

		ball.reset(1);
	}

	int Update(double dt)
	{	
		level.update();

		auto dir = paddle.update(dt);

		double xout, yout;

		if (ball.collids(xout, yout, paddle.x, paddle.y, paddle.get_width(), paddle.get_height()))
		{
			sound.setBuffer(sound_buffer[PADDLE_HIT]);

			sound.play();

			ball.dy = -std::abs(ball.dy);	// ball always goes up afer hitting the paddle

			// moving left and ball hits in the left

			if (dir == -1 && (ball.x + ball.get_width() / 2.0) < (paddle.x + paddle.get_width() / 2.0))
			{
				ball.dx += - 50 - ((paddle.x + paddle.get_width() / 2.0) - (ball.x + ball.get_width() / 2.0));
			}

			// moving right and ball hits in the right

			if (dir == 1 && (ball.x + ball.get_width() / 2.0) > (paddle.x + paddle.get_width() / 2.0))
			{
				ball.dx += 50 + ((ball.x + ball.get_width() / 2.0) - (paddle.x + paddle.get_width() / 2.0));
			}

			// place the ball on the paddle

			ball.y = paddle.y - ball.get_height();

			//ball.x = xout;

			//ball.y = yout;
		}

		ball.update(dt);

		return -1;
	}

	void Render()
	{
		level.render();

		paddle.render();

		ball.render();
	}

	void Exit()
	{
		level.clear_level();
	}
}play;