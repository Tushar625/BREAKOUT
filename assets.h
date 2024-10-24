
// the assets for this game

#pragma once

sf::Font font;

sf::Text small_text, medium_text, large_text;

std::vector<sf::Texture> texture{ TEXTURE_COUNT };

std::vector<sf::SoundBuffer> sound{ SOUND_COUNT };

sf::Music music;