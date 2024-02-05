#pragma once
#include <yaml-cpp/yaml.h>
#include <raylib.h>
#include <vector>

#include "../engine/object.hpp"

namespace Graphics {
    class Window {
    public:
        int width;
        int height;
        bool debug;
        int vramWidth;
        int vramHeight;
        std::vector<std::vector<char>> vram;
        std::vector<Object*> objects;
        Font font;

        Window(YAML::Node config);
        ~Window();
        void update();
    
    private:
        void DrawInstruments();
        void DrawSlide();
        void ClearVRAM();
    };
}
