#pragma once

#include "asset_atlas.h"
#include "asset_atlas_cells.hpp"
#include <map>
#include <string>

using namespace asset;
namespace asset {
    struct AssetStruct {
        AssetStruct();
        static std::map<std::string, std::pair<asset::uv, asset::uv>> asset_map;
    };
}