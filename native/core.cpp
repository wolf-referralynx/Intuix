#include "include/core.h"
#include "imgui.h"
#include "include/asset_map.h"

Core* Core::instance = nullptr;

Core::Core() {
    instance = this;
}

Core* Core::getInstance() {
    if (instance == nullptr) { instance = new Core(); }
    return instance;
}

ImVec2 Core::make_uv_zero(std::string asset_name){
    return ImVec2(asset::AssetStruct::asset_map[asset_name].first.x, asset::AssetStruct::asset_map[asset_name].first.y);
}

ImVec2 Core::make_uv_one(std::string asset_name){
    return ImVec2(asset::AssetStruct::asset_map[asset_name].second.x, asset::AssetStruct::asset_map[asset_name].second.y);
}