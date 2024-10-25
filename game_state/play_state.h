#pragma once

class play_state : public BASE_STATE
{
	sf::Sound snd;

	void Enter()
	{
		paddle.x = VIRTUAL_WIDTH / 2.0 - paddle.get_width() / 2.0;

		paddle.y = VIRTUAL_HEIGHT - 32;

		ball.reset(1);
	}

	int Update(double dt)
	{
		if (ball.collids(paddle.x, paddle.y, paddle.get_width(), paddle.get_height()))
		{
			snd.setBuffer(sound_buffer[PADDLE_HIT]);

			snd.play();

			ball.dy = -ball.dy;
		}
		
		ball.update(dt);

		paddle.update(dt);

		return -1;
	}

	void Render()
	{
		paddle.render();

		ball.render();
	}

	void Exit()
	{}
}play;