#pragma once
#include "State.h"
#include "PlayerUI.h"
#include "PointHoverUI.h"
#include "Notification.h"
#include "TeamPopUp.h"

class MapState :
    public State
{
private:
    std::map<std::string, sf::Texture> textures;
    std::vector<Point> points;
    sf::Font font;
    PopUpWindow* popUpWindow;
    TeamPopUp* teamPopUp;
    std::string popUpKey;

    PointHoverUI* pointHoverUI;

    sf::FloatRect mapViewport;
    sf::FloatRect notifViewport;
    sf::FloatRect UIViewport;

    sf::RectangleShape background;

    Player* player;
    sf::Uint8 playerID;

    std::vector<Player*> teams;

    PlayerUI* playerUI;
    sf::View UIView;

    std::vector<Notification*> notifications;
    sf::View notifView;

    void initPoints();
    void initTextures();
    void initMap();
    void initUI();
    void checkBoundaries();
    void checkPointsClicked();
    void updateMouseInput() override;
    void updateNotifList();

    // On server broadcast
    void onBroadcastStart();
    void onBroadcastGameTime(sf::Uint32 currentGameTime);
    void onBroadcastBankrupt(sf::Uint8 shopID);
    void onBroadcastTransaction(sf::Uint8 shopID, sf::Uint8 purchasingTeamID, sf::Uint8 sellingTeamID, sf::Uint32 price);
    void onBroadcastMove(sf::Uint8 teamID, sf::Uint8 fromShopID, sf::Uint8 toShopID, sf::Uint16 duration);
    void onBroadcastPriceUpdate(sf::Int32 cap);

    // On server send
    void onTagsCollectionUpdate(ShopTag tag, double bonus, bool lose);
    void onPlayerInformation(sf::Int32 cash, sf::Int32 cap, std::vector<sf::Uint8> owenedShopsID, sf::Uint8 visitingShopID, sf::Uint8 prevVisitingShopID, bool moving, sf::Uint16 moveDuration);
    void onSell(sf::Uint8 shopID, sf::Uint8 purchasingTeamID, sf::Uint32 income, sf::Int32 cashBalance, sf::Int32 cap);
    void onRevenue(sf::Int32 amount, std::vector<sf::Int32> byShop, sf::Uint32 cashBalance);
    void onBankrupt(sf::Uint8 shopID, sf::Int32 cap);

    // void pushNotification(); //TODO


public:

    MapState(sf::RenderWindow* window, std::stack<State*>* states, MouseData* mouseData, sf::Uint8 teamID, Communicator* communicator);
    ~MapState();
    void update(const float& dt) override;
    void handleRecieves();
    void render(sf::RenderWindow* window = nullptr) override;
    void resizeView(float aspectRatio) override;


};

