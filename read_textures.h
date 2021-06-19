#ifndef READ_TEXTURES_H
#define READ_TEXTURES_H

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

extern sf::Texture jumping_elements_textures,hero_texture,menu_back_texture,menu_button_textures,rules_back;
extern sf::Texture highscores_back,assassin_logo_texture,jumping_back_textures;
extern sf::Texture stationary_jumping_backgrounds,scoreboards_textures,mind_game_back_texture;
extern sf::Texture fighting_game_back_texture, fighting_elements_textures;

extern sf::Font font_comica, font_comica_bold;

extern sf::SoundBuffer coin_sound_buffer,task_coin_sound_buffer,jump_sound_buffer, death_buffer, click_buffer;
extern sf::SoundBuffer throw_sound_buffer, hit_sound_buffer, countdown_buffer;//wav file for short sounds
extern sf::SoundBuffer answer_correct_sound_buffer,answer_wrong_sound_buffer, minigame_end_horns_buffer;

extern sf::Sound coin_sound,task_coin_sound,jump_sound;
extern sf::Sound throw_sound, hit_sound, countdown, death, click;
extern sf::Sound answer_correct_sound,answer_wrong_sound, minigame_end_horns;

extern sf::Music jumping_game_music, menu_music, mind_music, fighting_music; //ogg file for long music

#endif // READ_TEXTURES_H
