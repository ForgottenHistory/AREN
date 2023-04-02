#pragma once
#include "glmpch.h"

class ColorManager
{
public:
    enum COLORS
    {
        RED,
        GREEN,
        BLUE,
        YELLOW,
        WHITE,
        BLACK,
        PURPLE,
        ORANGE,
        BROWN,
        PINK,
        GRAY,
        NUM_COLORS
    };

    static ColorManager &GetInstance()
    {
        static ColorManager instance; // create the singleton instance
        return instance;
    }

    glm::vec3 GetColor(COLORS color)
    {
        switch (color)
        {
        case RED:
            return glm::vec3(1.0f, 0.0f, 0.0f);
        case GREEN:
            return glm::vec3(0.0f, 1.0f, 0.0f);
        case BLUE:
            return glm::vec3(0.0f, 0.0f, 1.0f);
        case YELLOW:
            return glm::vec3(1.0f, 1.0f, 0.0f);
        case WHITE:
            return glm::vec3(1.0f, 1.0f, 1.0f);
        case BLACK:
            return glm::vec3(0.0f, 0.0f, 0.0f);
        case PURPLE:
            return glm::vec3(0.5f, 0.0f, 0.5f);
        case ORANGE:
            return glm::vec3(1.0f, 0.5f, 0.0f);
        case BROWN:
            return glm::vec3(0.5f, 0.25f, 0.0f);
        case PINK:
            return glm::vec3(1.0f, 0.75f, 0.8f);
        case GRAY:
            return glm::vec3(0.5f, 0.5f, 0.5f);
        default:
            return glm::vec3(0.0f, 0.0f, 0.0f);
        }
    }

private:
    ColorManager() {} // private constructor to prevent instantiation
};
