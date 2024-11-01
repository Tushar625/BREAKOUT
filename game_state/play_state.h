#pragma once

class play_state : public bb::BASE_STATE
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
		ball.update(dt);

		level.update();

		auto dir = paddle.update(dt);

		double xout, yout;

		if (ball.collids(xout, yout, paddle.x, paddle.y, paddle.get_width(), paddle.get_height()))
		{
			sound.setBuffer(sound_buffer[PADDLE_HIT]);

			sound.play();

			ball.dy = -std::abs(ball.dy);	// ball always goes up afer hitting the paddle

			double amp = 35 + std::abs((ball.x + ball.get_width() / 2.0) - (paddle.x + paddle.get_width() / 2.0));

			if (/*top*/bb::flx::relep_eq(yout, paddle.y))
			{
				// moving left and ball hits in the left

				if (dir == -1 && (ball.x + ball.get_width() / 2.0) < (paddle.x + paddle.get_width() / 2.0))
				{
					ball.dx -= amp;
				}

				// moving right and ball hits in the right

				if (dir == 1 && (ball.x + ball.get_width() / 2.0) > (paddle.x + paddle.get_width() / 2.0))
				{
					ball.dx += amp;
				}
			}
			else if (/*left*/bb::flx::relep_eq(xout, paddle.x))
			{
				if (dir == -1)
				{
					// paddle moving left

					ball.dx = -std::abs(ball.dx - amp);
				}
				else
				{
					ball.dx = -(std::abs(ball.dx));
				}
			}
			else if (/*right*/bb::flx::relep_eq(xout, paddle.x + paddle.get_width()))
			{
				if (dir == 1)
				{
					// paddle moving right

					ball.dx = std::abs(ball.dx + amp);
				}
				else
				{
					ball.dx = std::abs(ball.dx);
				}
			}
			
			ball.y = paddle.y - ball.get_height(); // always place ball on top
		}

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