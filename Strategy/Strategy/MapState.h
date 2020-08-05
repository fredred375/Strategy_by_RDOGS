#pragma once
#include "State.h"
#include "PlayerUI.h"
#include "PointHoverUI.h"
class MapState :
    public State
{
private:
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, Point> points;
    sf::Font font;
    PopUpWindow* popUpWindow;
    std::string popUpKey;

    PointHoverUI* pointHoverUI;

    sf::FloatRect mapViewport;

    sf::RectangleShape background;

    Player player;

    PlayerUI* playerUI;
    sf::View UIView;
    sf::FloatRect UIViewport;

    void initPoints();
    void initTextures();
    void initMap();
    void initUI();
    void checkBoundaries();
    void checkPointsClicked();
    void updateMouseInput() override;
public:
    MapState(sf::RenderWindow* window, std::stack<State*>* states, MouseData* mouseData);
    ~MapState();
    void update(const float& dt) override;
    void render(sf::RenderWindow* window = nullptr) override;
    void resizeView(float aspectRatio) override;
};

