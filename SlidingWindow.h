

#ifndef SLIDINGWINDOW_H
#define SLIDINGWINDOW_H

#include <SFML/Graphics.hpp>


class SlidingWindow{
private:
    float offsetX;
    float screenWidth;
    float scrollSpeed;
    float leftMargin;
    float rightMargin;

public:
    // Constructor
    SlidingWindow(float screenWidth, float scrollSpeed);

    // Update the camera based on player's X position
    void update(float playerX, float, float);

    // Get the current X offset
    float getOffset() const;

    // Reset the offset to the start
    void reset();
};
#endif SLIDINGWINDOW_H

