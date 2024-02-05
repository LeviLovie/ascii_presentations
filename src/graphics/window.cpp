#include "window.hpp"
#include <yaml-cpp/yaml.h>
#include <raylib.h>
#include <glog/logging.h>

#include "../engine/object.hpp"

#define INSTRUMETS_TOP_HEIGHT 150
#define INSTRUMENTS_LEFT_WIDTH 300

namespace Graphics {
    Window::Window(YAML::Node config) {
        if (!config["window"]["width"]) {
            LOG(WARNING) << "Unable to find \"window\":\"width\" prop in the config; using default value";
            width = 1280;
        } else
            width = config["window"]["width"].as<int>();

        if (!config["window"]["height"]) {
            LOG(WARNING) << "Unable to find \"window\":\"height\" prop in the config; using default value";
            height = 720;
        } else
            height = config["window"]["height"].as<int>();

        InitWindow(width, height, "ASCII_Presentations");
        SetTargetFPS(60);
        SetWindowState(FLAG_WINDOW_RESIZABLE);

        vramWidth = 80;
        vramHeight = 45;
        ClearVRAM();

        font = LoadFontEx("data/RobotoMono-Regular.ttf", 32, 0, 250);

        objects.push_back(new Rect(2, 2, 4, 4));
    }

    Window::~Window() {
        CloseWindow();
    }

    void Window::update() {
        if (WindowShouldClose())
            CloseWindow();
        if (IsWindowResized()) {
            width = GetScreenWidth();
            height = GetScreenHeight();
        }
        BeginDrawing();
        if (debug)
            DrawFPS(1, 0);
        ClearBackground(RAYWHITE);

        DrawInstruments();
        DrawSlide();
        
        EndDrawing();
    }

    void Window::DrawInstruments() {
        DrawRectangle(0, 0, width, INSTRUMETS_TOP_HEIGHT, GRAY);
        DrawRectangle(0, INSTRUMETS_TOP_HEIGHT, INSTRUMENTS_LEFT_WIDTH, height, GRAY);
    }

    void Window::DrawSlide() {
        float aspectRatio = 16.0f / 9.0f;
        float slideWidth = width - INSTRUMENTS_LEFT_WIDTH;
        float slideHeight = height - INSTRUMETS_TOP_HEIGHT;
        float slideX = INSTRUMENTS_LEFT_WIDTH;
        float slideY = INSTRUMETS_TOP_HEIGHT;
        if (slideWidth / slideHeight > aspectRatio) {
            slideWidth = slideHeight * aspectRatio;
            slideX = INSTRUMENTS_LEFT_WIDTH + (width - INSTRUMENTS_LEFT_WIDTH - slideWidth) / 2;
        } else {
            slideHeight = slideWidth / aspectRatio;
            slideY = INSTRUMETS_TOP_HEIGHT + (height - INSTRUMETS_TOP_HEIGHT - slideHeight) / 2;
        }
        DrawRectangleLines(slideX, slideY, slideWidth, slideHeight, BLACK);

        ClearVRAM();
        for (auto object : objects) {
            object->Draw(&vram);
        }

        for (int i = 0; i < vramHeight; i++) {
            std::string line = "";
            for (int j = 0; j < vramWidth; j++) {
                line += vram[i][j];
            }
            DrawTextEx(font, line.c_str(), Vector2{slideX, slideY + i * 20}, 20, 0, BLACK);
        }
    }

    void Window::ClearVRAM() {
        vram.clear();
        for (int i = 0; i < vramHeight; i++) {
            std::vector<char> line;
            for (int j = 0; j < vramWidth; j++) {
                line.push_back(' ');
            }
            vram.push_back(line);
        }
    }
}
