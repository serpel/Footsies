#include "CharacterSelect.h"

std::pair<string, string> received;

string getLocalPlayer1Input()
{
    if (rosalila()->receiver->isKeyPressed('d') || rosalila()->receiver->isJoyPressed(-6, 0))
    {
        return "6";
    }

    if (rosalila()->receiver->isKeyPressed('a') || rosalila()->receiver->isJoyPressed(-4, 0))
    {
        return "4";
    }

    if (rosalila()->receiver->isKeyPressed('w') || rosalila()->receiver->isJoyPressed(1, 0))
    {
        return "a";
    }

    return "5";
}

string getLocalPlayer2Input()
{
    if (rosalila()->receiver->isKeyPressed('l') || rosalila()->receiver->isJoyPressed(-6, 1))
    {
        return "6";
    }

    if (rosalila()->receiver->isKeyPressed('j') || rosalila()->receiver->isJoyPressed(-4, 1))
    {
        return "4";
    }

    if (rosalila()->receiver->isKeyPressed('i') || rosalila()->receiver->isJoyPressed(1, 1))
    {
        return "a";
    }

    return "5";
}

string getPlayer1Input(string game_type)
{
    if (game_type == "local")
    {
        return getLocalPlayer1Input();
    }
    if (game_type == "online")
    {
        return received.first;
    }
    return "";
}

string getPlayer2Input(string game_type)
{
    if (game_type == "local")
    {
        return getLocalPlayer2Input();
    }
    if (game_type == "online")
    {
        return received.second;
    }

    return "";
}

string characterSelect(string game_type, int player)
{
    Image *background = rosalila()->graphics->getTexture(assets_directory + "menu/character_select_bg.png");
    Image *cursor_player1 = rosalila()->graphics->getTexture(assets_directory + "menu/cursor_player1.png");
    Image *cursor_player2 = rosalila()->graphics->getTexture(assets_directory + "menu/cursor_player2.png");
    Image *cursor_player1_selected = rosalila()->graphics->getTexture(assets_directory + "menu/cursor_player1_selected.png");
    Image *cursor_player2_selected = rosalila()->graphics->getTexture(assets_directory + "menu/cursor_player2_selected.png");

    string character_directory = ".modio/mods/";
    //assets_directory + "character/"

    vector<string> character_directories = rosalila()->utility->getDirectoryNames(character_directory);
    vector<Image *> portraits;
    vector<vector<Image *>> idle_animations;
    vector<vector<int>> idle_animation_durations;
    int player1_idle_animation_frame = 0;
    int player2_idle_animation_frame = 0;
    int player1_idle_animation_image = 0;
    int player2_idle_animation_image = 0;

    for (int i = 0; i < (int)character_directories.size(); i++)
    {
        string directory_name = character_directories[i];
        portraits.push_back(rosalila()->graphics->getTexture(character_directory + directory_name + "/portrait.png"));

        Node *moves_node = rosalila()->parser->getNodes(character_directory + directory_name + "/displacement.xml");
        vector<Node *> move_nodes = moves_node->getNodesByName("Move");
        for (int i = 0; i < (int)move_nodes.size(); i++)
        {
            if (move_nodes[i]->attributes["name"] == "idle")
            {
                vector<Node *> frames = move_nodes[i]->getNodeByName("Frames")->getNodesByName("Frame");
                vector<Image *> idle_animation;
                vector<int> durations;
                for (int i = 0; i < (int)frames.size(); i++)
                {
                    idle_animation.push_back(rosalila()->graphics->getTexture(character_directory + directory_name + "/" + frames[i]->attributes["image"]));
                    durations.push_back(atoi(frames[i]->attributes["duration"].c_str()));
                }
                idle_animations.push_back(idle_animation);
                idle_animation_durations.push_back(durations);
            }
        }
    }

    vector<Image *> ready_anim;
    int p1_ready_framecounter = 0;
    int p2_ready_framecounter = 0;
    int ready_timing = 4;

    int p1_ready_currentframe = 0;
    int p2_ready_currentframe = 0;

    ready_anim.push_back(rosalila()->graphics->getTexture(assets_directory + "menu/ready/ready1.png"));
    ready_anim.push_back(rosalila()->graphics->getTexture(assets_directory + "menu/ready/ready2.png"));
    ready_anim.push_back(rosalila()->graphics->getTexture(assets_directory + "menu/ready/ready3.png"));
    ready_anim.push_back(rosalila()->graphics->getTexture(assets_directory + "menu/ready/ready3.png"));
    // vector<string> ready_frame_names = rosalila()->utility->getFileNames(assets_directory + "menu/ready");
    // for(int i = 0; i < (int)ready_frame_names.size(); i++){
    //   ready_anim.push_back(rosalila()->graphics->getTexture(assets_directory + "menu/ready/" + ready_frame_names[i]));
    // }

    int player1_cursor = 0;
    int player2_cursor = portraits.size() - 1;
    int player1_selection = -1;
    int player2_selection = -1;

    TTF_Font *menu_font = NULL;

    string font_path = assets_directory + "misc/font.ttf";
    menu_font = TTF_OpenFont(font_path.c_str(), 28);

    rosalila()->sound->playMusic(assets_directory + "menu/music.ogg", -1);
    rosalila()->sound->playSound("character_select_screen", -1, 0, 0, false);

    while (true)
    {
        if (game_type == "online")
        {
            received = rosalila()->net->receive2PlayerBuffers();
        }

        string player1_input = getPlayer1Input(game_type);
        string player2_input = getPlayer2Input(game_type);

        rosalila()->graphics->draw2DImage(background,
                                          background->getWidth(), background->getHeight(),
                                          0, 0,
                                          1.0,
                                          0.0,
                                          false,
                                          0, 0,
                                          Color(255, 255, 255, 255),
                                          0, 0,
                                          false,
                                          FlatShadow());

        if (player1_input[0] == '6' && player1_selection == -1)
        {
            player1_cursor++;
            if (player1_cursor >= (int)portraits.size())
                player1_cursor = 0;
            player1_idle_animation_frame = 0;
            player1_idle_animation_image = 0;
            rosalila()->sound->playSound("move_cursor", -1, 0, 0, false);
        }

        if (player1_input[0] == '4' && player1_selection == -1)
        {
            player1_cursor--;
            if (player1_cursor < 0)
                player1_cursor = portraits.size() - 1;
            player1_idle_animation_frame = 0;
            player1_idle_animation_image = 0;
            rosalila()->sound->playSound("move_cursor", -1, 0, 0, false);
        }

        if (player2_input[0] == '6' && player2_selection == -1)
        {
            player2_cursor++;
            if (player2_cursor >= (int)portraits.size())
                player2_cursor = 0;
            player2_idle_animation_frame = 0;
            player2_idle_animation_image = 0;
            rosalila()->sound->playSound("move_cursor", -1, 0, 0, false);
        }

        if (player2_input[0] == '4' && player2_selection == -1)
        {
            player2_cursor--;
            if (player2_cursor < 0)
                player2_cursor = portraits.size() - 1;
            player2_idle_animation_frame = 0;
            player2_idle_animation_image = 0;
            rosalila()->sound->playSound("move_cursor", -1, 0, 0, false);
        }

        if (player1_input[0] == 'a')
        {
            player1_selection = player1_cursor;

            rosalila()->sound->playSound("confirm", -1, 0, 0, false);
        }

        if (player2_input[0] == 'a')
        {
            player2_selection = player2_cursor;

            rosalila()->sound->playSound("confirm", -1, 0, 0, false);
        }

        if (game_type == "online")
        {
            string current_player_input = getLocalPlayer1Input();
            rosalila()->net->send(current_player_input);
        }

        for (int i = 0; i < (int)portraits.size(); i++)
        {
            int x = i * 120 + 372;
            int y = 90;

            rosalila()->graphics->draw2DImage(portraits[i],
                                              portraits[i]->getWidth(), portraits[i]->getHeight(),
                                              x, y,
                                              1.0,
                                              0.0,
                                              false,
                                              0, 0,
                                              Color(255, 255, 255, 255),
                                              0, 0,
                                              false,
                                              FlatShadow());

            if (player1_cursor == i)
            {
                if (player1_selection == -1)
                    rosalila()->graphics->draw2DImage(cursor_player1,
                                                      cursor_player1->getWidth(), cursor_player1->getHeight(),
                                                      x, y,
                                                      1.0,
                                                      0.0,
                                                      false,
                                                      0, 0,
                                                      Color(255, 255, 255, 255),
                                                      0, 0,
                                                      false,
                                                      FlatShadow());
                else
                {
                    rosalila()->graphics->draw2DImage(cursor_player1_selected,
                                                      cursor_player1_selected->getWidth(), cursor_player1_selected->getHeight(),
                                                      x, y,
                                                      1.0,
                                                      0.0,
                                                      false,
                                                      0, 0,
                                                      Color(255, 255, 255, 255),
                                                      0, 0,
                                                      false,
                                                      FlatShadow());

                    if (p1_ready_currentframe < (int)ready_anim.size() - 1)
                    {
                        p1_ready_framecounter++;
                        if (p1_ready_framecounter > ready_timing)
                        {
                            p1_ready_framecounter = 0;
                            p1_ready_currentframe++;
                        }
                    }

                    rosalila()->graphics->draw2DImage(
                        ready_anim[p1_ready_currentframe],
                        ready_anim[p1_ready_currentframe]->getWidth(), ready_anim[p1_ready_currentframe]->getHeight(),
                        44, 155,
                        1.0, 0.0, false, 0, 0, Color(255, 255, 255, 255), 0, 0, false, FlatShadow());
                }
            }

            if (player2_cursor == i)
            {
                if (player2_selection == -1)
                    rosalila()->graphics->draw2DImage(cursor_player2,
                                                      cursor_player2->getWidth(), cursor_player2->getHeight(),
                                                      x, y,
                                                      1.0,
                                                      0.0,
                                                      false,
                                                      0, 0,
                                                      Color(255, 255, 255, 255),
                                                      0, 0,
                                                      false,
                                                      FlatShadow());
                else
                {
                    rosalila()->graphics->draw2DImage(cursor_player2_selected,
                                                      cursor_player2_selected->getWidth(), cursor_player2_selected->getHeight(),
                                                      x, y,
                                                      1.0,
                                                      0.0,
                                                      false,
                                                      0, 0,
                                                      Color(255, 255, 255, 255),
                                                      0, 0,
                                                      false,
                                                      FlatShadow());

                    if (p2_ready_currentframe < (int)ready_anim.size() - 1)
                    {
                        p2_ready_framecounter++;
                        if (p2_ready_framecounter > ready_timing)
                        {
                            p2_ready_framecounter = 0;
                            p2_ready_currentframe++;
                        }
                    }

                    rosalila()->graphics->draw2DImage(
                        ready_anim[p2_ready_currentframe],
                        ready_anim[p2_ready_currentframe]->getWidth(), ready_anim[p2_ready_currentframe]->getHeight(),
                        944, 410,
                        1.0, 0.0, false, 0, 0, Color(255, 255, 255, 255), 0, 0, false, FlatShadow());
                }
            }
        }

        if (p1_ready_currentframe == (int)ready_anim.size() - 1 && p2_ready_currentframe == (int)ready_anim.size() - 1)
        {
            Footsies *footsies = new Footsies(character_directories[player1_selection], character_directories[player2_selection], 3, game_type, player);
            footsies->gameLoop();
            rosalila()->sound->playMusic(assets_directory + "menu/music.ogg", -1);
            player1_selection = -1;
            player2_selection = -1;
            p2_ready_currentframe = 0;
            p1_ready_currentframe = 0;
        }

        player1_idle_animation_frame++;
        if (player1_idle_animation_frame >= idle_animation_durations[player1_cursor][player1_idle_animation_image])
        {
            player1_idle_animation_frame = 0;
            player1_idle_animation_image++;
            if (player1_idle_animation_image >= (int)idle_animations[player1_cursor].size())
                player1_idle_animation_image = 0;
        }

        player2_idle_animation_frame++;
        if (player2_idle_animation_frame >= idle_animation_durations[player2_cursor][player2_idle_animation_image])
        {
            player2_idle_animation_frame = 0;
            player2_idle_animation_image++;
            if (player2_idle_animation_image >= (int)idle_animations[player2_cursor].size())
                player2_idle_animation_image = 0;
        }

        Image *player1_idle_image = idle_animations[player1_cursor][player1_idle_animation_image];
        rosalila()->graphics->draw2DImage(player1_idle_image,
                                          player1_idle_image->getWidth(), player1_idle_image->getHeight(),
                                          -100, -170,
                                          1.0,
                                          0.0,
                                          false,
                                          0, 0,
                                          Color(255, 255, 255, 255),
                                          0, 0,
                                          false,
                                          FlatShadow());

        Image *player2_idle_image = idle_animations[player2_cursor][player2_idle_animation_image];
        rosalila()->graphics->draw2DImage(player2_idle_image,
                                          player2_idle_image->getWidth(), player2_idle_image->getHeight(),
                                          780, 80,
                                          1.0,
                                          0.0,
                                          true,
                                          0, 0,
                                          Color(255, 255, 255, 255),
                                          0, 0,
                                          false,
                                          FlatShadow());

        rosalila()->graphics->drawText(menu_font, character_directories[player1_cursor], 85, 375, false, false);
        rosalila()->graphics->drawText(menu_font, character_directories[player2_cursor], 975, 627, false, false);
        rosalila()->graphics->drawText(menu_font, "Player1: " + received.first, 0, 0, false, false);
        rosalila()->graphics->drawText(menu_font, "Player2: " + received.second, 500, 0, false, false);

        rosalila()->update();
    }
}