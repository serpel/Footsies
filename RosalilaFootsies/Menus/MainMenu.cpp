#include "MainMenu.h"

string mainMenu()
{
    vector<string> options;
    options.push_back("Play");
    options.push_back("Create online match");
    options.push_back("Join online match");
    options.push_back("Download mods");
    options.push_back("Exit");
    int option_cursor = 0;
    Image *background = rosalila()->graphics->getTexture(assets_directory + "menu/white_background.png");
    string input = "";
    SDL_StartTextInput();
    bool input_finished = false;
    string font_path = assets_directory + "misc/font.ttf";
    TTF_Font *label_font = TTF_OpenFont(font_path.c_str(), 18);
    TTF_Font *input_font = TTF_OpenFont(font_path.c_str(), 18);
    TTF_Font *selected_font = TTF_OpenFont(font_path.c_str(), 21);

    while (!input_finished)
    {
        rosalila()->graphics->draw2DImage(background,
                                          rosalila()->graphics->screen_width, rosalila()->graphics->screen_height,
                                          0, 0,
                                          1.0,
                                          0.0,
                                          false,
                                          0, 0,
                                          Color(0, 0, 0, 255),
                                          0, 0,
                                          false,
                                          FlatShadow());

        rosalila()->graphics->drawText(label_font, "Main menu", 0, rosalila()->graphics->screen_height / 2 - 200, true, false);

        for (int i = 0; i < (int)options.size(); i++)
        {
            TTF_Font *option_font = input_font;
            if (i == option_cursor)
                option_font = selected_font;
            rosalila()->graphics->drawText(option_font, options[i], 0, 300 + 100 * i, true, false);
        }

        if (rosalila()->receiver->isKeyPressed(SDL_SCANCODE_UP))
        {
            option_cursor--;
            if (option_cursor < 0)
                option_cursor = options.size() - 1;
        }
        if (rosalila()->receiver->isKeyPressed(SDL_SCANCODE_DOWN))
        {
            option_cursor++;
            if (option_cursor >= (int)options.size())
                option_cursor = 0;
        }

        if (rosalila()->receiver->isKeyPressed(SDLK_RETURN))
        {
            cout << "Cursor:" << option_cursor << endl;
            if (option_cursor == 0) //Play
            {
                characterSelect("local", 0);
            }
            if (option_cursor == 1) //Create online match
            {
                rosalila()->net->send("olas");

                while (true)
                {
                    string received_message = rosalila()->net->receive();
while(rosalila()->net->receive()!="");

                    if (received_message.find('|')!=std::string::npos)
                    {
                        characterSelect("online", 1);
                        break;
                    }
                    string displayed_message = "Waiting for opponent, your match code is: " + received_message;

                    rosalila()->graphics->draw2DImage(background,
                                                      rosalila()->graphics->screen_width, rosalila()->graphics->screen_height,
                                                      0, 0,
                                                      1.0,
                                                      0.0,
                                                      false,
                                                      0, 0,
                                                      Color(0, 0, 0, 255),
                                                      0, 0,
                                                      false,
                                                      FlatShadow());

                    if (received_message != "")
                    {
                        rosalila()->graphics->drawText(label_font, displayed_message, 0, 0, true, true);
                    }
                    else
                    {
                        rosalila()->graphics->drawText(label_font, "Waiting...", 0, 0, true, true);
                    }
                    rosalila()->update();
                }
            }
            if (option_cursor == 2) //Join online match
            {
                string code = textInput("please type the match code:");
                cout << code << endl;
                rosalila()->net->send(code);

                while (true)
                {
                    string received_message = rosalila()->net->receive();
while(rosalila()->net->receive()!="");
                    if (received_message.find('|')!=std::string::npos)
                    {
                        characterSelect("online", 2);
                        break;
                    }
                    string displayed_message = "Received: " + received_message;

                    rosalila()->graphics->draw2DImage(background,
                                                      rosalila()->graphics->screen_width, rosalila()->graphics->screen_height,
                                                      0, 0,
                                                      1.0,
                                                      0.0,
                                                      false,
                                                      0, 0,
                                                      Color(0, 0, 0, 255),
                                                      0, 0,
                                                      false,
                                                      FlatShadow());

                    if (received_message != "")
                    {
                        rosalila()->graphics->drawText(label_font, displayed_message, 0, 0, true, true);
                    }
                    else
                    {
                        rosalila()->graphics->drawText(label_font, "Waiting...", 0, 0, true, true);
                    }
                    rosalila()->update();
                }
            }
            if (option_cursor == 3) //Download mods
            {
                downloadMods();
            }
            if (option_cursor == 4)
                exit(0);
        }

        rosalila()->update();
    }
    SDL_StopTextInput();
    return input;
}
