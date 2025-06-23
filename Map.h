
#ifndef MAP_H
#define MAP_H


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
using namespace std;
using namespace sf;

class Map {
private:
    
    int height;
    int width;
    char** lvl;
    int cellSize;
    sf::Texture wallTex1;
    sf::Sprite wallSprite1;
    Texture platformTex;
	Sprite platformSprite;
	Texture spikesTex;
	Sprite spikesSprite;
	Texture breakWallTex;
	Sprite breakWallSprite;
	Texture FinishTex;
	Sprite FinishSprite;
	Texture bottomLessTex;
	Sprite bottomLessSprite;


public:
    // Constructor
    Map(string);

    // Destructor
    ~Map();

    // Map setup and rendering
    /*this function drawws map using diifferent charchters on the map 
    a simple wall  'w'
    a breakabale wall 'b'
	a platform 'p'
	a spikes 's'
	rings 'r'
	finish line 'f'
    a bottom less pit block 'x'
    a bonus life is 'l'
	power up is 'h'


    if you want nothing but empty space then  'g' 
    
    */
    void drawMap(sf::RenderWindow& window, float offsetX, Sprite&, Sprite&, Sprite&);
	void drawMap(sf::RenderWindow& window, Sprite&, Sprite&);

    // Getters
    char** getLevel() const;
    int getHeight() const;
    int getWidth() const;
    int getCellSize() const;
    sf::Texture& getWallTexture();
    sf::Sprite& getWallSprite();

    // Setters
    void setLevel(char** newLvl);
    void setHeight(int h);
    void setWidth(int w);
    void setCellSize(int cs);
    void setWallTexture(const sf::Texture& tex);
    void setWallSprite(const sf::Sprite& spr);
};
#endif MAP_H


