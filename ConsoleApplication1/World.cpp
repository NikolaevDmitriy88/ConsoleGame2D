#include "NPC.h"

char World::location_end[HIGHT_MAP][WIDTH_MAP]{};
char World::location_cave[HIGHT_MAP][WIDTH_MAP]{};
char World::location_field[HIGHT_MAP][WIDTH_MAP]{};
char World::location_forest[HIGHT_MAP][WIDTH_MAP]{};
char World::location_viladge[HIGHT_MAP][WIDTH_MAP]{};
char World::location_viladge_tavern[HIGHT_MAP][WIDTH_MAP]{};
char World::location[HIGHT_MAP][WIDTH_MAP]{};

void World::loadLevels()
{
	level = Levels::Empty;
	FILE* fp;
	const char* levels[COUNT_OF_LEVELS] = { "Viladge", "Cave", "Field", "Forest", "Viladge_tavern", "End"};

	for (int lvl = 0; lvl < COUNT_OF_LEVELS; ++lvl) 
	{
		if ((fp = fopen(levels[lvl], "r")) == NULL) 
		{
			puts("Cannot open file.\n");
			exit(1);
		}
		for (int y = 0; y < HIGHT_MAP; ++y) 
		{
			for (int x = 0; x < WIDTH_MAP; ++x) 
			{
				if (!lvl) location_viladge[y][x] = fgetc(fp);
				else if (lvl == 1) location_cave[y][x] = fgetc(fp);
				else if (lvl == 2) location_field[y][x] = fgetc(fp);
				else if (lvl == 3) location_forest[y][x] = fgetc(fp);
				else if (lvl == 4) location_viladge_tavern[y][x] = fgetc(fp);
				else location_end[y][x] = fgetc(fp);
			}
		}
		fclose(fp);
	}
	location_viladge[23][18] = HEAD;
	location_viladge[23][5] = HEAD;
}

void World::createLevel(const Player& player) 
{
	if (player.checkLevel() == Levels::VILADGE) 
	{
		for (int i = 0; i < HIGHT_MAP; ++i)
			for (int j = 0; j < WIDTH_MAP; ++j)
				location[i][j] = location_viladge[i][j];
		level = Levels::VILADGE;
	}
	else if (player.checkLevel() == Levels::CAVE) 
	{
		for (int i = 0; i < HIGHT_MAP; ++i)
			for (int j = 0; j < WIDTH_MAP; ++j)
				location[i][j] = location_cave[i][j];
		level = Levels::CAVE;
	}
	else if (player.checkLevel() == Levels::VILADGE_TAVERN) 
	{
		for (int i = 0; i < HIGHT_MAP; ++i)
			for (int j = 0; j < WIDTH_MAP; ++j)
				location[i][j] = location_viladge_tavern[i][j];
		level = Levels::VILADGE_TAVERN;
	}
	else if (player.checkLevel() == Levels::FIELD) 
	{
		for (int i = 0; i < HIGHT_MAP; ++i)
			for (int j = 0; j < WIDTH_MAP; ++j)
				location[i][j] = location_field[i][j];
		level = Levels::FIELD;
	}
	else if (player.checkLevel() == Levels::FOREST) 
	{
		for (int i = 0; i < HIGHT_MAP; ++i)
			for (int j = 0; j < WIDTH_MAP; ++j)
				location[i][j] = location_forest[i][j];
		level = Levels::FOREST;
	}
	else if (player.checkLevel() == Levels::END)
	{
		for (int i = 0; i < HIGHT_MAP; ++i)
			for (int j = 0; j < WIDTH_MAP; ++j)
				location[i][j] = location_end[i][j];
		level = Levels::END;
	}
	else level = Levels::Empty;
}

void World::hidePartOfMap(const Player& pl)
{
	int start_for_x, end_for_x;
		if (pl.getPosX() < 98)
		{
			start_for_x = 97;
			end_for_x = WIDTH_MAP;
		}
		else 
		{
			start_for_x = 0;
			end_for_x = 96;
		}
		for (int y = 0; y < HIGHT_MAP; ++y)
			for (int x = start_for_x; x < end_for_x; ++x)
				location[y][x] = ' ';
	/*if (level == Levels::CAVE)
	{
	}
	if (level == Levels::FOREST)
	{
		if (pl.getPosX() > 87)
		{
			start_for_x = 127;
			end_for_x = WIDTH_MAP;
		
			for (int y = 0; y < 8; ++y)
				for (int x = start_for_x; x < end_for_x; ++x)
					location[y][x] = location_forest[y][x];
		}
	}*/
}

void World::addChanges(const Player& player) 
{
	if (level == Levels::CAVE) hidePartOfMap(player);

	int max_hp = player.getMaxHp();
	int posX = player.getPosX();
	int HP = player.getHP();
	int AP = player.getAP();

	if (posX + 4 >= WIDTH_MAP) posX = WIDTH_MAP - 4;
	location[17][posX - 2] = -43; location[17][posX - 1] = '-'; location[17][posX] = '-';
	location[17][posX + 1] = '-'; location[17][posX + 2] = '-'; location[17][posX + 3] = -65;
	if (HP >= max_hp) {
		location[18][posX - 2] = '|'; location[18][posX - 1] = -37; location[18][posX] = -37;
		location[18][posX + 1] = -37; location[18][posX + 2] = -37; location[18][posX + 3] = '|';
	}
	else if (HP > 86 && HP < max_hp) {
		location[18][posX - 2] = '|'; location[18][posX - 1] = -37; location[18][posX] = -37;
		location[18][posX + 1] = -37; location[18][posX + 2] = -35; location[18][posX + 3] = '|';
	}
	else if (HP > 74 && HP < 87) {
		location[18][posX - 2] = '|'; location[18][posX - 1] = -37; location[18][posX] = -37;
		location[18][posX + 1] = -37; location[18][posX + 2] = ' '; location[18][posX + 3] = '|';
	}
	else if (HP > 61 && HP < 75) {
		location[18][posX - 2] = '|'; location[18][posX - 1] = -37; location[18][posX] = -37;
		location[18][posX + 1] = -35; location[18][posX + 2] = ' '; location[18][posX + 3] = '|';
	}
	else if (HP > 49 && HP < 62) {
		location[18][posX - 2] = '|'; location[18][posX - 1] = -37; location[18][posX] = -37;
		location[18][posX + 1] = ' '; location[18][posX + 2] = ' '; location[18][posX + 3] = '|';
	}
	else if (HP > 36 && HP < 50) {
		location[18][posX - 2] = '|'; location[18][posX - 1] = -37; location[18][posX] = -35;
		location[18][posX + 1] = ' '; location[18][posX + 2] = ' '; location[18][posX + 3] = '|';
	}
	else if (HP > 24 && HP < 37) {
		location[18][posX - 2] = '|'; location[18][posX - 1] = -37; location[18][posX] = ' ';
		location[18][posX + 1] = ' '; location[18][posX + 2] = ' '; location[18][posX + 3] = '|';
	}
	else if (HP > 11 && HP < 25) {
		location[18][posX - 2] = '|'; location[18][posX - 1] = -35; location[18][posX] = ' ';
		location[18][posX + 1] = ' '; location[18][posX + 2] = ' '; location[18][posX + 3] = '|';
	}
	else if (HP > 0 && HP < 12) {
		location[18][posX - 2] = '|'; location[18][posX - 1] = '['; location[18][posX] = ' ';
		location[18][posX + 1] = ' '; location[18][posX + 2] = ' '; location[18][posX + 3] = '|';
	}
	else {
		location[18][posX - 2] = '|'; location[18][posX - 1] = 'D'; location[18][posX] = 'E';
		location[18][posX + 1] = 'A'; location[18][posX + 2] = 'D'; location[18][posX + 3] = '|';
	}

	if (AP > 5) {
		location[19][posX - 2] = '|'; location[19][posX - 1] = -80; location[19][posX] = -80;
	}
	else if (0 < AP && AP < 6) {
		location[19][posX - 2] = '|'; location[19][posX - 1] = -80; location[19][posX] = ' ';
	}
	else {
		location[19][posX - 2] = '|'; location[19][posX - 1] = ' '; location[19][posX] = ' ';
	}

	if (player.crossbowInHand() && player.readyForShoote()) {
		location[19][posX + 1] = 24;
	}
	else if (player.swordInHand() && player.readyForSkill()) {
		location[19][posX + 1] = 'N';
	}
	else location[19][posX + 1] = ' ';

	if ((player.checkTransfer() == Transfer_to::VILADGE_TAVERN)   // Signal! Can make some operation
		|| (player.checkTransfer() == Transfer_to::FIELD)
		|| (player.checkTransfer() == Transfer_to::BORDER_VILADGE)
		|| (player.checkTransfer() == Transfer_to::FOREST)
		|| (player.checkTransfer() == Transfer_to::CAVE)
		|| player.getSignal())
		location[19][posX + 2] = 'R';
	else location[19][posX + 2] = ' ';

	location[19][posX + 3] = '|';
	location[20][posX + 1] = '-'; location[20][posX + 2] = '-'; location[20][posX + 3] = -39;
	location[20][posX - 2] = '|'; location[20][posX - 1] = '/'; location[20][posX] = '-';
}