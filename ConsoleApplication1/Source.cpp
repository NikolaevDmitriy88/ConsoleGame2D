#include "NPC.h"
void hideCursor();
void setCurPos(int y, int x);
void showScreen(World*, NPC*);
//=============================================================================
void wakeUp(World& game_world, int y, int x);

int main()
{
	hideCursor();
	srand(static_cast<unsigned int>(time(NULL)));

	World game_world;
	game_world.loadLevels();

	Player player(23, 10, 100, Levels::FIELD);
	Knight oldman(23, 40, 150, Levels::FOREST);
	Knight guard1(23, 80, 200, Levels::FOREST);
	Knight guard2(23, 120, 200, Levels::FOREST);
	
	std::array<Knight*, 3> enemyList{ &oldman, &guard1, &guard2 };	
	FlyingMonster bird(5, 30);
	Spider spider(11, 50);

	do {		
		game_world.createLevel(player);
		game_world.addChanges(player);
		player.putOnMap(&game_world, enemyList, bird);
		if (player.getPosX() < 98)
		{
			bird.putOnMap(game_world);
			spider.putOnMap(game_world);
		}
		for (const auto enemy : enemyList)
			enemy->putOnMap(&game_world, &player);
		
		Sleep(150);
		showScreen(&game_world, &player);
		
		player.movePlayer(&game_world, enemyList);
		bird.moveII(player);
		for (const auto enemy : enemyList)
			enemy->moveII(&game_world, &player);

		if (player.isWakeUp()) break;

	} while (GetKeyState(VK_ESCAPE) >= 0);

	if (player.checkIsDead() && player.isWakeUp())
	{
		player.setLevel(Levels::END);
		game_world.createLevel(player);

		wakeUp(game_world, 16, 26);
	}

	return 0;
}
void changeChar(World& game_world, int y, int x)
{
	setCurPos(y, x);
	_putch(game_world.getPieceOfLocation(y, x));
	Sleep(1);
}
void wakeUp(World& game_world, int y, int x)
{
	game_world.setCharInLocation(15, 108, 1);
	int next_y = y;
	int next_x = x;
	int max_step = x;
	setCurPos(next_y, next_x);
	changeChar(game_world, next_y, next_x);

	for (int cnt = 1; cnt <= max_step; ++cnt)
	{
		if (cnt < max_step)
		{
			++next_x;
			changeChar(game_world, next_y, next_x);
		}

		while (next_y < y + cnt && next_y < HIGHT_WINDOW)
		{
			++next_y;
			changeChar(game_world, next_y, next_x);
		}
		while (next_x > x - cnt && next_x > 0)
		{
			--next_x;
			changeChar(game_world, next_y, next_x);
		}
		while (next_y > y - cnt && next_y > 0)
		{
			--next_y;
			changeChar(game_world, next_y, next_x);
		}
		while (next_x < x + cnt && next_x < WIDTH_WINDOW)
		{
			++next_x;
			changeChar(game_world, next_y, next_x);
		}
		while (next_y < y)
		{
			++next_y;
			changeChar(game_world, next_y, next_x);
		}
	}
	setCurPos(0, 0);
	char ch = 'A';
	for (int y = 0; y < HIGHT_WINDOW; ++y)
		for (int x = WIDTH_WINDOW; x < WIDTH_MAP; ++x)
			_putch(game_world.getPieceOfLocation(y, x));
	Sleep(6000);
	setCurPos(0, 0);

	game_world.setCharInLocation(12, 33, ' ');
	game_world.setCharInLocation(12, 34, ' ');
	game_world.setCharInLocation(12, 35, ' ');

	game_world.setCharInLocation(13, 25, 'T');
	game_world.setCharInLocation(13, 26, 'H');
	game_world.setCharInLocation(13, 27, 'E');
	game_world.setCharInLocation(13, 28, ' ');
	game_world.setCharInLocation(13, 29, 'E');
	game_world.setCharInLocation(13, 30, 'N');
	game_world.setCharInLocation(13, 31, 'D');
	game_world.setCharInLocation(13, 32, ' ');

	game_world.setCharInLocation(14, 27, ' ');
	game_world.setCharInLocation(14, 28, ' ');
	game_world.setCharInLocation(14, 29, ' ');

	for (int y = 0; y < HIGHT_WINDOW; ++y)
		for (int x = 0; x < WIDTH_WINDOW; ++x)
			_putch(game_world.getPieceOfLocation(y, x));
	do
	{
		ch = _getch();
	} while (GetKeyState(VK_ESCAPE) >= 0);
}