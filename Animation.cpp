//Testing

#include "Animation.h"

void Animation::updateBallAnimation(
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
) {
    if (!isBallForm || leadIsFlying) return;

    ballFrameTimer += ballFrameTime;

    if (ballFrameTimer >= ballFrameTime) {
        ballFrameTimer = 0.0f;
        ballFrameIndex = (ballFrameIndex + 1) % ballFrameCount;

        sf::IntRect frameRect(ballFrameIndex * ballFrameWidth, 0, ballFrameWidth, ballFrameHeight);

        if (velocityX >= 0) {
            spriteRightBall.setTextureRect(frameRect);
            spriteMain = spriteRightBall;
        }
        else {
            spriteLeftBall.setTextureRect(frameRect);
            spriteMain = spriteLeftBall;
        }
    }
}

void Animation::updateLeftRightAnimation(
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
) {
    if (isBallForm || leadIsFlying || velocityX == 0) return;

    leftRightFrameTimer += leftRightFrameTime;

    if (leftRightFrameTimer >= leftRightFrameTime) {
        leftRightFrameTimer = 0.0f;
        leftRightFrameIndex = (leftRightFrameIndex + 1) % leftRightFrameCount;

        sf::IntRect frameRect(leftRightFrameIndex * leftRightFrameWidth, 0, leftRightFrameWidth, leftRightFrameHeight);

        if (velocityX > 0) {
            spriteRight.setTextureRect(frameRect);
            spriteMain = spriteRight;
        }
        else {
            spriteLeft.setTextureRect(frameRect);
            spriteMain = spriteLeft;
        }
    }
}

void Animation::updateLeftRightFastAnimation(
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
) {
    if (isBallForm || !isFastRun || leadIsFlying || velocityX == 0) return;

    leftRightFastFrameTimer += leftRightFastFrameTime;

    if (leftRightFastFrameTimer >= leftRightFastFrameTime) {
        leftRightFastFrameTimer = 0.0f;
        leftRightFastFrameIndex = (leftRightFastFrameIndex + 1) % leftRightFastFrameCount;

        sf::IntRect frameRect(leftRightFastFrameIndex * leftRightFastFrameWidth, 0, leftRightFastFrameWidth, leftRightFastFrameHeight);

        if (velocityX > 0) {
            spriteRightRun.setTextureRect(frameRect);
            spriteMain = spriteRightRun;
        }
        else {
            spriteLeftRun.setTextureRect(frameRect);
            spriteMain = spriteLeftRun;
        }
    }
}
