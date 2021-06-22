#include <assetsmanager.h>

sf::Texture menu_back_texture;
sf::Texture hero_texture;
sf::Texture jumping_elements_textures;
sf::Texture menu_button_textures;
sf::Texture rules_back;
sf::Texture highscores_back;
sf::Texture assassin_logo_texture;
sf::Texture jumping_back_textures;
sf::Texture stationary_jumping_backgrounds;
sf::Texture scoreboards_textures;
sf::Texture mind_game_back_texture;
sf::Texture fighting_game_back_texture;
sf::Texture fighting_elements_textures;
sf::Font font_comica, font_comica_bold;

sf::SoundBuffer coin_sound_buffer,task_coin_sound_buffer,jump_sound_buffer, death_buffer, click_buffer;
sf::SoundBuffer throw_sound_buffer, hit_sound_buffer,countdown_buffer;//wav file for short sounds
sf::SoundBuffer answer_correct_sound_buffer,answer_wrong_sound_buffer,minigame_end_horns_buffer;

sf::Sound coin_sound,task_coin_sound,jump_sound;
sf::Sound throw_sound,hit_sound,countdown, death, click;
sf::Sound answer_correct_sound,answer_wrong_sound,minigame_end_horns;

sf::Music jumping_game_music, menu_music, mind_music, fighting_music; //ogg file for long music
