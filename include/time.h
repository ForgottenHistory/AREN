#pragma once

class Time {
public:
    static float time;
    static float deltaTime;
    static float sinTime;
    static float cosTime;
    static float tanTime;
    static float elapsedTime;

    static void UpdateTime();
    static void PrintTime();

private:
    static float currentTime;
    static float lastTime;
};