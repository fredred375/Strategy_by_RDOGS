#pragma once
#include "State.h"
class MapState :
    public State
{
private:

    // DEBUG ============

    sf::Uint8 teamID = 7;

    // ==================


    std::map<std::string, sf::Texture> textures;
    std::map<std::string, Point> points;
    sf::Font font;

    bool popUpWindowActivated;
    std::string popUpKey;

    sf::RectangleShape background;

    void initPoints();
    void initTextures();
    void initMap();
    //void logIn();

    void checkBoundaries();
    void checkPointsClicked();
    void updateMouseInput() override;
public:
    MapState(sf::RenderWindow* window, std::stack<State*>* states, MouseData* mouseData, Communicator* communicator);
    ~MapState();
    void update() override;
    void render(sf::RenderWindow* window = nullptr) override;
};

