
#pragma once
#include <SFML/Graphics.hpp>

class Animation {
public:
    static void updateBallAnimation(
        sf::Sprite& spriteRightBall,
        sf::Sprite& spriteLeftBall,
        sf::Sprite& spriteMain,
        float velocityX,
        bool isBallForm,
        bool leadIsFlying,
        int& ballFrameIndex,
        float& ballFrameTimer,
        const float ballFrameTime,
        const int ballFrameCount,
        const int ballFrameWidth,
        const int ballFrameHeight
    );

    static void updateLeftRightAnimation(
        sf::Sprite& spriteRight,
        sf::Sprite& spriteLeft,
        sf::Sprite& spriteMain,
        float velocityX,
        bool isBallForm,
        bool leadIsFlying,
        int& leftRightFrameIndex,
        float& leftRightFrameTimer,
        const float leftRightFrameTime,
        const int leftRightFrameCount,
        const int leftRightFrameWidth,
        const int leftRightFrameHeight
    );

    static void updateLeftRightFastAnimation(
        sf::Sprite& spriteRightRun,
        sf::Sprite& spriteLeftRun,
        sf::Sprite& spriteMain,
        float velocityX,
        bool isBallForm,
        bool isFastRun,
        bool leadIsFlying,
        int& leftRightFastFrameIndex,
        float& leftRightFastFrameTimer,
        const float leftRightFastFrameTime,
        const int leftRightFastFrameCount,
        const int leftRightFastFrameWidth,
        const int leftRightFastFrameHeight
    );
};
