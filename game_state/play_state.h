#pragma once

class play_state : public BASE_STATE
{
	void Enter()
	{
		paddle.x = VIRTUAL_WIDTH / 2.0;

		paddle.y = VIRTUAL_HEIGHT - 32;
	}

	int Update(double dt)
	{
		paddle.update(dt);

		return -1;
	}

	void Render()
	{
		paddle.render();
	}

	void Exit()
	{}
}play;