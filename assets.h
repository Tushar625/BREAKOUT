
// the assets for this game

#pragma once

sf::Font font;

sf::Text small_text, medium_text, large_text;

std::vector<sf::Texture> texture{ TEXTURE_COUNT };

std::vector<std::vector<sf::Sprite>> sprite{ SPRITE_COUNT };

std::vector<sf::SoundBuffer> sound{ SOUND_COUNT };

sf::Music music;




// loading the assets




class ASSET_LOADER
{
	public:

	ASSET_LOADER()
	{
		// loading fonts



		if (!font.loadFromFile("font/font.ttf"))
		{
			std::cout << "can't load font\n";
		}

		font.setSmooth(false);

		small_text.setFont(font); small_text.setCharacterSize(SMALL_FONT_SIZE);

		medium_text.setFont(font); medium_text.setCharacterSize(MEDIUM_FONT_SIZE);

		large_text.setFont(font); large_text.setCharacterSize(LARGE_FONT_SIZE);



		// loading images



		if (!texture[BACKGROUND].loadFromFile("image/background.png"))
		{
			std::cout << "can't load background\n";
		}

		if (!texture[MAIN].loadFromFile("image/breakout.png"))
		{
			std::cout << "can't load main\n";
		}

		if (!texture[ARROWS].loadFromFile("image/arrows.png"))
		{
			std::cout << "can't load arrows\n";
		}

		if (!texture[HEARTS].loadFromFile("image/hearts.png"))
		{
			std::cout << "can't load hearts\n";
		}

		if (!texture[PARTICLE].loadFromFile("image/particle.png"))
		{
			std::cout << "can't load particles\n";
		}



		// generating sprites



		sprite[PADDLE] = get_paddle_sprites(texture[MAIN]);

		sprite[BALL] = get_ball_sprites(texture[MAIN]);

		sprite[BRICK] = get_brick_sprites(texture[MAIN]);



		// loading sounds



		if (!sound[PADDLE_HIT].loadFromFile("sound/paddle_hit.wav"))
		{
			std::cout << "can't load paddle_hit\n";
		}

		if (!sound[SCORE].loadFromFile("sound/score.wav"))
		{
			std::cout << "can't load score\n";
		}

		if (!sound[WALL_HIT].loadFromFile("sound/wall_hit.wav"))
		{
			std::cout << "can't load wall_hit\n";
		}

		if (!sound[CONFIRM].loadFromFile("sound/confirm.wav"))
		{
			std::cout << "can't load confirm\n";
		}

		if (!sound[SELECT].loadFromFile("sound/select.wav"))
		{
			std::cout << "can't load select\n";
		}

		if (!sound[NO_SELECT].loadFromFile("sound/no_select.wav"))
		{
			std::cout << "can't load no_select\n";
		}

		if (!sound[BRICK_HIT_1].loadFromFile("sound/brick_hit_1.wav"))
		{
			std::cout << "can't load brick_hit_1\n";
		}

		if (!sound[BRICK_HIT_2].loadFromFile("sound/brick_hit_2.wav"))
		{
			std::cout << "can't load brick_hit_2\n";
		}

		if (!sound[HURT].loadFromFile("sound/hurt.wav"))
		{
			std::cout << "can't load hurt\n";
		}

		if (!sound[VICTORY].loadFromFile("sound/victory.wav"))
		{
			std::cout << "can't load victory\n";
		}

		if (!sound[RECOVER].loadFromFile("sound/recover.wav"))
		{
			std::cout << "can't load recover\n";
		}

		if (!sound[HIGH_SCORE].loadFromFile("sound/high_score.wav"))
		{
			std::cout << "can't load high_score\n";
		}

		if (!sound[PAUSE].loadFromFile("sound/pause.wav"))
		{
			std::cout << "can't load pause\n";
		}

		if (!music.openFromFile("sound/music.wav"))
		{
			std::cout << "can't load music\n";
		}
	}
}obj;