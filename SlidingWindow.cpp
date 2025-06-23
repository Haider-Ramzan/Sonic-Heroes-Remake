

#include "SlidingWindow.h"



SlidingWindow::SlidingWindow(float screenWidth, float scrollSpeed)
    : screenWidth(screenWidth), scrollSpeed(scrollSpeed), offsetX(0.0f) {
    leftMargin = screenWidth * 0.25f;
    rightMargin = screenWidth * 0.6f;
}

void SlidingWindow::update(float playerX, float playerVelocity, float terminalVelocity) {
    
    float dynamicScrollSpeed = playerVelocity>=0 ? playerVelocity: playerVelocity*-1; // making the speed positive only

    if (dynamicScrollSpeed == 0) return; // so no screen scrolling when speed is zere

    if (dynamicScrollSpeed > terminalVelocity) dynamicScrollSpeed = terminalVelocity;

    if (playerX < offsetX + leftMargin) {
        offsetX -= dynamicScrollSpeed;
        if (playerX < offsetX) offsetX = playerX;
    }

    else if (playerX > offsetX + rightMargin) {
        offsetX += dynamicScrollSpeed;
        if (playerX > offsetX + screenWidth) offsetX = playerX - screenWidth;
    }

}

float SlidingWindow::getOffset() const {
    return offsetX;
}

void SlidingWindow::reset() {
    offsetX = 0.0f;
}
