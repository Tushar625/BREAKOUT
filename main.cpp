
#define SET_ANTIALIASHING	// this macro allows you to set antialiashing

#include"requirements.h"

// the value returned by this function will be set as the value for antialiashing

unsigned int set_antialiashing()
{
	return 0;
}

// loading the game states into the state machine

STATE_MACHINE game_state({ &initial, &play });

inline bool Game::Create()
{
	WINDOW.setTitle("Breakout prototype 2");



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



	sprite[PADDLE] = get_paddle_sprites();

	sprite[BALL] = get_ball_sprites();


	
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


	
	// setting window size



	WINDOW.setSize(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT));

	auto this_view = WINDOW.getView();

	this_view.reset(sf::FloatRect(0, 0, VIRTUAL_WIDTH, VIRTUAL_HEIGHT));

	WINDOW.setView(this_view);



	// other settings



	srand(time(0));

	MY_GAME.set_fps(30);

	game_state.change_to(INITIAL);

	

	//text.setFillColor(sf::Color::White);

	// ~~~~ [write your statements here] ~~~~

	return SUCCESS;
}

inline bool Game::Update(double dt)
{
	// exit

	if (INPUT.isClosed() || INPUT.isPressed(sf::Keyboard::Scan::Escape) || game_state.Update(dt) == EXIT)
		return STOP_GAME_LOOP;

	/*auto pos = INPUT.pointer();

	if(INPUT.isPressedM(sf::Mouse::Left))
	{
		std::cout << "{" << pos.x << ", " << pos.y << "}\n";
	}*/

	return !STOP_GAME_LOOP;
}

inline void Game::Render()
{
	sf::Sprite bg_sprite;

	bg_sprite.setTexture(texture[BACKGROUND]);

	auto bg_size = texture[BACKGROUND].getSize();

	bg_sprite.setScale(sf::Vector2f(VIRTUAL_WIDTH / (float)(bg_size.x - 1), VIRTUAL_HEIGHT / (float)(bg_size.y - 1)));

	WINDOW.draw(bg_sprite);

	game_state.Render();

	small_text.setString(std::to_string(MY_GAME.get_fps()));

	WINDOW.draw(small_text);
}