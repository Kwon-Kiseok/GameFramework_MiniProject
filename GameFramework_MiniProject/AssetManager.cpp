#include "AssetManager.h"
#include "Components.h"

AssetManager::AssetManager(Manager* man) : manager(man)
{

}

AssetManager::~AssetManager()
{

}

//텍스쳐 경로 id로 등록
void AssetManager::AddTexture(std::string id, const char* path)
{
	textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string id)
{
	return textures[id];
}

//폰트 경로 id로 등록
void AssetManager::AddFont(std::string id, std::string path, int fontsize)
{
	fonts.emplace(id, TTF_OpenFont(path.c_str(), fontsize));
}

TTF_Font* AssetManager::GetFont(std::string id)
{
	return fonts[id];
}