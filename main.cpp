#include <iostream>
#include <read_textures.h>


int menu();
int game_jumping();
int highscores();
int rules();


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

void setSFXvolume(const float &volume){
    coin_sound.setVolume(volume);
    task_coin_sound.setVolume(volume);
    jump_sound.setVolume(volume);
    throw_sound.setVolume(volume);
    hit_sound.setVolume(volume);
    countdown.setVolume(volume);
    death.setVolume(volume);
    click.setVolume(volume);
    answer_correct_sound.setVolume(volume);
    answer_wrong_sound.setVolume(volume);
    minigame_end_horns.setVolume(volume);
}

void setmusicvolume(const float &volume){
    menu_music.setVolume(volume);
    mind_music.setVolume(volume);
    jumping_game_music.setVolume(volume);
    fighting_music.setVolume(volume);
}

void load_textures(){
    if(!menu_back_texture.loadFromFile("assets/menu/menu_back.png")){
        throw std::runtime_error("texture menu_back.png not found!");
    }
    if(!menu_button_textures.loadFromFile("assets/menu/options.png")){
        throw std::runtime_error("texture options.png not found!");
    }
    if(!hero_texture.loadFromFile("assets/character.png")){
        throw std::runtime_error("texture character.png not found!");
    }
    if(!jumping_elements_textures.loadFromFile("assets/spritesheet_jumper.png")){
        throw std::runtime_error("texture spritesheet_jumper.png not found!");
    }
    if(!rules_back.loadFromFile("assets/rules_back.png")){
        throw std::runtime_error("texture rules_back.png not found!");
    }
    if(!highscores_back.loadFromFile("assets/highscores_back.png")){
        throw std::runtime_error("texture highscores_back.png not found!");
    }
    if(!assassin_logo_texture.loadFromFile("assets/assassin_logo.png")){
        throw std::runtime_error("texture assassin_logo.png not found!");
    }
    if(!jumping_back_textures.loadFromFile("assets/background_1.png")){
        throw std::runtime_error("texture jumping_back_textures.png not found!");
    }
    if(!stationary_jumping_backgrounds.loadFromFile("assets/stationary_jumping_backgrounds.png")){
        throw std::runtime_error("texture stationary_jumping_backgrounds.png not found!");
    }
    if(!scoreboards_textures.loadFromFile("assets/scoreboards_textures.png")){
        throw std::runtime_error("texture scoreboards_textures.png not found!");
    }
    if(!mind_game_back_texture.loadFromFile("assets/mind_game_back_texture.png")){
        throw std::runtime_error("texture mind_game_back_texture.png not found!");
    }
    if(!fighting_game_back_texture.loadFromFile("assets/fighting_game_back_texture.png")){
        throw std::runtime_error("texture fighting_game_back_texture.png not found!");
    }
    if(!fighting_elements_textures.loadFromFile("assets/fighting_game_elements.png")){
        throw std::runtime_error("texture fighting_game_elements.png not found!");
    }
}
void load_fonts(){
    if(!font_comica.loadFromFile("assets/Comica_BD.ttf")){
        throw std::runtime_error("font Comica_BD.ttf not found!");
    }
    if(!font_comica_bold.loadFromFile("assets/Comica_BD_Bold.ttf")){
        throw std::runtime_error("font Comica_BD_Bold.ttf not found!");
    }
}
void load_sounds(){
    if(!coin_sound_buffer.loadFromFile("assets/sounds/coin_sound.wav")){
        throw std::runtime_error("sound coin_sound.wav not found!");
    }
    else{
        coin_sound.setBuffer(coin_sound_buffer);
    }
    if(!task_coin_sound_buffer.loadFromFile("assets/sounds/task_coin_sound.wav")){
        throw std::runtime_error("sound task_coin_sound.wav not found!");
    }
    else{
        task_coin_sound.setBuffer(task_coin_sound_buffer);
    }
    if(!jump_sound_buffer.loadFromFile("assets/sounds/jump_sound.wav")){
        throw std::runtime_error("sound jump_sound.wav not found!");
    }
    else{
        jump_sound.setBuffer(jump_sound_buffer);
    }
    if(!throw_sound_buffer.loadFromFile("assets/sounds/knife_throw.wav")){
        throw std::runtime_error("sound knife_throw.wav not found!");
    }
    else{
        throw_sound.setBuffer(throw_sound_buffer);
    }
    if(!hit_sound_buffer.loadFromFile("assets/sounds/target_hit.wav")){
        throw std::runtime_error("sound target_hit.wav not found!");
    }
    else{
        hit_sound.setBuffer(hit_sound_buffer);
    }
    if(!answer_correct_sound_buffer.loadFromFile("assets/sounds/answer_correct.wav")){
        throw std::runtime_error("sound answer_correct.wav not found!");
    }
    else{
        answer_correct_sound.setBuffer(answer_correct_sound_buffer);
    }
    if(!answer_wrong_sound_buffer.loadFromFile("assets/sounds/answer_wrong.wav")){
        throw std::runtime_error("sound answer_wrong.wav not found!");
    }
    else{
        answer_wrong_sound.setBuffer(answer_wrong_sound_buffer);
    }
    if(!minigame_end_horns_buffer.loadFromFile("assets/sounds/minigame_end_horns.wav")){
        throw std::runtime_error("sound minigame_end_horns.wav not found!");
    }
    else{
        minigame_end_horns.setBuffer(minigame_end_horns_buffer);
    }
    if(!countdown_buffer.loadFromFile("assets/sounds/countdown.wav")){
        throw std::runtime_error("sound countdown.wav not found!");
    }
    else{
        countdown.setBuffer(countdown_buffer);
    }
    if(!death_buffer.loadFromFile("assets/sounds/death.wav")){
        throw std::runtime_error("sound death.wav not found!");
    }
    else{
        death.setBuffer(death_buffer);
    }
    if(!click_buffer.loadFromFile("assets/sounds/click.wav")){
        throw std::runtime_error("sound click.wav not found!");
    }
    else{
        click.setBuffer(click_buffer);
    }
    if(!menu_music.openFromFile("assets/sounds/menu_music.ogg")){
        throw std::runtime_error("sound menu_music.ogg not found!");
    }
    else{
        menu_music.setLoop(true);
    }
    if(!mind_music.openFromFile("assets/sounds/mind_music.ogg")){
        throw std::runtime_error("sound mind_music.ogg not found!");
    }
    else{
        mind_music.setLoop(true);
    }
    if(!jumping_game_music.openFromFile("assets/sounds/jumping_music_mix.ogg")){
        throw std::runtime_error("sound jumping_music_mix.ogg not found!");
    }
    else{
        jumping_game_music.setLoop(true);
    }
    if(!fighting_music.openFromFile("assets/sounds/fighting_music.ogg")){
        throw std::runtime_error("sound fighting_music.ogg not found!");
    }
    else{
        fighting_music.setLoop(true);
    }

    setmusicvolume(60);
    setSFXvolume(100);

}

int main()
{
    try{
        load_textures();
        load_fonts();
        load_sounds();
    }
    catch (const std::exception &e) {
        std::cerr<<"ERROR: "<<e.what()<<std::endl;
        sf::sleep(sf::seconds(5));
        return 0;
    }
    menu_music.play();
    int x;
    do{
        x = menu();
        switch (x) {
        case 1: menu_music.stop();game_jumping();menu_music.play();break;
        case 2: highscores();break;
        case 3: rules();break;
        }
    }
    while(x!=0);
    return 0;
}
