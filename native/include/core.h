#ifndef CORE_H
#define CORE_H

#include "imgui.h"
#include <string>

class Core {
private:
    static Core* instance;
    Core();

public:
    static Core* getInstance();
    ImVec2 make_uv_zero(std::string asset_name);
    ImVec2 make_uv_one(std::string asset_name);
};

#endif //CORE_H