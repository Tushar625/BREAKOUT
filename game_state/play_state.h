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

		return -1;
	}

	void Render()
	{
		level.render();

		ball.render();

		paddle.render();
	}

	void Exit()
	{
		level.clear_level();
	}
}play;