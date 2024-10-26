#pragma once

#include<cmath>

class ball_class
{
	sf::Sound snd;

	int width, height;

public:

	double x, y, dx, dy;

	int index;

	ball_class()
	{
		x = y = dx = dy = 0;

		width = height = 8;

		index = 0;
	}

	int get_width() const
	{
		return width;
	}

	int get_height() const
	{
		return height;
	}

	void reset(int ball_type = 0)
	{
		dx = (100 + rand() % 51) * (rand() % 2 ? -1 : 1);
		
		dy = (100 + rand() % 51) * (rand() % 2 ? -1 : 1);

		// place the ball on the paddle
		
		x = paddle.x + paddle.get_width() / 2.0;
			
		y = paddle.y - height - 1;

		index = ball_type;
	}

	//bool collids(double xb, double yb, int widthb, int heightb)
	//{
	//	// if top of any of the boxes below the bottom of others

	//	if (/* top */ y + height < yb || /* bottom */ yb + heightb < y)
	//	{
	//		return false;
	//	}

	//	// if left of any of the boxes after the right of others

	//	if (/* left */ x + width < xb || /* right */ xb + widthb < x)
	//	{
	//		return false;
	//	}

	//	return true;
	//}

	bool collids(double& xp, double& yp, double xb, double yb, int widthb, int heightb) const
	{
		auto radius = get_width() / 2.0;

		sf::Vector2f aabb_half(widthb / 2.0f, heightb / 2.0f);

		sf::Vector2f center((x + radius), (y + radius)); // center of the circle (ball)

		sf::Vector2f box_center((xb + aabb_half.x), (yb + aabb_half.y)); // center of the box

		auto delta = center - box_center;

		//std::cout << B.x << ", " << B.y << "\n";

		//std::cout << C.x << ", " << C.y << "\n";
		//
		//std::cout << delta.x << ", " << delta.y << "\n";

		delta.x = std::max(-aabb_half.x, std::min(delta.x, aabb_half.x));
		
		delta.y = std::max(-aabb_half.y, std::min(delta.y, aabb_half.y));

		//std::cout << widthb / 2.0f << ", " << heightb / 2.0f << "\n";

		//std::cout << delta.x << ", " << delta.y << "\n";

		auto nearest_point = box_center + delta;	// point on the box

		xp = nearest_point.x;

		yp = nearest_point.y;

		delta = nearest_point - center; // distance between P and C

		//std::cout << xb << ", " << yb << "\n";

		//std::cout << xb + widthb << ", " << yb + heightb << "\n";
		
		//std::cout << "a " << nearest_point.x << ", " << nearest_point.y << "\n";

		auto dist = sqrt(delta.x * delta.x + delta.y * delta.y);

		/*if (dist <= radius)
		{
			std::cout << "box: " << xb << ", " << yb << "\n";

			std::cout << "ball: " << x << ", " << y << "\n";
		}*/

		return dist < radius;
	}

	void update(double dt)
	{
		x += dx * dt;

		y += dy * dt;

		// top collision

		if (y < 0)
		{
			y = 0;

			dy = -dy;

			snd.setBuffer(sound_buffer[WALL_HIT]);

			snd.play();
		}

		// left collision

		if (x < 0)
		{
			x = 0;

			dx = -dx;

			snd.setBuffer(sound_buffer[WALL_HIT]);

			snd.play();
		}

		// right collision

		if (x + width > VIRTUAL_WIDTH)
		{
			x = VIRTUAL_WIDTH - width;

			dx = -dx;

			snd.setBuffer(sound_buffer[WALL_HIT]);

			snd.play();
		}
	}

	void render()
	{
		sprite[BALL][index].setPosition(sf::Vector2f(x, y));

		WINDOW.draw(sprite[BALL][index]);
	}
} ball;