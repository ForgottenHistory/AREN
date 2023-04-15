#pragma once
#include "glmpch.h"
#include "math/AVec3.h"

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

    AVec3 GetColor(COLORS color)
    {
        switch (color)
        {
        case RED:
            return AVec3(1.0f, 0.0f, 0.0f);
        case GREEN:
            return AVec3(0.0f, 1.0f, 0.0f);
        case BLUE:
            return AVec3(0.0f, 0.0f, 1.0f);
        case YELLOW:
            return AVec3(1.0f, 1.0f, 0.0f);
        case WHITE:
            return AVec3(1.0f, 1.0f, 1.0f);
        case BLACK:
            return AVec3(0.0f, 0.0f, 0.0f);
        case PURPLE:
            return AVec3(0.5f, 0.0f, 0.5f);
        case ORANGE:
            return AVec3(1.0f, 0.5f, 0.0f);
        case BROWN:
            return AVec3(0.5f, 0.25f, 0.0f);
        case PINK:
            return AVec3(1.0f, 0.75f, 0.8f);
        case GRAY:
            return AVec3(0.5f, 0.5f, 0.5f);
        default:
            return AVec3(0.0f, 0.0f, 0.0f);
        }
    }

private:
    ColorManager() {} // private constructor to prevent instantiation
};
