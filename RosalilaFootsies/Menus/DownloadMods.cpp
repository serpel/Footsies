#include "DownloadMods.h"

class DownloadableMod
{
public:
  int id;
  string name;
  string summary;
  Image *image;
  DownloadableMod(int id, string name, string summary)
  {
    this->id = id;
    this->name = name;
    this->summary = summary;
    this->image = NULL;
  }
};

string downloadMods()
{
  Image *background = rosalila()->graphics->getTexture(assets_directory + "menu/white_background.png");
  string input = "";
  SDL_StartTextInput();
  string font_path = assets_directory + "misc/font.ttf";
  TTF_Font *label_font = TTF_OpenFont(font_path.c_str(), 18);
  TTF_Font *input_font = TTF_OpenFont(font_path.c_str(), 18);
  TTF_Font *selected_font = TTF_OpenFont(font_path.c_str(), 21);

  vector<DownloadableMod *> downloadable_mods;

  modio::FilterCreator filter;
  filter.setLimit(5);
  modio_instance->getMods(filter, [&](const modio::Response &response, const std::vector<modio::Mod> &mods) {
    if (response.code == 200)
    {
      for (auto &mod : mods)
      {
        DownloadableMod *downloadable_mod = new DownloadableMod(mod.id, mod.name, mod.summary);
        downloadable_mods.push_back(downloadable_mod);
        string image_path = rosalila()->utility->toString(mod.id) + ".png";
        modio_instance->downloadImage(mod.logo.thumb_320x180, image_path, [downloadable_mod, image_path](const modio::Response &response) {
          std::cout << "Download Image response: " << response.code << std::endl;

          if (response.code == 200)
          {
            downloadable_mod->image = rosalila()->graphics->getTexture(image_path);
          }
        });
      }
    }
  });

  int option_cursor = 0;

  while (true)
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

    rosalila()->graphics->drawText(label_font, "Press enter to download", 0, rosalila()->graphics->screen_height / 2 - 200, true, false);
    rosalila()->graphics->drawText(input_font, input, 0, 0, true, true);

    if (rosalila()->receiver->isKeyPressed(SDL_SCANCODE_UP))
    {
      option_cursor--;
      if (option_cursor < 0)
        option_cursor = downloadable_mods.size() + 1 - 1;
    }
    if (rosalila()->receiver->isKeyPressed(SDL_SCANCODE_DOWN))
    {
      option_cursor++;
      if (option_cursor >= (int)downloadable_mods.size() + 1)
        option_cursor = 0;
    }

    if (rosalila()->receiver->isKeyPressed(SDLK_RETURN))
    {
      if ((int)downloadable_mods.size() == option_cursor)
        break;
      modio_instance->installMod(downloadable_mods[option_cursor]->id, [&](const modio::Response &response) {
        std::cout << "Install Modfile response: " << response.code << std::endl;

        if (response.code == 200)
        {
          std::cout << "Modfile installed successfully!" << std::endl;
        }
      });
    }

    int i = 0;
    for (auto &downloadable_mod : downloadable_mods)
    {
      if (downloadable_mod->image)
      {
        rosalila()->graphics->draw2DImage(downloadable_mod->image,
                                          downloadable_mod->image->getWidth(), downloadable_mod->image->getHeight(),
                                          0, 300 + 100 * i,
                                          1.0,
                                          0.0,
                                          false,
                                          0, 0,
                                          Color(255, 255, 255, 255),
                                          0, 0,
                                          false,
                                          FlatShadow());
      }
      TTF_Font *option_font = input_font;
      if (i == option_cursor)
        option_font = selected_font;
      string text_displayed = downloadable_mod->name + ": " + downloadable_mod->summary;
      rosalila()->graphics->drawText(option_font, text_displayed, 0, 300 + 100 * i, true, false);
      i++;
    }

    TTF_Font *option_font = input_font;
    if ((int)downloadable_mods.size() == option_cursor)
      option_font = selected_font;
    rosalila()->graphics->drawText(option_font, "Exit", 0, 300 + 100 * (i + 1), true, false);

    rosalila()->update();

    modio_instance->process();
  }
  SDL_StopTextInput();
  return input;
}
