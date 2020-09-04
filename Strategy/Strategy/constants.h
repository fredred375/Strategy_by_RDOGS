#pragma once
namespace constants
{
	const int PLAYER_ID = 1;

	const float FRAMERATE_LOW = 20.f;

	const unsigned int WINDOW_WIDTH_SMALL = 800;
	const unsigned int WINDOW_HEIGHT_SMALL = 600;

	const unsigned int WINDOW_WIDTH_BIG = 1920;
	const unsigned int WINDOW_HEIGHT_BIG = 1080;

	const float PLAYER_UI_PORTION = 0.25f;
	const float MAP_PORTION = 1.f - PLAYER_UI_PORTION;

	const float ZOOM_IN_SPEED = 0.95f;
	const float ZOOM_OUT_SPEED = 1.05f;

	const float MAPVIEW_WIDTH = 1440.f;
	const float MAPVIEW_HEIGHT = 1080.f;

	const float UIVIEW_WIDTH = 480.f;
	const float UIVIEW_HEIGHT = 1000.f;

	const float INFO_BOX_WIDTH = 380.f;
	const float INFO_BOX_HEIGHT = 45.f;



}
enum class ShopTag
{
	WENZHOU = 0,

	SHIDA = 1,

	YIYIBA = 2,

	GONGGUAN = 3,

	FASTFOOD = 4,

	STARBUCKS = 5,

	CURRY = 6,

	RAMEN = 7,

	HOTPOT = 8,

	ICE = 9,

	CHAMONIX = 10,

	MALA = 11,

	numShopTags
};