#pragma once
#include <string>
#include <glog/logging.h>

class Object {
public:
    virtual void Draw(std::vector<std::vector<char>>* vram) {
        LOG(WARNING) << "Called abstract Object::Draw()";
    };
};

class Rect: public Object {
public:
    int x, y, width, height;

    Rect(int x, int y, int width, int height) {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
    }

    void Draw(std::vector<std::vector<char>>* vram) {
        (*vram)[y][x] = '+';
        (*vram)[y][x + width - 1] = '+';
        (*vram)[y + height - 1][x] = '+';
        (*vram)[y + height - 1][x + width - 1] = '+';
        for (int i = 1; i < width - 1; i++) {
            (*vram)[y][x + i] = '-';
            (*vram)[y + height - 1][x + i] = '-';
        }
        for (int i = 1; i < height - 1; i++) {
            (*vram)[y + i][x] = '|';
            (*vram)[y + i][x + width - 1] = '|';
        }
    }
};
