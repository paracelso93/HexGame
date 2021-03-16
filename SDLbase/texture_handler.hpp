#ifndef ROGUELIKE_TEXTURE_HANDLER_H
#define ROGUELIKE_TEXTURE_HANDLER_H

#include <unordered_map>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "vectors.hpp"
#include "color.hpp"
#include "helper.hpp"
#include "../camera.hpp"

#define texture_t unsigned int

struct Texture {
    texture_t id;
    Vector2<float> position;
    Vector2<float> size;

    Texture(const std::string& file, SDL_Renderer* renderer);
    explicit Texture(texture_t texture);
    void render(SDL_Renderer* renderer, const Vector2<float>& pos, Color color = Color(255, 255, 255), const Vector2<float>& scale = Vector2<float>(1.0f, 1.0f), float rotation = 0, const Vector2<float>& center = Vector2<float>(), SDL_RendererFlip flip = SDL_FLIP_NONE);
    void set_src_size(int x, int y);
    void set_src_position(int x, int y);

    Texture(const Texture& other) {
        this->id = other.id;
        this->position = other.position;
        this->size = other.size;
    }
};


class TextureHandler {
	public:
		static TextureHandler* getInstance() {
			if (mInstance == nullptr) {
				mInstance = new TextureHandler();
				return mInstance;
			}
			return mInstance;
		}
		bool add_texture(const std::string& filePath, texture_t& id, SDL_Renderer* renderer);
		SDL_Texture* get_texture(texture_t id);
		void render(SDL_Renderer* renderer, texture_t id, const Vector2<float>& position, Color color = Color(255, 255, 255), const Vector2<float>& scale = Vector2<float>(1.0f, 1.0f), float rotation = 0, const Vector2<float>& center = Vector2<float>(), SDL_RendererFlip flip = SDL_FLIP_NONE);
		void set_src_rect(texture_t id, const Vector2<float>& src);
		void set_src_position(texture_t id, const Vector2<float>& src);
		Vector2<float> get_src_rect(texture_t id) { return mSizes[id]; }
		Vector2<float> get_src_position(texture_t id) { return mPositions[id]; }
		void apply_offset(Camera* camera);
	private:
		static TextureHandler* mInstance;
		Vector2<float> offset;
		std::unordered_map<texture_t, Vector2<float> > mSizes;
		std::unordered_map<texture_t, Vector2<float> > mPositions;
		std::unordered_map<texture_t, SDL_Texture*> mTextures;
};

#endif