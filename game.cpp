//
// Created by edoardo biasio on 2021-03-01.
//

#include "game.hpp"
#include "parsers/unit_parser.hpp"

#define TARGET_FPS 120

Game::Game(int window_width, int window_height, int map_width, int map_height) : mWindow(nullptr), mRenderer(nullptr), mDone(false), mMousePosition(window_width / 2, window_height / 2) {
    srand(time(nullptr));
    mMouse = 0;
    mDeltaTime = 0.017f;
    mWindowWidth = window_width;
    mWindowHeight = window_height;
    init_sdl(window_width, window_height);
    mMap = std::make_unique<HexMap>(map_width, map_height, mRenderer);
    mCamera = std::make_unique<Camera>();

    startTime = SDL_GetTicks();

    UnitParser::init();
    auto entities = UnitParser::parse<Hex, Movable, Renderable, Selectable>("data/simple_unit.txt", this);
    AStar::set_game(this);
    for (int i = 0; i < 10; i++) {
        std::string val = "tank";
        if (i == 5) val = "model";
        if (i > 5) {
            val = "infantry";
        }
        Entity* e = UnitParser::create_entity_from_unit<Hex, Movable, Renderable, Selectable>(UnitParser::get_unit_with_id(val));
        e->get_component<Hex>()->move(0, i, e->get_component<Renderable>()->get_transform());
        mEntities.push_back(e);
    }

    int rand_x = rand() % map_width;
    int rand_y = rand() % map_height;
    Tile* tile = mMap->get_tile_at_index(rand_x, rand_y);
    tile->blocks = true;
    tile->set_new_tile_texture("assets/mountain.png", mRenderer);

    info = new Info();
    info->bg_panel = new GUI_Panel(1720, 880, 200, 200, BLUE);
    info->position_info = new GUI_Text(GUI_Fonts::get_instance()->get_font_with_size(24), "position: (,)", YELLOW, 1750, 920);
    old_position = Vector2<int>(0, 0);
}

Game::~Game() {
    clean();
}

void Game::init_sdl(int window_width, int window_height) {
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    TTF_Init();
    mWindow = SDL_CreateWindow("HexMap", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_INPUT_GRABBED);
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void Game::handle_input() {
    SDL_Event event;

    mMouse = 0;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            mDone = true;
        }
        float dx = 0, dy = 0;

        const Uint8* state = SDL_GetKeyboardState(nullptr);
        if (state[SDL_SCANCODE_UP]) {
            dy += 10;
        }
        if (state[SDL_SCANCODE_DOWN]) {
            dy -= 10;
        }
        if (state[SDL_SCANCODE_LEFT]) {
            dx -= 10;
        }
        if (state[SDL_SCANCODE_RIGHT]) {
            dx += 10;
        }
        if (state[SDL_SCANCODE_ESCAPE]) {
            mDone = true;
        }

        if (mMousePosition.x < 10) dx -= 10;
        if (mMousePosition.x > mWindowWidth - 10) dx += 10;
        if (mMousePosition.y < 10) dy += 10;
        if (mMousePosition.y > mWindowHeight - 10) dy -= 10;

        mCamera->move(dx, dy);

        if (event.type == SDL_MOUSEBUTTONDOWN) {

            switch (event.button.button) {
                case SDL_BUTTON_LEFT:
                    mMouse |= LEFT_BUTTON_DOWN;
                    break;
                case SDL_BUTTON_RIGHT:
                    mMouse |= RIGHT_BUTTON_DOWN;
                    break;
                case SDL_BUTTON_MIDDLE:
                    mMouse |= MIDDLE_BUTTON_DOWN;
                    break;
            }
        }
        if (event.type == SDL_MOUSEBUTTONUP) {

            switch (event.button.button) {
                case SDL_BUTTON_LEFT:
                    mMouse |= LEFT_BUTTON_UP;
                    break;
                case SDL_BUTTON_RIGHT:
                    mMouse |= RIGHT_BUTTON_UP;
                    break;
                case SDL_BUTTON_MIDDLE:
                    mMouse |= MIDDLE_BUTTON_UP;
                    break;
            }
        }
    }
}

void Game::update() {
    Uint32 delta = SDL_GetTicks() - startTime;
    startTime = SDL_GetTicks();
    if (delta >= TARGET_FPS) {
        SDL_Delay(delta - TARGET_FPS);
        delta = TARGET_FPS;
    }

    mDeltaTime = delta / 1000.0f;

    info->position_info->set_text("position: " + mMap->get_selector()->position.to_string());

    if (!(old_position == mMap->get_selector()->position)) {
        mEntities[0]->get_component<Hex>()->move(mMap->get_selector()->position.x - old_position.x, mMap->get_selector()->position.y - old_position.y,
                                                 mEntities[0]->get_component<Renderable>()->get_transform());
        for (int x = 0; x < mMap->get_size().x; x++) {
            for (int y = 0; y < mMap->get_size().y; y++) {
                Tile *tile = mMap->get_tile_at_index(x, y);
                if (tile == nullptr) continue;
                tile->set_new_tile_texture("assets/grass.png", mRenderer);
                if (mEntities[0]->get_component<Movable>()->can_move(x, y)) {

                    tile->set_new_tile_texture("assets/base.png", mRenderer);
                }
            }
        }
        old_position = mMap->get_selector()->position;
    }

    SDL_GetMouseState(&mMousePosition.x, &mMousePosition.y);
    mMap->update(mDeltaTime, mMousePosition, mMouse & LEFT_BUTTON_DOWN, mCamera.get());
    mCamera->update(mDeltaTime);

    for (Entity* entity : mEntities) {
        entity->update(mDeltaTime);
    }
    //button->update(mMousePosition, mMouse);
}

void Game::render() {
    SDL_SetRenderDrawColor(mRenderer, 8, 156, 32, 255);
    SDL_RenderClear(mRenderer);
    TextureHandler::getInstance()->apply_offset(mCamera.get());
    mMap->render(mRenderer);

    for (Entity* entity : mEntities) {
        if (entity->has_component<Renderable>()) {
            entity->get_component<Renderable>()->render(mRenderer);
        }
    }
    TextureHandler::getInstance()->apply_offset(nullptr);
    info->bg_panel->render(mRenderer);
    info->position_info->render(mRenderer);

    SDL_RenderPresent(mRenderer);
}

void Game::tick() {
    handle_input();
    update();
    render();
}

void Game::clean() {
    mMap->clean();
    mMap.reset(nullptr);
}

Entity* Game::get_entity_at_position(int x, int y) {
    for (auto entity : mEntities) {
        if (entity->has_component<Hex>()) {
            auto hex = entity->get_component<Hex>();
            if (hex->get_position().x == x && hex->get_position().y == y) {
                return entity;
            }
        }
    }
    return nullptr;
}