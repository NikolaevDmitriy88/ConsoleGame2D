#include "NPC.h"
//=============================================================================
void hideCursor() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = false;
	SetConsoleCursorInfo(consoleHandle, &info);
}
void setCurPos(int y, int x) {
	COORD coord;
	coord.Y = y;
	coord.X = x;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
//=============================================================================
void Player::putOnMap(World* lvl, std::array<Knight*, 3>& eList, FlyingMonster& flym) {
	if (m_onTheGround)
	{
		if (m_stage_up_dawn)
		{
			animationUpDown(lvl);
			m_stage_up_dawn = false;
		}
		else
		{
			if (isRightDirection && isStandUp && !isBlocking && !isDead) {
				animationWalk(lvl);
				animationBody(lvl);
			}
			else if (isRightDirection && isDead) {
				lvl->setCharInLocation(posY + 1, posX - 2, HEAD);		//
				lvl->setCharInLocation(posY + 1, posX - 1, 127);		//    o#_
				lvl->setCharInLocation(posY + 1, posX, '_');			//
			}
			else if (isRightDirection && isStandUp && isBlocking && !isDead) {
				lvl->setCharInLocation(posY - 1, posX - 1, HEAD);		//		0|
				lvl->setCharInLocation(posY - 1, posX, -76);			//		o|
				lvl->setCharInLocation(posY, posX - 1, 48);				//		Л
				lvl->setCharInLocation(posY, posX, -76);
				animationWalk(lvl);
			}
			else if (isRightDirection && !isStandUp && !isDead) {
				lvl->setCharInLocation(posY + 1, posX, ']');				//
				lvl->setCharInLocation(posY + 1, posX - 1, HEAD);			//		_=o]
				animationWalk(lvl);
			}
			else if (!isRightDirection && !isStandUp && !isDead) {
				lvl->setCharInLocation(posY + 1, posX - 2, '[');			//
				lvl->setCharInLocation(posY + 1, posX - 1, HEAD);			//		[o=_
				animationWalk(lvl);
			}
			else if (!isRightDirection && isDead) {
				lvl->setCharInLocation(posY + 1, posX, HEAD);			//
				lvl->setCharInLocation(posY + 1, posX - 1, 127);		//    _#o
				lvl->setCharInLocation(posY + 1, posX - 2, '_');		//
			}
			else if (!isRightDirection && isStandUp && !isBlocking && !isDead) {
				animationWalk(lvl);
				animationBody(lvl);
			}
			else {
				lvl->setCharInLocation(posY - 1, posX - 1, HEAD);
				lvl->setCharInLocation(posY - 1, posX - 2, -61);		//	   |o
				lvl->setCharInLocation(posY, posX - 1, 48);				//	   |0
				lvl->setCharInLocation(posY, posX - 2, -61);			//		Л
				animationWalk(lvl);
			}
			if (Bolt_in_Flight) shoote(lvl, eList, flym);
			if (isUseSplit && stage_of_split == 1) useSplit(lvl, eList, flym);
			if (isUseAttack && stage_of_attack == 2) useAttack(lvl, eList, flym);
		}
	}
	else if (!m_onTheGround)
	{
		lvl->setCharInLocation(posY, posX - 2, HEAD);			//		
		lvl->setCharInLocation(posY, posX - 1, 'V');			//		OV^=>
		lvl->setCharInLocation(posY, posX, 127);				//
		lvl->setCharInLocation(posY, posX + 1, '=');
		lvl->setCharInLocation(posY, posX + 2, -72);
	}
}
void Player::movePlayer(World* lvl, std::array<Knight*, 3>& eList) {
	if (active_points < max_active_points) ++active_points;
	if (stage_of_split) --stage_of_split;
	if (stage_of_attack) --stage_of_attack;
	m_in_tunnel = (!isStandUp && level == Levels::CAVE && (posX > 93 && posX < 105)) ? true : false;
	int oldX = posX;
	if (!isDead && !stage_of_split && !stage_of_attack && m_onTheGround) {
		if (GetKeyState('I') < 0) { openInventory(); }
		if ((GetAsyncKeyState('O') & 0x0001) != 0) { useHealingPoition(); }
		if ((GetAsyncKeyState('Q') & 0x0001) != 0) { isRightDirection = false; }
		if ((GetAsyncKeyState('E') & 0x0001) != 0) { isRightDirection = true; }
		if ((GetAsyncKeyState('N') & 0x0001) != 0) {
			if (active_points >= cost_split && !isBlocking && isStandUp && isArmedSword) {
				stage_of_split = 5;				// look change in animationBody()
				isUseSplit = true;
				active_points -= cost_split;
			}
		}
		if ((GetAsyncKeyState('F') & 0x0001) != 0) {
			if (active_points >= cost_hit && !isBlocking && isStandUp && isArmedSword) {
				isUseAttack = true;
				stage_of_attack = 2;			// look change in animationBody()
				active_points -= cost_hit;
			}
			else if (bolt && !isBlocking && isStandUp && !range && isArmedCrossbow) {
				Bolt_in_Flight = true;
				--bolt;
			}
		}
		if ((GetAsyncKeyState('B') & 0x0001) != 0) {
			if (isBlocking) isBlocking = false;
			else isBlocking = true;
		}
		if ((GetAsyncKeyState('W') & 0x0001) != 0) {
			if (!isStandUp && !m_in_tunnel) {
				m_stage_up_dawn = true;
				isStandUp = true;
			}
		}
		if ((GetAsyncKeyState('S') & 0x0001) != 0) {
			if (isStandUp) {
				m_stage_up_dawn = true;
				isStandUp = false;
			}
		}
		//if ((GetAsyncKeyState('A') & 0x0001) != 0) {
		if (GetKeyState('A') < 0) {
			if (!step) step = true;
			else step = false;
			if (!(!isStandUp && isRightDirection))
			{
				--posX;
			}
			if (!isStandUp && step && !isRightDirection)
			{
				++posX;
			}
			if ((posX == 1) ||
				(level == Levels::CAVE && isStandUp && posX == 104))
				++posX;

			//if (isStandUp) {
			//}

			// FOR MOVE 2posX INFRONT
			/*
			if (isRightDirection && isStandUp) {
				--posX;
				if (posX == 1) ++posX;		//Чтоб щит или меч не выходили за границу
			}
			else if (!isRightDirection && isStandUp) {
				posX -= 2;
				if (posX == 1) ++posX;
				if (posX < 1) posX = oldX;
			}
			*/
			//
		}
		//if ((GetAsyncKeyState('D') & 0x0001) != 0) {
		if (GetKeyState('D') < 0) {
			if (!step) step = true;
			else step = false;
			if (!(!isStandUp && !isRightDirection))
			{
				++posX;
			}
			if (!isStandUp && step && isRightDirection)
			{
				--posX;
			}
			if ((posX == WIDTH_MAP) ||
				(level == Levels::CAVE && isStandUp && posX == 94) ||
				(level == Levels::VILADGE_TAVERN && posX == (WIDTH_MAP - WIDTH_WINDOW)))
				--posX;
			/*
			{

			if (isStandUp) {
				++posX;
				}
				else if (level == Levels::VILADGE_TAVERN) {
					if (posX == (WIDTH_MAP - WIDTH_WINDOW)) --posX;
				}
				else {
					if (posX == WIDTH_MAP) --posX;
				}
			}
			*/

			/*
			if (isRightDirection && isStandUp) {
				posX += 2;
				if (level == Levels::CAVE) {
					if (posX == (WIDTH_MAP - center_screen)) --posX;
					if (posX > (WIDTH_MAP - center_screen)) posX = oldX;
				}
				else if (level == Levels::VILADGE_TAVERN) {
					if (posX == (WIDTH_MAP - WIDTH_WINDOW)) --posX;
					if (posX > (WIDTH_MAP - WIDTH_WINDOW)) posX = oldX;
				}
				else {
					if (posX == WIDTH_MAP) --posX;
					if (posX > WIDTH_MAP) posX = oldX;
				}
			}
			else if (!isRightDirection && isStandUp) {
				++posX;
				if (level == Levels::CAVE) {
					if (posX == (WIDTH_MAP - center_screen)) --posX;
				}
				else if (level == Levels::VILADGE_TAVERN) {
					if (posX == (WIDTH_MAP - WIDTH_WINDOW)) --posX;
				}
				else {
					if (posX == WIDTH_MAP) --posX;
				}
			}
			*/
		}
		if ((GetAsyncKeyState('G') & 0x0001) != 0) {
			if (haveCrossbow) changeWeapon();
		}
		if ((GetAsyncKeyState('R') & 0x0001) != 0)
		{
			if (signal)
			{
				healing_poitions += eList[enemyID - 1]->getHealingPoitions();
				bolt += eList[enemyID - 1]->getBolt();
				monets += eList[enemyID - 1]->getMonets();
				eList[enemyID - 1]->setEmpty();
			}
			else if (level == Levels::FIELD && walk_to == Transfer_to::BORDER_VILADGE)
			{
				posX = 4;
				level = Levels::VILADGE;
			}
			else if (level == Levels::VILADGE && walk_to == Transfer_to::FIELD)
			{
				level = Levels::FIELD;
				posX = 155;
			}
			else if (level == Levels::VILADGE_TAVERN && walk_to == Transfer_to::BORDER_VILADGE)
			{
				level = Levels::VILADGE;
				posX = 100;
			}
			else if (walk_to == Transfer_to::VILADGE_TAVERN)
			{
				posX = 4;
				level = Levels::VILADGE_TAVERN;
			}
			else if (level == Levels::VILADGE && walk_to == Transfer_to::FOREST)
			{
				level = Levels::FOREST;
				posX = 4;
			}
			else if (level == Levels::FOREST && walk_to == Transfer_to::BORDER_VILADGE)
			{
				level = Levels::VILADGE;
				posX = 155;
			}
			else if (walk_to == Transfer_to::CAVE)
			{
				posX = 4;
				level = Levels::CAVE;
			}
			else if (level == Levels::CAVE && walk_to == Transfer_to::FOREST)
			{
				level = Levels::FOREST;
				posX = 145;
			}
		}
		if (level == Levels::VILADGE && (98 < posX && posX < 104))
			walk_to = Transfer_to::VILADGE_TAVERN;
		else if (level == Levels::VILADGE_TAVERN && (posX < 15))
			walk_to = Transfer_to::BORDER_VILADGE;
		else if (level == Levels::FIELD && (posX > 150))
			walk_to = Transfer_to::BORDER_VILADGE;
		else if (level == Levels::VILADGE && (posX < 15))
			walk_to = Transfer_to::FIELD;
		else if (level == Levels::VILADGE && (posX > 150))
			walk_to = Transfer_to::FOREST;
		else if (level == Levels::FOREST && (posX < 15))
			walk_to = Transfer_to::BORDER_VILADGE;
		else if (level == Levels::FOREST && (posX > 135 && posX < 145))
			walk_to = Transfer_to::CAVE;
		else if (level == Levels::CAVE && (posX < 15))
			walk_to = Transfer_to::FOREST;
		else walk_to = Transfer_to::END;
		signal = false;
	}
	if (m_isFall)
	{
		if (posY < 21)
			posY += 3;
		else
		{
			posY = 23;
			m_onTheGround = true;
			m_isFall = false;
			health_points = 0;
			isDead = true;
		}
	}
	if (level == Levels::CAVE && posX > 120)
	{
		finalDialog(lvl);
		isDead = true;
		wakeUp = true;
	}
}
void Player::finalDialog(World* lvl)
{
	setCurPos(16, 30);	puts("I found you, dragon"); Sleep(3000);
	setCurPos(16, 30);	puts("                   ");
	setCurPos(14, 50);	puts("Khe-Khe, what?"); Sleep(3000);
	setCurPos(14, 50);	puts("              ");
	setCurPos(16, 30);	puts("I FOUND YOU AND NOW KILL YOU!"); Sleep(4000);
	setCurPos(16, 30);	puts("                             ");
	setCurPos(14, 50);	puts("Oh yeah?"); Sleep(2000);
	setCurPos(14, 50);	puts("*Deep breath*"); Sleep(3000);
	setCurPos(14, 50);	puts("              ");
	setCurPos(18, 58);	_putch('~'); setCurPos(19, 58);	_putch('~'); Sleep(500);
	setCurPos(18, 55);	_putch('~'); setCurPos(20, 57);	_putch('~'); Sleep(500);
	setCurPos(18, 51);	_putch('~'); setCurPos(19, 53);	_putch('~'); 
	setCurPos(20, 51);	_putch('~'); setCurPos(21, 53);	_putch('~'); Sleep(500);
	setCurPos(18, 45);	_putch('~'); setCurPos(19, 47);	_putch('~');
	setCurPos(21, 48);	_putch('~'); setCurPos(23, 48);	_putch('~'); Sleep(500);
	setCurPos(18, 39);	_putch('~'); setCurPos(19, 41);	_putch('~');
	setCurPos(20, 42);	_putch('~'); setCurPos(21, 44);	_putch('~');
	setCurPos(22, 45);	_putch('~'); setCurPos(24, 46);	_putch('~'); Sleep(500);
	setCurPos(18, 34);	_putch('~'); setCurPos(19, 36);	_putch('~');
	setCurPos(20, 38);	_putch('~'); setCurPos(22, 41);	_putch('~');
	setCurPos(23, 42);	_putch('~'); setCurPos(24, 41);	_putch('~'); 
	setCurPos(16, 30);	puts("AAAaaaaa!"); Sleep(500);
	setCurPos(24, 31);	_putch('~'); setCurPos(20, 30);	_putch('~');
	setCurPos(17, 30);	_putch('~'); setCurPos(19, 32);	_putch('~');
	setCurPos(21, 34);	_putch('~'); setCurPos(23, 34);	_putch('~'); 
	
	Sleep(500);
	setCurPos(11, 22);	_putch('~'); setCurPos(12, 20);	_putch('~');
	setCurPos(13, 20);	_putch('~'); setCurPos(14, 19);	_putch('~');
	setCurPos(15, 21);	_putch('~'); setCurPos(14, 23);	_putch('~');
	setCurPos(17, 23);	_putch('~'); setCurPos(16, 26);	_putch('~');
	setCurPos(18, 27);	_putch('~'); setCurPos(20, 25);	_putch('~');
	setCurPos(24, 24);	_putch('~'); setCurPos(22, 28);	_putch('~'); Sleep(1500);
	setCurPos(0, 0);
	/*int cnt = WIDTH_WINDOW * HIGHT_WINDOW;
	while (cnt) 
	{
		_putch('~'); --cnt;
	}
	setCurPos(0, 0);*/
}
void Player::openInventory() {
	//std::cin.setf(std::ios::unitbuf);
	int temp = CONST_EXP + lvl * 45;
	bool done = false;
	char ch = 'A';
	while (!done) {

		puts("\n\n|==================|");
		printf("|LVL%-2d             |\n", lvl);
		printf("|EXP%-4d NEXT %-4d |\n", m_exp, temp);
		puts("|==================|");
		printf("|HP:%3d            |\n", health_points);
		printf("|AP:%2d             |\n", active_points);
		printf("|%c%-3d              |\n", 3, healing_poitions);
		printf("|%c%-3d              |\n", 24, bolt);
		printf("|%c%-5d            |\n", 36, monets);
		puts("|press'K'to close  |");
		puts("|==================|\n");

		ch = _getch();
		if (toupper(ch) == 'K') {
			done = true;
		}
		setCurPos(0, 0);
	}
	//Sleep(5000);
}
void Player::changeWeapon() {
	if (!isBlocking && isStandUp) {
		if (isArmedSword) {
			isArmedSword = false;
			isArmedCrossbow = true;
		}
		else if (isArmedCrossbow) {
			isArmedCrossbow = false;
			isArmedSword = true;
		}
	}
}
void Player::shoote(World* lvl, std::array<Knight*, 3>& eList, FlyingMonster& flym) {
	if (!range && isRightDirection) {
		shooteRightDirection = true;
		shoote_posX = posX;
	}
	else if (!range && !isRightDirection) {
		shooteRightDirection = false;
		shoote_posX = posX - 2;
	}
	if (range < max_range && shooteRightDirection)	shoote_posX += 2;
	else if (range < max_range && !shooteRightDirection) shoote_posX -= 2;

	lvl->setCharInLocation(posY, shoote_posX, '-');
	++range;

	for (const auto enemy : eList)
	{
		if (!enemy->checkIsDead() && (level == enemy->checkLevel()))
		{
			if (!enemy->checkBlock() ||
				(enemy->checkBlock() && (isRightDirection == enemy->checkDirection()))) {
				if ((shoote_posX == enemy->getPosX() - 1) ||
					(shoote_posX == enemy->getPosX()) ||
					(shoote_posX == enemy->getPosX() + 1)) {
					Bolt_in_Flight = false;
					range = 0;
					enemy->takeDamage(lvl, physical_attack);
				}
			}
		}
	}
	if (!flym.checkIsDead() && (level == flym.checkLevel()))
	{
		if ((shoote_posX == flym.getPosX() - 1) ||
			(shoote_posX == flym.getPosX()) ||
			(shoote_posX == flym.getPosX() + 1))
		{
			Bolt_in_Flight = false;
			range = 0;
			flym.isDead();
		}
	}
	if (range >= max_range) { range = 0; Bolt_in_Flight = false; }
}
void Player::useSplit(World* lvl, std::array<Knight*, 3>& eList, FlyingMonster& flym) {
	for (const auto enemy : eList)
	{
		if (!enemy->checkIsDead() && (level == enemy->checkLevel()))
		{
			if (!enemy->checkBlock() ||
				(enemy->checkBlock() && (this->isRightDirection == enemy->checkDirection())))
			{
				for (int i = 1; i < 6; ++i)
				{
					if ((isRightDirection && (posX + 1 + i == (enemy->getPosX() - 1))) ||
						(!isRightDirection && (posX - 1 - i == (enemy->getPosX() + 1))))
					{
						enemy->takeDamage(lvl, physical_attack * 2);
						break;
					}
					if ((isRightDirection && (posX + 1 + i == (flym.getPosX() - 1))) ||
						(!isRightDirection && (posX - 1 - i == (flym.getPosX() + 1))))
					{
						flym.isDead();
						break;
					}
				}
			}
		}
	}
	isUseSplit = false;
}
void Player::useAttack(World* lvl, std::array<Knight*, 3>& eList, FlyingMonster& flym) {
	for (const auto enemy : eList)
	{
		if (!enemy->checkIsDead() && (level == enemy->checkLevel()))
		{
			if (!enemy->checkBlock() ||
				(enemy->checkBlock() && (this->isRightDirection == enemy->checkDirection())))
			{
				for (int i = 0; i < 3; ++i)
				{
					if ((isRightDirection && (posX + 1 + i == (enemy->getPosX() - 1))) ||
						(!isRightDirection && (posX - 1 - i == (enemy->getPosX() + 1))))
					{
						enemy->takeDamage(lvl, physical_attack);
						break;
					}
					if ((isRightDirection && (posX + 1 + i == (flym.getPosX() - 1))) ||
						(!isRightDirection && (posX - 1 - i == (flym.getPosX() + 1))))
					{
						flym.isDead();
						break;
					}
				}
			}
		}
	}
	isUseAttack = false;
}
void Player::useHealingPoition() {
	if (healing_poitions) {
		--healing_poitions;
		health_points += 25;
		if (health_points > max_health_points)
			health_points = max_health_points;;
	}
}
void Player::animationWalk(World* lvl) {
	if (isStandUp)
	{
		if (!step) lvl->setCharInLocation(posY + 1, posX - 1, LEGS2);
		else lvl->setCharInLocation(posY + 1, posX - 1, LEGS1);
	}
	else if (!isStandUp && isRightDirection)
	{
		if (!step)
		{
			lvl->setCharInLocation(posY + 1, posX - 3, '_');
			lvl->setCharInLocation(posY + 1, posX - 2, '=');
		}
		else lvl->setCharInLocation(posY + 1, posX - 2, -55);
	}
	else if (!isStandUp && !isRightDirection)
	{
		if (!step)
		{
			lvl->setCharInLocation(posY + 1, posX, '=');
			lvl->setCharInLocation(posY + 1, posX + 1, '_');
		}
		else lvl->setCharInLocation(posY + 1, posX, -69);
	}
}
void Player::animationUpDown(World* lvl)
{
	if (isRightDirection && !isBlocking) {
		lvl->setCharInLocation(posY, posX - 1, HEAD);
		lvl->setCharInLocation(posY, posX, '/');
		lvl->setCharInLocation(posY + 1, posX, 93);
		lvl->setCharInLocation(posY + 1, posX - 1, '>');
		lvl->setCharInLocation(posY + 1, posX - 2, 95);
	}
	else if (!isRightDirection && !isBlocking) {
		lvl->setCharInLocation(posY, posX - 1, HEAD);
		lvl->setCharInLocation(posY, posX - 2, '\\');
		lvl->setCharInLocation(posY + 1, posX - 2, 91);
		lvl->setCharInLocation(posY + 1, posX - 1, '<');
		lvl->setCharInLocation(posY + 1, posX, 95);
	}
	else if (isRightDirection && isBlocking) {
		lvl->setCharInLocation(posY, posX - 1, HEAD);
		lvl->setCharInLocation(posY, posX, -76);
		lvl->setCharInLocation(posY + 1, posX, -76);
		lvl->setCharInLocation(posY + 1, posX - 1, '>');
		lvl->setCharInLocation(posY + 1, posX - 2, 95);
	}
	else if (!isRightDirection && isBlocking) {
		lvl->setCharInLocation(posY, posX - 1, HEAD);
		lvl->setCharInLocation(posY, posX - 2, -61);
		lvl->setCharInLocation(posY + 1, posX - 2, -61);
		lvl->setCharInLocation(posY + 1, posX - 1, '<');
		lvl->setCharInLocation(posY + 1, posX, 95);
	}
}
void Player::animationBody(World* lvl) {
	if (stage_of_split == 5 && isRightDirection) {
		lvl->setCharInLocation(posY - 1, posX - 1, HEAD);
		lvl->setCharInLocation(posY, posX - 2, '<');			//       o
		lvl->setCharInLocation(posY, posX - 1, '/');			//	    </]
		lvl->setCharInLocation(posY, posX, ']');				//	    /|
		lvl->setCharInLocation(posY + 1, posX - 1, '|');
		lvl->setCharInLocation(posY + 1, posX - 2, '/');
	}
	else if (stage_of_split == 4 && isRightDirection) {
		lvl->setCharInLocation(posY, posX - 5, '-');
		lvl->setCharInLocation(posY, posX - 4, 26);
		lvl->setCharInLocation(posY, posX - 3, '^');
		lvl->setCharInLocation(posY, posX - 2, HEAD);			//        
		lvl->setCharInLocation(posY, posX - 1, ']');			//   ->^O]
		lvl->setCharInLocation(posY + 1, posX - 1, '\\');		/*	   < \    */
		lvl->setCharInLocation(posY + 1, posX - 2, ' ');
		lvl->setCharInLocation(posY + 1, posX - 2, '<');
	}
	else if (stage_of_split == 3 && isRightDirection) {
		lvl->setCharInLocation(posY, posX - 3, '<');
		lvl->setCharInLocation(posY, posX - 2, '_');
		lvl->setCharInLocation(posY, posX - 1, HEAD);			//        
		lvl->setCharInLocation(posY, posX, ']');				//	   <_O]
		lvl->setCharInLocation(posY + 1, posX - 1, '\\');		/*	    /\    */
		lvl->setCharInLocation(posY + 1, posX - 2, '/');
	}
	else if (stage_of_split == 2 && isRightDirection) {
		lvl->setCharInLocation(posY, posX - 2, ' ');			//        
		lvl->setCharInLocation(posY, posX - 1, '[');			//	     [O~>--
		lvl->setCharInLocation(posY, posX, HEAD);				/*	    />    */
		lvl->setCharInLocation(posY, posX + 1, '~');
		lvl->setCharInLocation(posY, posX + 2, 27);
		lvl->setCharInLocation(posY, posX + 3, '-');
		lvl->setCharInLocation(posY, posX + 4, '-');
		lvl->setCharInLocation(posY + 1, posX - 1, '>');
		lvl->setCharInLocation(posY + 1, posX - 2, '/');
	}
	else if (stage_of_split == 1 && isRightDirection) {
		lvl->setCharInLocation(posY - 1, posX - 1, HEAD);
		lvl->setCharInLocation(posY - 1, posX + 1, '/');
		lvl->setCharInLocation(posY, posX - 2, '[');			//      O /
		lvl->setCharInLocation(posY, posX - 1, '/');			//	   [/^
		lvl->setCharInLocation(posY, posX, '^');				/*	    Л     */
		lvl->setCharInLocation(posY + 1, posX - 1, LEGS1);
	}
	else if (!stage_of_split && isRightDirection) {
		lvl->setCharInLocation(posY - 1, posX - 1, HEAD);
		lvl->setCharInLocation(posY, posX - 2, 91);				  //         o
		lvl->setCharInLocation(posY, posX - 1, 'L');			  //	    [L/
		if (isArmedSword) lvl->setCharInLocation(posY, posX, '/');//	     Л
		else lvl->setCharInLocation(posY, posX, 26);
	}
	else if (stage_of_split == 5 && !isRightDirection) {
		lvl->setCharInLocation(posY - 1, posX - 1, HEAD);
		lvl->setCharInLocation(posY, posX - 2, '[');			//       o
		lvl->setCharInLocation(posY, posX - 1, ']');			//	    []>
		lvl->setCharInLocation(posY, posX, '>');				//	     |\  
		lvl->setCharInLocation(posY + 1, posX - 1, '|');
		lvl->setCharInLocation(posY + 1, posX, '\\');
	}
	else if (stage_of_split == 4 && !isRightDirection) {
		lvl->setCharInLocation(posY, posX + 3, '-');
		lvl->setCharInLocation(posY, posX + 2, 27);
		lvl->setCharInLocation(posY, posX + 1, '^');
		lvl->setCharInLocation(posY, posX, HEAD);					//        
		lvl->setCharInLocation(posY, posX - 1, '[');				//	 [O^>-				
		lvl->setCharInLocation(posY + 1, posX - 1, '/');			/*	 / >    */
		lvl->setCharInLocation(posY + 1, posX, ' ');
		lvl->setCharInLocation(posY + 1, posX + 1, '>');
	}
	else if (stage_of_split == 3 && !isRightDirection) {
		lvl->setCharInLocation(posY, posX + 1, '>');
		lvl->setCharInLocation(posY, posX, '_');
		lvl->setCharInLocation(posY, posX - 1, HEAD);			//        
		lvl->setCharInLocation(posY, posX - 2, '[');			//	   [O_>			
		lvl->setCharInLocation(posY + 1, posX, '\\');			/*      /\     */
		lvl->setCharInLocation(posY + 1, posX - 1, '/');
	}
	else if (stage_of_split == 2 && !isRightDirection) {
		lvl->setCharInLocation(posY, posX - 6, '-');
		lvl->setCharInLocation(posY, posX - 5, '-');			//        
		lvl->setCharInLocation(posY, posX - 4, 26);				//	 --<~O]
		lvl->setCharInLocation(posY, posX - 3, '~');			/*	      <\    */
		lvl->setCharInLocation(posY, posX - 2, HEAD);
		lvl->setCharInLocation(posY, posX - 1, ']');
		lvl->setCharInLocation(posY, posX, ' ');
		lvl->setCharInLocation(posY + 1, posX - 1, '<');
		lvl->setCharInLocation(posY + 1, posX, '\\');
	}
	else if (stage_of_split == 1 && !isRightDirection) {
		lvl->setCharInLocation(posY - 1, posX - 1, HEAD);
		lvl->setCharInLocation(posY - 1, posX - 3, '\\');
		lvl->setCharInLocation(posY, posX - 2, '^');			//    \ O  
		lvl->setCharInLocation(posY, posX - 1, '[');			//     ^[]
		lvl->setCharInLocation(posY, posX, ']');				/*	    Л      */
		lvl->setCharInLocation(posY + 1, posX - 1, LEGS1);
	}
	else if (!stage_of_split && !isRightDirection) {
		lvl->setCharInLocation(posY - 1, posX - 1, HEAD);
		lvl->setCharInLocation(posY, posX, 93);							//		o
		lvl->setCharInLocation(posY, posX - 1, 91);						//	   \[]
		if (isArmedSword) lvl->setCharInLocation(posY, posX - 2, '\\');	//		Л
		else lvl->setCharInLocation(posY, posX - 2, 27);
	}
	//if (active_points > 1) {   // Для ориентации по шкале АР
		//if (isRightDirection && isStandUp && !isBlocking) {

	if (stage_of_attack == 2 && isRightDirection) {
		lvl->setCharInLocation(posY, posX, ' ');
		lvl->setCharInLocation(posY - 1, posX, '/');
		lvl->setCharInLocation(posY, posX - 1, '~');
	}
	else if (stage_of_attack == 1 && isRightDirection) {
		lvl->setCharInLocation(posY - 1, posX, ' ');
		lvl->setCharInLocation(posY, posX - 1, '=');
		lvl->setCharInLocation(posY, posX, 27);
		lvl->setCharInLocation(posY, posX + 1, '-');
		lvl->setCharInLocation(posY, posX + 2, '-');
	}
	else if (stage_of_attack == 2 && !isRightDirection) {
		lvl->setCharInLocation(posY, posX - 2, ' ');
		lvl->setCharInLocation(posY - 1, posX - 2, '\\');
	}
	else if (stage_of_attack == 1 && !isRightDirection) {
		lvl->setCharInLocation(posY - 1, posX - 2, ' ');
		lvl->setCharInLocation(posY, posX - 2, 26);
		lvl->setCharInLocation(posY, posX - 3, '-');
		lvl->setCharInLocation(posY, posX - 4, '-');
	}

	//checkAllEnemyForHit(lvl, eList);
}
void Player::animationIsDead(World* lvl) {
	if (isRightDirection) {
		lvl->setCharInLocation(posY - 1, posX - 1, ' ');
		lvl->setCharInLocation(posY, posX - 2, HEAD);
		lvl->setCharInLocation(posY, posX - 1, 'I');
		lvl->setCharInLocation(posY + 1, posX, '\\');
		lvl->setCharInLocation(posY + 1, posX - 1, '>');
	}
	else if (!isRightDirection) {
		lvl->setCharInLocation(posY - 1, posX - 1, ' ');
		lvl->setCharInLocation(posY, posX, HEAD);
		lvl->setCharInLocation(posY, posX - 1, 91);
		lvl->setCharInLocation(posY + 1, posX - 2, '/');
		lvl->setCharInLocation(posY + 1, posX - 1, '<');
	}
}
void Player::takeDamage(World* lvl, int p_attack) {
	health_points -= p_attack;
	if (health_points < 1 && !isDead) {
		animationIsDead(lvl);
		isDead = true;
	}
}
void Player::setExp(int exp) {
	m_exp += static_cast<int>(exp / 3);
	checkLvlUp();
}
void Player::checkLvlUp() {
	int temp = CONST_EXP + lvl * 45;
	if (temp <= m_exp) {
		++lvl;
		physical_attack += lvl + 5;
		m_exp = 0;
		health_points = max_health_points;
		--cost_hit;
		if (cost_hit < 5) cost_hit = 5;
		--cost_split;
		if (cost_split < 5) cost_hit = 5;
		textNPC();
		Sleep(500);
	}
}
void Player::textNPC()const {
	const char* msg = "lvl Up!!!";
	int length = static_cast<int>(strlen(msg) / 2);

	if (posX < length)				//Установка позиции текста над игроком
		setCurPos(posY - 6, 0);
	else if (posX >= WIDTH_MAP - length)
		setCurPos(posY - 6, WIDTH_WINDOW - static_cast<int>(strlen(msg)));
	else if (posX >= length && posX < center_screen)
		setCurPos(posY - 6, posX - length);
	else if (posX > WIDTH_MAP - center_screen - 1)
		setCurPos(posY - 6, (center_screen - length + 1) + posX - (WIDTH_MAP - center_screen));
	else
		setCurPos(posY - 6, center_screen - length);

	while (*msg) putchar(*msg++);
	setCurPos(0, 0);
}
//=============================================================================
void showScreen(World* lvl, NPC* pl) {        //Попытки ускорить вывод на экран
	static char screen[HIGHT_WINDOW * WIDTH_WINDOW + 1]{ 0 };
	enum { TOP = 0, HORIZON = 8, ROCK = 33 };
	char* temp_poiter = screen;
	int y, x;
	//========================== Show freeze sky
	if (lvl->whatLevelOnScreen() == Levels::VILADGE)
	{
		for (y = TOP; y < HORIZON; ++y)
			for (x = WIDTH_MAP - WIDTH_WINDOW; x < WIDTH_MAP; ++x)
				*temp_poiter++ = lvl->getPieceOfLocation(y, x);
		y = HORIZON;
	}
	else if (lvl->whatLevelOnScreen() == Levels::FIELD || lvl->whatLevelOnScreen() == Levels::FOREST)
	{
		for (y = TOP; y < HORIZON; ++y)
			for (x = 0; x < WIDTH_WINDOW; ++x)
				*temp_poiter++ = lvl->getPieceOfLocation(y, x);
		y = HORIZON;
	}
	else
		y = TOP;

	if (pl->getPosX() <= center_screen) {
		for (; y < HIGHT_WINDOW; ++y)
			for (x = 0; x < WIDTH_WINDOW; ++x)
				*temp_poiter++ = lvl->getPieceOfLocation(y, x);
	}
	else if (pl->getPosX() >= (WIDTH_MAP - center_screen)) {
		for (; y < HIGHT_WINDOW; ++y)
			for (x = WIDTH_MAP - WIDTH_WINDOW; x < WIDTH_MAP; ++x)
				*temp_poiter++ = lvl->getPieceOfLocation(y, x);
	}
	else {
		for (; y < HIGHT_WINDOW; ++y)
			for (x = pl->getPosX() - center_screen; x < pl->getPosX() + center_screen; ++x)
				*temp_poiter++ = lvl->getPieceOfLocation(y, x);
	}
	//========================== Show parth of rock with freeze sky
	if (lvl->whatLevelOnScreen() == Levels::FOREST)
	{
		if (pl->getPosX() > (WIDTH_MAP - center_screen))
		{
			for (int y = 0, i = 0; y < 8; ++y, i += WIDTH_WINDOW)
			{
				for (int x = 0; x < ROCK; ++x)
					screen[WIDTH_WINDOW - ROCK + x + i] = lvl->getPieceOfLocation(y, WIDTH_MAP - ROCK + x);
			}
		}
		else if (pl->getPosX() <= (WIDTH_MAP - center_screen)
			&& pl->getPosX() > (WIDTH_MAP - center_screen - ROCK))
		{
			int temp = pl->getPosX() - (WIDTH_MAP - center_screen - ROCK);
			for (int y = 0, i = 0; y < 8; ++y, i += WIDTH_WINDOW)
			{
				for (int x = 0; x < temp; ++x)
					screen[WIDTH_WINDOW - temp + x + i] = lvl->getPieceOfLocation(y, WIDTH_MAP - ROCK + x);
			}
		}
	}
	
	screen[HIGHT_WINDOW * WIDTH_WINDOW] = '\0';		// Заменил putchar(lvl->location[y][x]);
	temp_poiter = screen;							//
	while (*temp_poiter) putchar(*temp_poiter++);

	setCurPos(0, 0);
	/*													Мало символов через буффер
				putchar(lvl->location[y][x]);
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;
	WriteConsoleOutputCharacter(hConsole, screen, HIGHT_WINDOW * WIDTH_WINDOW, {0, 0}, &dwBytesWritten);
				*temp_poiter++ = lvl->location[y][x];
		wchar_t* temp_poiter = (wchar_t*)lvl->location;
	*/
}
//=============================================================================