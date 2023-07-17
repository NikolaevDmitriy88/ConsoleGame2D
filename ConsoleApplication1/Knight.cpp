#include "NPC.h"
unsigned int Knight::counter = 0;

void Knight::putOnMap(World* lvl, Player* pl) {
	if (!isEmpty) {
		if (level == lvl->whatLevelOnScreen()) {
			if (max_health_points - part < health_points
				&& health_points < max_health_points) {
				L = '='; C = '='; R = '-';
			}
			else if (part < health_points
				&& health_points <= max_health_points - part) {
				L = '='; C = '-'; R = ' ';
			}
			else if (0 < health_points && health_points <= part) {
				L = '-'; C = ' '; R = ' ';
			}
			if (health_points <= 0) {
				L = ' '; C = ' '; R = ' ';
			}
			lvl->setCharInLocation(posY - 2, posX - 2, L);
			lvl->setCharInLocation(posY - 2, posX - 1, C);
			lvl->setCharInLocation(posY - 2, posX, R);

			if (isRightDirection && isStandUp && !isBlocking && !isDead) {
				animationBody(lvl);
				animationWalk(lvl);
			}
			else if (!isRightDirection && isStandUp && !isBlocking && !isDead) {
				animationBody(lvl);
				animationWalk(lvl);
			}
			else if (isRightDirection && isDead) {
				lvl->setCharInLocation(posY + 1, posX - 2, 2);
				lvl->setCharInLocation(posY + 1, posX - 1, 127);
				lvl->setCharInLocation(posY + 1, posX, '_');
			}
			else if (!isRightDirection && isDead) {
				lvl->setCharInLocation(posY + 1, posX, 2);
				lvl->setCharInLocation(posY + 1, posX - 1, 127);
				lvl->setCharInLocation(posY + 1, posX - 2, '_');
			}
			else if (isRightDirection && isStandUp && isBlocking && !isDead) {
				lvl->setCharInLocation(posY - 1, posX - 1, 2);
				lvl->setCharInLocation(posY - 1, posX, -76);
				lvl->setCharInLocation(posY, posX - 1, 48);
				lvl->setCharInLocation(posY, posX, -76);
				animationWalk(lvl);
			}
			else if (!isRightDirection && isStandUp && isBlocking && !isDead) {
				lvl->setCharInLocation(posY - 1, posX - 1, 2);
				lvl->setCharInLocation(posY - 1, posX - 2, -61);
				lvl->setCharInLocation(posY, posX - 1, 48);
				lvl->setCharInLocation(posY, posX - 2, -61);
				animationWalk(lvl);
			}
		}
		if (isUseAttack && stage_of_attack == 1) checkHit(lvl, pl);
	}
}
void Knight::moveII(World* lvl, Player* pl) {
	if (stage_of_attack)
		--stage_of_attack;
	if (!isEmpty && !stage_of_attack) {
		checkDistance(pl);
		if (!isDead && level == lvl->whatLevelOnScreen()) {
			if ((distance < range_vision && distance >= 0) &&
				!isRightDirection && !pl->checkIsDead())
			{
				seeEnemyLeft = true; seeEnemyRight = false; needBack = true;
			}
			else if ((distance > -range_vision && distance < 0) &&
				isRightDirection && !pl->checkIsDead())
			{
				seeEnemyRight = true; seeEnemyLeft = false; needBack = true;
			}
			else
			{
				seeEnemyRight = false; seeEnemyLeft = false;
			}
			//================= Тонкая настройка :) =========
			int rand_dist = 3 + rand() % 2;  // 3 + r 3
			if (seeEnemyLeft) {
				seeEnemyRight = false;
				if (0 < distance && distance < rand_dist) {
					if (active_points < 7 && !isStop)
						isStop = true;
					else if (active_points < 7 && isStop)
					{
						isStop = false;
						--posX;
					}
					else {
						if (isStop)	isStop = false;
						attack();
						++posX;
					}
				}
				else {
					if (isStop)	isStop = false;
					--posX;
				}
			}
			if (seeEnemyRight) {
				seeEnemyLeft = false;
				if (-rand_dist < distance && distance < 0) {
					if (active_points < 7 && !isStop)
						isStop = true;
					else if (active_points < 7 && isStop)
					{
						isStop = false;
						++posX;
					}
					else {
						if (isStop)	isStop = false;
						attack();
						--posX;
					}
				}
				else {
					if (isStop)	isStop = false;
					++posX;
				}
			}
			if (!seeEnemyLeft && !seeEnemyRight && needBack) {
				if (distance > 0 && distance < 3 && isRightDirection)
					isRightDirection = false;
				else if (distance < 0 && distance > -3 && !isRightDirection)
					isRightDirection = true;
				else {
					if (posX < startPosX)
					{
						isRightDirection = true;
						++posX;
					}
					else if (posX > startPosX)
					{
						isRightDirection = false;
						--posX;
					}
					else needBack = false;
				}
			}
			if (!seeEnemyLeft && !seeEnemyRight && !needBack)
			{
				if (isRightDirection) ++posX;
				else --posX;
				++steps;
				if (steps == max_steps) {
					if (isRightDirection) isRightDirection = false;
					else isRightDirection = true;
					steps = 0;
				}
			}
			if (!stage_of_attack)
			{
				int rand_time_block = rand() % 5;
				if (active_points <= rand_time_block && !pl->checkIsDead())
					isBlocking = true;								  // KNIGHT BLOCKING FEATURES  
				else
					isBlocking = false;
				if (active_points < 10)
					++active_points;
			}
		}
		else if (!pl->checkIsDead() && isDead && (distance > -5 && 5 > distance))
		{
			sendSignal(pl);
			pl->setEnemyID(this->ID);
		}
		else
		{
			seeEnemyRight = false; seeEnemyLeft = false; needBack = true;
		}
	}
	if (isDead) {
		if (stage_of_attack) stage_of_attack = 0;
		if (steps) steps = 0;
		if (step) step = false;
		if (isStop) isStop = false;
		if (haveExp) {
			pl->setExp(max_health_points);
			haveExp = false;
		}
		--timer;	//Включить отсчет и возродить
		if (!timer) {
			distance = 0;
			seeEnemyRight = false;
			seeEnemyLeft = false;
			needBack = false;
			isEmpty = false;
			isDead = false;
			haveExp = true;
			posX = startPosX;
			isRightDirection = rand() % 2;
			bolt = rand() % 5;
			monets = rand() % 15;
			healing_poitions = rand() % 2;
			health_points = max_health_points;
			timer = 150;
			L = C = R = '=';
		}
	}
}
void Knight::attack() {
	isUseAttack = true;
	stage_of_attack = 2;
	active_points -= cost_hit;
}
void Knight::checkHit(World* lvl, Player* pl) {
	if (!pl->checkIsDead())
	{
		if (!pl->checkBlock() ||
			(pl->checkBlock() && (isRightDirection == pl->checkDirection())))
		{
			for (int i = 0; i < 4; ++i)
			{
				if ((isRightDirection && (posX + 1 + i == (pl->getPosX() - 1))) ||
					(!isRightDirection && (posX - 1 - i == (pl->getPosX() + 1))))
				{
					pl->takeDamage(lvl, physical_attack);
					break;
				}
			}
		}
	}
	isUseAttack = false;
}
void Knight::animationBody(World* lvl) {
	if (stage_of_attack == 2 && isRightDirection) {
		lvl->setCharInLocation(posY - 1, posX - 1, 2);
		lvl->setCharInLocation(posY, posX - 2, '{');
		lvl->setCharInLocation(posY - 1, posX, '/');
		lvl->setCharInLocation(posY, posX - 1, '~');
	}
	else if (stage_of_attack == 1 && isRightDirection) {
		lvl->setCharInLocation(posY - 1, posX - 1, 2);
		lvl->setCharInLocation(posY, posX - 2, '{');
		lvl->setCharInLocation(posY, posX - 1, '=');
		lvl->setCharInLocation(posY, posX, 27);
		lvl->setCharInLocation(posY, posX + 1, '-');
		lvl->setCharInLocation(posY, posX + 2, '-');
	}
	else if (stage_of_attack == 0 && isRightDirection) {
		lvl->setCharInLocation(posY - 1, posX - 1, 2);
		lvl->setCharInLocation(posY, posX - 2, '{');
		lvl->setCharInLocation(posY, posX - 1, 'L');
		lvl->setCharInLocation(posY, posX, '/');
	}
	else if (stage_of_attack == 2 && !isRightDirection) {
		lvl->setCharInLocation(posY - 1, posX - 1, 2);
		lvl->setCharInLocation(posY - 1, posX - 2, '\\');
		lvl->setCharInLocation(posY, posX - 1, '{');
		lvl->setCharInLocation(posY, posX, '}');
	}
	else if (stage_of_attack == 1 && !isRightDirection) {
		lvl->setCharInLocation(posY - 1, posX - 1, 2);
		lvl->setCharInLocation(posY, posX, '}');
		lvl->setCharInLocation(posY, posX - 1, '{');
		lvl->setCharInLocation(posY, posX - 2, 26);
		lvl->setCharInLocation(posY, posX - 3, '-');
		lvl->setCharInLocation(posY, posX - 4, '-');
	}
	else if (stage_of_attack == 0 && !isRightDirection) {
		lvl->setCharInLocation(posY - 1, posX - 1, 2);
		lvl->setCharInLocation(posY, posX, '}');
		lvl->setCharInLocation(posY, posX - 1, '{');
		lvl->setCharInLocation(posY, posX - 2, '\\');
	}
}
void Knight::animationIsDead(World* lvl) {
	if (isRightDirection) {
		lvl->setCharInLocation(posY, posX - 2, 2);
		lvl->setCharInLocation(posY, posX - 1, 'I');
		//lvl->setCharInLocation(posY, posX, ' ');
		lvl->setCharInLocation(posY + 1, posX, '\\');
		lvl->setCharInLocation(posY + 1, posX - 1, '>');
		lvl->setCharInLocation(posY + 1, posX - 2, ' ');
	}
	else if (!isRightDirection) {
		lvl->setCharInLocation(posY, posX, 2);
		lvl->setCharInLocation(posY, posX - 1, 91);
		lvl->setCharInLocation(posY, posX, 93);
		lvl->setCharInLocation(posY + 1, posX - 2, '/');
		lvl->setCharInLocation(posY + 1, posX - 1, '<');
		//lvl->setCharInLocation(posY + 1, posX, ' ');
	}
}
void Knight::animationWalk(World* lvl) {
	if (!stage_of_attack && !isStop) {
		if (!step) {
			lvl->setCharInLocation(posY + 1, posX - 1, LEGS2);
			step = true;
		}
		else {
			lvl->setCharInLocation(posY + 1, posX - 1, LEGS1);
			step = false;
		}
	}
	else {
		if (!step)
			lvl->setCharInLocation(posY + 1, posX - 1, LEGS2);
		else
			lvl->setCharInLocation(posY + 1, posX - 1, LEGS1);
	}
}
void Knight::takeDamage(World* lvl, int p_attack) {
	health_points -= p_attack;
	if (health_points < 1 && !isDead) {
		animationIsDead(lvl);
		isDead = true;
	}
	textNPC();
}
void Knight::textNPC()const {
	const char* msg = "Auch! ";
	int length = static_cast<int>(strlen(msg) / 2);
	int temp = center_screen + std::abs(distance);

	if (posX < center_screen)
		setCurPos(posY - 2, posX - length);
	else
		setCurPos(posY - 2, temp - length);
	//while (*msg) putchar(*msg++);
	if (health_points > 0)
		printf("%s%d", msg, health_points);
	else
		puts("DEAD");
	Sleep(100);
	setCurPos(0, 0);
}