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

    counter_animation_velocity = 4;
    counter_animation_frame = 0;
    counter_animation_image = 0;
    game_started = false;
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
        if(rosalila()->receiver->isJoyPressed(1,0) && rosalila()->receiver->isJoyPressed(1,1))
        {
          break;
        }
      }
    }

    stage->logic();
    character1->logic();
    character2->logic();
    stage->draw();
    character1->draw();
    character2->draw();
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
    rosalila()->graphics->drawText(rosalila()->utility->toString(player1_wins), -300, 0, true, false);
    rosalila()->graphics->drawText(rosalila()->utility->toString(player2_wins), 300, 0, true, false);

    counter_animation_frame++;
    if(counter_animation_frame > counter_animation_velocity)
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
        rosalila()->graphics->screen_shake_effect.set(20,15,0,0);
        rosalila()->graphics->point_explosion_effect->explode(character1_hit_x, character1_hit_y, Color(255,0,0,0), 40);
    }
    if(character2_hit)
    {
        character2->cancel("on_hit");
        rosalila()->graphics->screen_shake_effect.set(20,15,0,0);
        rosalila()->graphics->point_explosion_effect->explode(character2_hit_x, character2_hit_y, Color(255,0,0,0), 40);
    }
    if(hurtbox_collision)
    {
        character1->x-=4;
        character2->x+=4;
    }

    if(!character1->isInBounds() && !game_over)
    {
        character1->cancel("fall");
        player2_wins++;
        game_over = true;

        counter_animation_frame = 0;
        counter_animation_image = 0;
        game_started = false;
    }
    if(!character2->isInBounds() && !game_over)
    {
        character2->cancel("fall");
        player1_wins++;
        game_over = true;

        counter_animation_frame = 0;
        counter_animation_image = 0;
        game_started = false;
    }

    if(game_over)
    {
      game_over_frames++;
      if(player1_wins == total_rounds)
      {
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
        if(wins_animation_frame > wins_animation_velocity)
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
        if(wins_animation_frame > wins_animation_velocity)
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
      }
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
