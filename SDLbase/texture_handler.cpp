#include "texture_handler.hpp"

Texture::Texture(const std::string& file, SDL_Renderer* renderer) {
    TextureHandler::getInstance()->add_texture(file, id, renderer);
    position = TextureHandler::getInstance()->get_src_position(id);
    size = TextureHandler::getInstance()->get_src_rect(id);
}

Texture::Texture(texture_t texture) {
    this->id = texture;
}

void Texture::render(SDL_Renderer* renderer, const Vector2<float>& pos, Color color, const Vector2<float>& scale, float rotation, const Vector2<float>& center, SDL_RendererFlip flip) {
    TextureHandler::getInstance()->set_src_rect(id, size);
    TextureHandler::getInstance()->set_src_position(id, this->position);
    TextureHandler::getInstance()->render(renderer, id, pos, color, scale, rotation, center, flip);
}

void Texture::set_src_position(int x, int y) {
    position = Vector2<float>(x, y);
}

void Texture::set_src_size(int x, int y) {
    size = Vector2<float>(x, y);
}


TextureHandler* TextureHandler::mInstance = nullptr;

bool TextureHandler::add_texture(const std::string& filePath, texture_t& id, SDL_Renderer* renderer) {
	id = std::hash<std::string>()(filePath);
	if (mTextures.find(id) != mTextures.end()) {
		return true;
	}
	
	SDL_Surface* sur = IMG_Load(filePath.c_str());
	LOG(sur, "load surface " + filePath);
	
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, sur);
	LOG(tex, "create texture " + filePath);
	
	mTextures[id] = tex;
    int w, h;
    SDL_QueryTexture(mTextures[id], nullptr, nullptr, &w, &h);
    mSizes.insert(std::pair<texture_t, Vector2<float> >(id, Vector2<float>(w, h)));
    mSizes.insert(std::pair<texture_t, Vector2<float> >(id, Vector2<float>(0, 0)));

	return true;
}

SDL_Texture* TextureHandler::get_texture(texture_t id) {
	if (mTextures.find(id) != mTextures.end()) {
		return mTextures[id];
	} 
	std::cerr << "Unable to load " << std::to_string(id) << std::endl;
	return nullptr;
}

void TextureHandler::render(SDL_Renderer* renderer, texture_t id, const Vector2<float>& position, Color color, const Vector2<float>& scale, float rotation, const Vector2<float>& center, SDL_RendererFlip flip) {
	if (mTextures.find(id) == mTextures.end()) {
		std::cerr << "texture " << std::to_string(id) << " doesn't exists!" << std::endl;
		return;
	}
	
	SDL_Rect src;
	src.x = (int)mPositions[id].x;
	src.y = (int)mPositions[id].y;

	src.w = (int)mSizes[id].x;
	src.h = (int)mSizes[id].y;
	
	SDL_Rect dst;
	dst.x = (int)position.x + offset.x;
	dst.y = (int)position.y + offset.y;
	dst.w = (int)(mSizes[id].x * scale.x);
	dst.h = (int)(mSizes[id].y * scale.y);
	
	SDL_Point cen;
	cen.x = (int)center.x;
	cen.y = (int)center.y;
	SDL_SetTextureColorMod(mTextures[id], color.r, color.g, color.b);
	SDL_RenderCopyEx(renderer, mTextures[id], &src, &dst, rotation, &cen, flip);
}

void TextureHandler::set_src_rect(texture_t id, const Vector2<float>& src) {
    if (mTextures.find(id) == mTextures.end()) {
        std::cerr << "texture " << std::to_string(id) << " doesn't exists!" << std::endl;
        return;
    }

    mSizes[id] = src;
}

void TextureHandler::set_src_position(texture_t id, const Vector2<float>& src) {
    if (mTextures.find(id) == mTextures.end()) {
        std::cerr << "texture " << std::to_string(id) << " doesn't exists!" << std::endl;
        return;
    }

    mPositions[id] = src;
}

void TextureHandler::apply_offset(Camera *camera) {
    if (camera == nullptr) {
        offset = Vector2<float>(0, 0);
        return;
    }

    offset = camera->get_offset();
}
	
