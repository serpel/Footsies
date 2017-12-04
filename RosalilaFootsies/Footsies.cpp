#include "Footsies.h"

Footsies::Footsies(string character1_name, string character2_name, int total_rounds)
{
  this->initial_separation = 200;
  this->stage_boundaries = 250;
  this->character1 = new Character(this, 0,rosalila()->graphics->screen_width/2-initial_separation, character1_name);
  this->character2 = new Character(this, 1,rosalila()->graphics->screen_width/2+initial_separation, character2_name);
  this->character1->opponent = character2;
  this->character2->opponent = character1;
  this->stage = new Stage("Aliens");
  this->frame = 1;
  this->player1_wins = 0;
  this->player2_wins = 0;
  this->game_over = false;
  this->game_over_frames = 0;
  this->total_rounds = total_rounds;

  this->character1_name = character1->name;
  for(short i = 0; i < this->character1_name.length(); ++i)
    this->character1_name[i] = toupper(this->character1_name[i]);

  this->character2_name = character2->name;
  for(short i = 0; i < this->character2_name.length(); ++i)
    this->character2_name[i] = toupper(this->character2_name[i]);

  hit_images.push_back(rosalila()->graphics->getTexture(assets_directory + "misc/hiteffects/1.png"));
  hit_images.push_back(rosalila()->graphics->getTexture(assets_directory + "misc/hiteffects/2.png"));
  hit_images.push_back(rosalila()->graphics->getTexture(assets_directory + "misc/hiteffects/3.png"));

  hit_animation_velocity = 5;
  player1_hit_animation_framecounter = 0;
  player2_hit_animation_framecounter = 0;
  player1_hit_current_image = 0;
  player2_hit_current_image = 0;
  player1_hit_active = false;
  player2_hit_active = false;
  player1_hit_posx = 0;
  player1_hit_posy = 0;
  player2_hit_posx = 0;
  player2_hit_posy = 0;


  player1_wins_images.push_back(rosalila()->graphics->getTexture(assets_directory + "misc/game_over/player1_wins/1.png"));
  player1_wins_images.push_back(rosalila()->graphics->getTexture(assets_directory + "misc/game_over/player1_wins/2.png"));
  player1_wins_images.push_back(rosalila()->graphics->getTexture(assets_directory + "misc/game_over/player1_wins/3.png"));
  player1_wins_images.push_back(rosalila()->graphics->getTexture(assets_directory + "misc/game_over/player1_wins/4.png"));
  player1_wins_images.push_back(rosalila()->graphics->getTexture(assets_directory + "misc/game_over/player1_wins/5.png"));
  player1_wins_images.push_back(rosalila()->graphics->getTexture(assets_directory + "misc/game_over/player1_wins/6.png"));
  player1_wins_images.push_back(rosalila()->graphics->getTexture(assets_directory + "misc/game_over/player1_wins/7.png"));

  player2_wins_images.push_back(rosalila()->graphics->getTexture(assets_directory + "misc/game_over/player2_wins/1.png"));
  player2_wins_images.push_back(rosalila()->graphics->getTexture(assets_directory + "misc/game_over/player2_wins/2.png"));
  player2_wins_images.push_back(rosalila()->graphics->getTexture(assets_directory + "misc/game_over/player2_wins/3.png"));
  player2_wins_images.push_back(rosalila()->graphics->getTexture(assets_directory + "misc/game_over/player2_wins/4.png"));
  player2_wins_images.push_back(rosalila()->graphics->getTexture(assets_directory + "misc/game_over/player2_wins/5.png"));
  player2_wins_images.push_back(rosalila()->graphics->getTexture(assets_directory + "misc/game_over/player2_wins/6.png"));
  player2_wins_images.push_back(rosalila()->graphics->getTexture(assets_directory + "misc/game_over/player2_wins/7.png"));

  win_anim_velocities.push_back(6);
  win_anim_velocities.push_back(6);
  win_anim_velocities.push_back(6);
  win_anim_velocities.push_back(6);
  win_anim_velocities.push_back(32);
  win_anim_velocities.push_back(10);
  win_anim_velocities.push_back(10);

  wins_animation_velocity = 5;
  wins_animation_frame = 0;
  wins_animation_image = 0;

  counter_images.push_back(rosalila()->graphics->getTexture(assets_directory + "misc/counter/1.png"));
  counter_images.push_back(rosalila()->graphics->getTexture(assets_directory + "misc/counter/2.png"));
  counter_images.push_back(rosalila()->graphics->getTexture(assets_directory + "misc/counter/3.png"));
  counter_images.push_back(rosalila()->graphics->getTexture(assets_directory + "misc/counter/4.png"));
  counter_images.push_back(rosalila()->graphics->getTexture(assets_directory + "misc/counter/5.png"));
  counter_images.push_back(rosalila()->graphics->getTexture(assets_directory + "misc/counter/6.png"));
  counter_images.push_back(rosalila()->graphics->getTexture(assets_directory + "misc/counter/7.png"));
  counter_images.push_back(rosalila()->graphics->getTexture(assets_directory + "misc/counter/8.png"));
  counter_images.push_back(rosalila()->graphics->getTexture(assets_directory + "misc/counter/9.png"));
  counter_images.push_back(rosalila()->graphics->getTexture(assets_directory + "misc/counter/10.png"));
  counter_images.push_back(rosalila()->graphics->getTexture(assets_directory + "misc/counter/11.png"));
  counter_images.push_back(rosalila()->graphics->getTexture(assets_directory + "misc/counter/12.png"));

  counter_anim_velocities.push_back(4);
  counter_anim_velocities.push_back(4);
  counter_anim_velocities.push_back(18);
  counter_anim_velocities.push_back(4);
  counter_anim_velocities.push_back(4);
  counter_anim_velocities.push_back(18);
  counter_anim_velocities.push_back(4);
  counter_anim_velocities.push_back(4);
  counter_anim_velocities.push_back(18);
  counter_anim_velocities.push_back(4);
  counter_anim_velocities.push_back(4);
  counter_anim_velocities.push_back(18);

  counter_animation_velocity = 4;
  counter_animation_frame = 0;
  counter_animation_image = 0;
  game_started = false;

  scoreboard_player1 = rosalila()->graphics->getTexture(assets_directory + "misc/scoreboards/player1.png");
  scoreboard_player2 = rosalila()->graphics->getTexture(assets_directory + "misc/scoreboards/player2.png");

  this->character_name_font = NULL;
  string font_path = assets_directory+"misc/font.ttf";
  character_name_font = TTF_OpenFont( font_path.c_str(), 15 );

  rosalila()->sound->playMusic(assets_directory+"stages/" + this->stage->name + "/music.ogg", -1);
  rosalila()->sound->playSound("countdown", -1, 0, 0, false);
}

void Footsies::gameLoop()
{
  while(true)
  {

    if(player1_wins == total_rounds || player2_wins == total_rounds)
    {
      if(game_over_frames > 100)
      {
        if(rosalila()->receiver->isKeyPressed('w') || rosalila()->receiver->isKeyPressed('i'))
        {
          break;
        }
        if(rosalila()->receiver->isJoyPressed(1,0) || rosalila()->receiver->isJoyPressed(1,1))
        {
          break;
        }
      }
    }

    stage->logic();
    character1->logic();
    character2->logic();
    stage->draw();
    if(character1->last_attack_frame > character2->last_attack_frame)
    {
      character2->draw();
      character1->draw();
    }else
    {
      character1->draw();
      character2->draw();
    }

    this->drawScoreboards();

    if(!game_started)
    {
      if(!game_over)
      {
        rosalila()->graphics->draw2DImage
        (   counter_images[counter_animation_image],
            counter_images[counter_animation_image]->getWidth(),counter_images[counter_animation_image]->getHeight(),
            rosalila()->graphics->screen_width/2 - counter_images[counter_animation_image]->getWidth()/2,
            rosalila()->graphics->screen_height/2 - counter_images[counter_animation_image]->getHeight()/2,
            1.0,
            0.0,
            false,
            0,0,
            Color(255,255,255,255),
            0,0,
            false,
            FlatShadow());
      }
    }
    else
    {
        character1->game_started = true;
        character2->game_started = true;
    }

    counter_animation_frame++;
        if(counter_animation_frame > counter_anim_velocities[counter_animation_image])
    {
      counter_animation_frame = 0;
      counter_animation_image++;
      if(counter_animation_image >= (int)counter_images.size())
      {
        counter_animation_image = 0;
        game_started = true;
      }
    }

    Frame* character1_current_frame = character1->getCurrentMove()->getCurrentFrame();
    Frame* character2_current_frame = character2->getCurrentMove()->getCurrentFrame();

    vector<Hitbox*> character1_hitboxes = character1_current_frame->hitboxes;
    vector<Hitbox*> character2_hitboxes = character2_current_frame->hitboxes;
    vector<Hitbox*> character1_hurtboxes = character1_current_frame->hurtboxes;
    vector<Hitbox*> character2_hurtboxes = character2_current_frame->hurtboxes;
    bool character1_hit = false;
    bool character2_hit = false;
    bool hurtbox_collision = false;
    int character2_hit_x = -1;
    int character2_hit_y = -1;
    int character1_hit_x = -1;
    int character1_hit_y = -1;
    for(int i=0;i< (int)character1_hitboxes.size();i++)
    {
        Hitbox character1_hitbox = character1_hitboxes[i]->getPlacedHitbox(character1->x + character1_current_frame->x,0);
        if(character1->isFlipped())
            character1_hitbox = character1_hitboxes[i]->getFlippedHitbox().getPlacedHitbox(character1->x - character1_current_frame->x,0);

        for(int j=0;j< (int)character2_hurtboxes.size();j++)
        {
            Hitbox character2_hurtbox = character2_hurtboxes[j]->getPlacedHitbox(character2->x + character2_current_frame->x,0);
            if(character2->isFlipped())
                character2_hurtbox = character2_hurtboxes[j]->getFlippedHitbox().getPlacedHitbox(character2->x - character2_current_frame->x,0);

            if(character1_hitbox.collides(character2_hurtbox))
            {
                character2_hit = true;
                character2_hit_x = character2_hurtbox.x;
                character2_hit_y = 620 - character1_hitbox.y + character1_hitbox.height/2;
            }
        }
    }
    for(int i=0;i< (int)character2_hitboxes.size();i++)
    {
        Hitbox character2_hitbox = character2_hitboxes[i]->getPlacedHitbox(character2->x + character2_current_frame->x,0);
        if(character2->isFlipped())
            character2_hitbox = character2_hitboxes[i]->getFlippedHitbox().getPlacedHitbox(character2->x - character2_current_frame->x,0);

        for(int j=0;j< (int)character1_hurtboxes.size();j++)
        {
            Hitbox character1_hurtbox = character1_hurtboxes[j]->getPlacedHitbox(character1->x + character1_current_frame->x,0);
            if(character1->isFlipped())
                character1_hurtbox = character1_hurtboxes[j]->getFlippedHitbox().getPlacedHitbox(character1->x - character1_current_frame->x,0);

            if(character2_hitbox.collides(character1_hurtbox))
            {
                character1_hit = true;
                character1_hit_x = 100;
                character1_hit_y = 500;
                character1_hit_x = character1_hurtbox.x + character1_hurtbox.width;
                character1_hit_y = 620 - character2_hitbox.y + character2_hitbox.height/2;
            }
        }
    }
    for(int i=0;i< (int)character2_hurtboxes.size();i++)
    {

        Hitbox character2_hurtbox = character2_hurtboxes[i]->getPlacedHitbox(character2->x + character2_current_frame->x,0);
        if(character2->isFlipped())
            character2_hurtbox = character2_hurtboxes[i]->getFlippedHitbox().getPlacedHitbox(character2->x - character2_current_frame->x,0);

        for(int j=0;j< (int)character1_hurtboxes.size();j++)
        {
            Hitbox character1_hurtbox = character1_hurtboxes[j]->getPlacedHitbox(character1->x + character1_current_frame->x,0);
            if(character1->isFlipped())
                character1_hurtbox = character1_hurtboxes[j]->getFlippedHitbox().getPlacedHitbox(character1->x - character1_current_frame->x,0);

            if(character2_hurtbox.collides(character1_hurtbox))
            {
                hurtbox_collision = true;
            }
        }
    }

    if(character1_hit)
    {
        character1->cancel("on_hit");

        string sound_on_connect = character2->name + "#" + character2->current_state + "#on_connect";
        if(rosalila()->sound->soundExists(sound_on_connect))
          rosalila()->sound->playSound(sound_on_connect, -1, 0, 0, false);

        rosalila()->graphics->screen_shake_effect.set(20,15,0,0);
        player1_hit_posx = character1_hit_x;
        player1_hit_posy = character1_hit_y;
        player1_hit_active = true;
    }
    if(character2_hit)
    {
        character2->cancel("on_hit");

        string sound_on_connect = character1->name + "#" + character1->current_state + "#on_connect";
        if(rosalila()->sound->soundExists(sound_on_connect))
          rosalila()->sound->playSound(sound_on_connect, -1, 0, 0, false);

        rosalila()->graphics->screen_shake_effect.set(20,15,0,0);
        // rosalila()->graphics->point_explosion_effect->explode(character2_hit_x, character2_hit_y, Color(255,0,0,0), 40);
        player2_hit_posx = character2_hit_x;
        player2_hit_posy = character2_hit_y;
        player2_hit_active = true;
    }
    if(hurtbox_collision)
    {
        character1->x-=4;
        character2->x+=4;
    }

    if(player1_hit_active){
      player1_hit_animation_framecounter++;
      if(player1_hit_animation_framecounter > hit_animation_velocity){
        player1_hit_current_image++;
        player1_hit_animation_framecounter = 0;
      }

      if(player1_hit_current_image < (int)hit_images.size()){
        rosalila()->graphics->draw2DImage(
          hit_images[player1_hit_current_image],
          hit_images[player1_hit_current_image]->getWidth(), hit_images[player1_hit_current_image]->getHeight(),
          player1_hit_posx - (hit_images[player1_hit_current_image]->getWidth()/2),
          player1_hit_posy - (hit_images[player1_hit_current_image]->getHeight()/2),
          1.0, 0.0, false, 0, 0, Color(255, 255, 255, 255), 0, 0, false, FlatShadow()
        );

      }else{
        player1_hit_active = false;
        player1_hit_animation_framecounter = 0;
        player1_hit_current_image = 0;
      }
    }

    if(player2_hit_active){
      player2_hit_animation_framecounter++;
      if(player2_hit_animation_framecounter > hit_animation_velocity){
        player2_hit_current_image++;
        player2_hit_animation_framecounter = 0;
      }

      if(player2_hit_current_image < (int)hit_images.size()){
        rosalila()->graphics->draw2DImage(
          hit_images[player2_hit_current_image],
          hit_images[player2_hit_current_image]->getWidth(), hit_images[player2_hit_current_image]->getHeight(),
          player2_hit_posx - (hit_images[player2_hit_current_image]->getWidth()/2),
          player2_hit_posy - (hit_images[player2_hit_current_image]->getHeight()/2),
          1.0, 0.0, false, 0, 0, Color(255, 255, 255, 255), 0, 0, false, FlatShadow()
        );

      }else{
        player2_hit_active = false;
        player2_hit_animation_framecounter = 0;
        player2_hit_current_image = 0;
      }
    }

    bool player1_just_won = !character2->isInBounds() && !game_over;
    bool player2_just_won = !character1->isInBounds() && !game_over;

    if(player1_just_won || player2_just_won)
    {
      game_over = true;
      counter_animation_frame = 0;
      counter_animation_image = 0;
      game_started = false;

      if(player1_just_won)

      if(player1_just_won)
      {
        character2->cancel("fall");
        if(!player2_just_won)
          player1_wins++;
      }
      if(player2_just_won)
      {
        character1->cancel("fall");
        if(!player1_just_won)
          player2_wins++;
      }
    }

    if(game_over)
    {
      if(player1_wins == total_rounds)
      {
        if(game_over_frames==1)
          rosalila()->sound->playSound("player1_wins", -1, 0, 0, false);
        rosalila()->graphics->draw2DImage
        (   player1_wins_images[wins_animation_image],
            player1_wins_images[wins_animation_image]->getWidth(),player1_wins_images[wins_animation_image]->getHeight(),
            rosalila()->graphics->screen_width/2 - player1_wins_images[wins_animation_image]->getWidth()/2,
            rosalila()->graphics->screen_height/2 - player1_wins_images[wins_animation_image]->getHeight()/2,
            1.0,
            0.0,
            false,
            0,0,
            Color(255,255,255,255),
            0,0,
            false,
            FlatShadow());

        wins_animation_frame++;
        if(wins_animation_frame > win_anim_velocities[wins_animation_image])
        {
          wins_animation_frame = 0;
          wins_animation_image++;
          if(wins_animation_image >= (int)player1_wins_images.size())
          {
            wins_animation_image = 5;
          }
        }

      }else if(player2_wins == total_rounds)
      {
        if(game_over_frames==1)
          rosalila()->sound->playSound("player2_wins", -1, 0, 0, false);
        rosalila()->graphics->draw2DImage
        (   player2_wins_images[wins_animation_image],
            player2_wins_images[wins_animation_image]->getWidth(),player2_wins_images[wins_animation_image]->getHeight(),
            rosalila()->graphics->screen_width/2 - player2_wins_images[wins_animation_image]->getWidth()/2,
            rosalila()->graphics->screen_height/2 - player2_wins_images[wins_animation_image]->getHeight()/2,
            1.0,
            0.0,
            false,
            0,0,
            Color(255,255,255,255),
            0,0,
            false,
            FlatShadow());
        wins_animation_frame++;
        if(wins_animation_frame > win_anim_velocities[wins_animation_image])
        {
          wins_animation_frame = 0;
          wins_animation_image++;
          if(wins_animation_image >= (int)player2_wins_images.size())
          {
            wins_animation_image = 5;
          }
        }
      }else if(game_over_frames == 50)
      {
        character1->x = rosalila()->graphics->screen_width/2-initial_separation;
        character2->x = rosalila()->graphics->screen_width/2+initial_separation;

        counter_animation_frame = 0;
        counter_animation_image = 0;
        game_started = false;

        frame = 1;
        game_over = false;
        game_over_frames=0;
        character1->cancel("idle");
        character2->cancel("idle");
        character1->game_started = false;
        character2->game_started = false;

        rosalila()->sound->playSound("countdown", -1, 0, 0, false);
      }
      game_over_frames++;
    }

    if(rosalila()->receiver->isKeyPressed('r'))
    {
      character1->cancel("idle");
      character1->x = rosalila()->graphics->screen_width/2-initial_separation;
      character2->cancel("idle");
      character2->x = rosalila()->graphics->screen_width/2+initial_separation;

      counter_animation_frame = 0;
      counter_animation_image = 0;
      game_started = false;

      frame = 1;
      character1->game_started = false;
      character2->game_started = false;
      player1_wins = 0;
      player2_wins = 0;
    }

    frame++;
    rosalila()->update();
  }
}

void Footsies::drawScoreboards()
{
  int player1_scoreboard_x = 200;
  int player1_scoreboard_y = 50;
  int player2_scoreboard_x = 800;
  int player2_scoreboard_y = 50;

  rosalila()->graphics->draw2DImage
  (   scoreboard_player1,
      scoreboard_player1->getWidth(),scoreboard_player1->getHeight(),
      player1_scoreboard_x, player1_scoreboard_y,
      1.0,
      0.0,
      false,
      0,0,
      Color(255,255,255,255),
      0,0,
      false,
      FlatShadow());
  rosalila()->graphics->draw2DImage
  (   scoreboard_player2,
      scoreboard_player2->getWidth(),scoreboard_player2->getHeight(),
      player2_scoreboard_x, player2_scoreboard_y,
      1.0,
      0.0,
      false,
      0,0,
      Color(255,255,255,255),
      0,0,
      false,
      FlatShadow());

  int portrait1_hit_effect = 255;
  if(character1->current_state == "on_hit")
    portrait1_hit_effect = (this->frame*20)%255;

  int portrait2_hit_effect = 255;
  if(character2->current_state == "on_hit")
    portrait2_hit_effect = (this->frame*20)%255;

  rosalila()->graphics->draw2DImage
  (   character1->portrait,
      character1->portrait->getWidth(),character1->portrait->getHeight(),
      player1_scoreboard_x + 24 - 6, player1_scoreboard_y + 18 - 6,
      1.0,
      0.0,
      false,
      0,0,
      Color(255, portrait1_hit_effect, portrait1_hit_effect, 255),
      0,0,
      false,
      FlatShadow());

    rosalila()->graphics->draw2DImage
    (   character2->portrait,
        character2->portrait->getWidth(),character2->portrait->getHeight(),
        player2_scoreboard_x + 192 - 6, player2_scoreboard_y + 18 - 6,
        1.0,
        0.0,
        false,
        0,0,
        Color(255, portrait2_hit_effect, portrait2_hit_effect, 255),
        0,0,
        false,
        FlatShadow());

  rosalila()->graphics->drawText(rosalila()->utility->toString(player1_wins), player1_scoreboard_x + 183, player1_scoreboard_y + 27, false, false);
  rosalila()->graphics->drawText(this->character_name_font, character1_name, player1_scoreboard_x + 140, player1_scoreboard_y + 97, false, false);

  rosalila()->graphics->drawText(rosalila()->utility->toString(player2_wins), player2_scoreboard_x + 75, player2_scoreboard_y + 27, false, false);
  rosalila()->graphics->drawText(this->character_name_font, character2_name, player2_scoreboard_x + 35, player2_scoreboard_y + 97, false, false);

}
