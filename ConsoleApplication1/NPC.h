#define _CRT_SECURE_NO_WARNINGS
#include <stdio.H>
#include <Windows.h>
#include <conio.H>
#include <stdlib.H>
#include <time.h>
#include <array>
#include <iostream>
#include <iomanip>

class NPC;
class Player;
class Knight;
class FlyingMonster;
class Spider;

enum class Levels { VILADGE, CAVE, VILADGE_TAVERN, FIELD, FOREST, END, Empty };
enum class Transfer_to { FIELD, BORDER_VILADGE, VILADGE_TAVERN, 
							CENTR_VILADGE, FOREST, CAVE, END };

constexpr char HEAD = 1;
constexpr char LEGS1 = -117;
constexpr char LEGS2 = -77;
constexpr int HIGHT_WINDOW = 25;
constexpr int WIDTH_WINDOW = 80;
//Настройки окна размер и буфер 80 ширина 26 высота для корректного отображения

constexpr int WIDTH_MAP = 160;
constexpr int HIGHT_MAP = 25;

constexpr int CONST_EXP = 150;
constexpr int center_screen = WIDTH_WINDOW / 2;
//=============================================================================
void hideCursor();
void setCurPos(int y, int x);
//=============================================================================
class World
{
public:
	void loadLevels();
	void setCharInLocation(int y, int x, char ch) { this->location[y][x] = ch; }
	char getPieceOfLocation(int y, int x) { return (location[y][x]); }
	Levels whatLevelOnScreen() const { return level; }
	void createLevel(const Player& player);
	void addChanges(const Player& player);
	void hidePartOfMap(const Player& pl);
	
private:
	Levels level;
	enum { COUNT_OF_LEVELS = 6 };
	static char location[HIGHT_MAP][WIDTH_MAP];
	static char location_end[HIGHT_MAP][WIDTH_MAP];
	static char location_cave[HIGHT_MAP][WIDTH_MAP];
	static char location_field[HIGHT_MAP][WIDTH_MAP];
	static char location_forest[HIGHT_MAP][WIDTH_MAP];
	static char location_viladge[HIGHT_MAP][WIDTH_MAP];
	static char location_viladge_tavern[HIGHT_MAP][WIDTH_MAP];
};
//=============================================================================
class NPC
{
public:
	NPC(int y, int x, int hp, Levels location)
		:posY(y), posX(x), max_health_points(hp), level(location)
	{
		isRightDirection = rand() % 2;
		isUseAttack = false;
		isBlocking = false;
		isStandUp = true;
		isDead = false;
		step = false;
		health_points = max_health_points;
		max_active_points = 10;
		healing_poitions = 0;
		physical_attack = 25;
		stage_of_attack = 0;
		active_points = 0;
		cost_hit = 10;
		monets = 0;
		bolt = 0;
		lvl = 1;
	}
	virtual ~NPC() {}
	virtual void takeDamage(World* lvl, int p_attack) = 0;
	virtual void animationUpDown(World* lvl) = 0;
	virtual void animationIsDead(World* lvl) = 0;
	virtual void animationWalk(World* lvl) = 0;
	virtual void animationBody(World* lvl) = 0;
	virtual void textNPC()const = 0;
	virtual int getPosX()const = 0;
	virtual int getPosY()const = 0;
	virtual int getHP()const = 0;
	virtual int getAP()const = 0;
	virtual bool checkBlock()const = 0;
	virtual bool checkIsDead()const = 0;
	virtual bool checkDirection()const = 0;
protected:
	Levels level;
	int healing_poitions;
	int max_health_points;
	int max_active_points;
	int physical_attack;
	int stage_of_attack;
	int health_points;
	int active_points;
	int cost_hit;
	int monets;
	int bolt;
	int posY;
	int posX;
	int lvl;
	bool isRightDirection;
	bool isUseAttack;
	bool isBlocking;
	bool isStandUp;
	bool isDead;
	bool step;
};

class Player : public NPC
{
public:
	Player(int y, int x, int hp, Levels location)
		: NPC(y, x, hp, location), m_onTheGround{ true }, m_isFall{ false },
		m_stage_up_dawn{ false }, m_in_tunnel{ false }, wakeUp{ false }
	{
		walk_to = Transfer_to::END;
		healing_poitions = 0;
		stage_of_split = 0;
		cost_split = 10;
		shoote_posX = 0;
		skill_posX = 0;
		max_range = 9;
		cost_hit = 10;
		enemyID = 0;
		monets = 0;
		range = 0;
		bolt = 0;
		m_exp = 0;
		shooteRightDirection = false;
		skillRightDirection = false;
		isRightDirection = true;
		isArmedCrossbow = false;
		haveCrossbow = true;
		isArmedSword = true;
		isUseSplit = false;
		Bolt_in_Flight = false;
		signal = false;
	}
	Transfer_to checkTransfer() const { return walk_to; }
	Levels checkLevel() const { return level; }
	bool readyForSkill() const {
		return active_points >= cost_split && !isUseSplit ? true : false;
	}
	bool crossbowInHand() const { return isArmedCrossbow; }
	bool readyForShoote() const { return bolt && !range ? true : false; }
	bool swordInHand() const { return isArmedSword; }
	bool checkOnTheGround() const { return m_onTheGround; }
	bool getSignal() const { return signal; }
	void setSignal() { if (!signal) signal = true; }
	void setEnemyID(int ID) { enemyID = ID; }
	int getMaxHp() const { return max_health_points; }
	void textNPC()const;
	void setExp(int exp);

	void liftUp() { m_onTheGround = false; }
	void setPosY(int y_) { posY = y_; }
	void setPosX(int x_) { posX = x_; }
	void fall() { m_isFall = true; }
	void setDirection() { if (!isRightDirection) isRightDirection = true; }
	void setLevel(Levels lvl) { level = lvl; }
	void finalDialog(World* lvl);

	void checkLvlUp();
	void changeWeapon();
	void openInventory();
	void useHealingPoition();
	void shoote(World* lvl, std::array<Knight*, 3>& eList, FlyingMonster& flym);
	void putOnMap(World* lvl, std::array<Knight*, 3>& eList, FlyingMonster& flym);
	void useSplit(World* lvl, std::array<Knight*, 3>& eList, FlyingMonster& flym);
	void useAttack(World* lvl, std::array<Knight*, 3>& eList, FlyingMonster& flym);
	void movePlayer(World* lvl, std::array<Knight*, 3>& eList);
	void takeDamage(World* lvl, int p_attack) override;
	void animationUpDown(World* lvl) override;
	void animationIsDead(World* lvl) override;
	void animationBody(World* lvl) override;
	void animationWalk(World* lvl) override;
	bool checkDirection() const override { return isRightDirection; }
	bool checkIsDead() const override { return isDead; }
	bool checkBlock() const override { return isBlocking; }
	bool isWakeUp() { return wakeUp; }
	int getPosX() const override { return posX; }
	int getPosY() const override { return posY; }
	int getHP() const override { return health_points; }
	int getAP() const override { return active_points; }
private:
	bool m_in_tunnel;
	bool m_stage_up_dawn;
	bool Bolt_in_Flight;
	bool isArmedSword;
	bool haveCrossbow;
	bool isArmedCrossbow;
	bool m_onTheGround;
	bool m_isFall;
	Transfer_to walk_to;
	int stage_of_split;
	int m_exp;
	int range;
	int enemyID;
	int max_range;
	int cost_split;
	int skill_posX;
	int shoote_posX;
	bool signal;
	bool wakeUp;
	bool isUseSplit;
	bool skillRightDirection;
	bool shooteRightDirection;
};

class Knight : public Player
{
public:
	Knight(int y, int x, int hp, const Levels location)
		:Player(y, x, hp, location)
	{
		++counter;
		ID = counter;
		active_points = 10;
		range_vision = 20;
		startPosX = x;
		distance = 0;
		cost_hit = 8;
		timer = 250;
		steps = 0;
		L = '=';
		C = '=';
		R = '=';
		seeEnemyRight = false;
		seeEnemyLeft = false;
		needBack = false;
		isEmpty = false;
		isStop = false;
		haveExp = true;
		bolt = rand() % 5;
		monets = rand() % 15;
		max_steps = 5 + rand() % 10;
		healing_poitions = rand() % 2;
		part = static_cast<int>(max_health_points / 3);
	}
	~Knight() { --counter; }
	void setEmpty() { isEmpty = true; monets = 0; bolt = 0;	healing_poitions = 0;}
	void sendSignal(Player* pl) { pl->setSignal(); }
	int getHealingPoitions() { return healing_poitions; }
	int getMonets() { return monets; }
	int getBolt() { return bolt; }
	int getID() { return ID; }
	virtual void moveII(World* lvl, Player* pl);
	void attack();
	void checkHit(World* lvl, Player* pl);
	void checkDistance(Player* pl) { distance = posX - pl->getPosX(); }
	void putOnMap(World* lvl, Player* pl);
	void takeDamage(World* lvl, int p_attack)override;
	void animationIsDead(World* lvl)override;
	void animationBody(World* lvl)override;
	void animationWalk(World* lvl)override;
	void textNPC()const override;
private:
	static unsigned int counter;
	int range_vision;
	int startPosX;
	int max_steps;
	int distance;
	int timer;
	int steps;
	int part;
	int ID;
	bool seeEnemyRight;
	bool seeEnemyLeft;
	bool needBack;
	bool isEmpty;
	bool haveExp;
	bool isStop;
	char L;			//
	char C;			// индикатор хп над головой
	char R;			//
};

class FlyingMonster
{
public:
	FlyingMonster(int y_, int x_) :
		m_start_posY{ y_ },
		m_start_posX{ x_ },
		m_posY{ m_start_posY },
		m_posX{ m_start_posX },
		m_exp{ 150 },
		m_stage_of_fly{ 0 },
		m_stage_of_attack{ 0 },
		m_sleep{ false },
		m_isDead{ false },
		m_isEmpty{ false },
		m_isCatch{ false },
		m_needRest{ false },
		m_level{Levels::CAVE},
		m_isAttack{ false },
		m_onTheRightSide{ true }
	{
	}
	void putOnMap(World& lvl);
	void moveII(Player& pl);
	void attack(Player& pl);
	void isCatch(Player& pl);
	void rest();
	void moveTo(int y_, int x_);
	void isDead() { m_isDead = true; }
	bool checkIsDead() { return m_isDead; }
	int getPosX()const { return m_posX; }
	Levels checkLevel() const { return m_level; }
private:
	enum { ZERO = 0, 
		MAX_DISTANCE = 25, 
		MAX_STAGE_OF_FLY = 4,
		MAX_STAGE_OF_ATTACK = 3,
		START_Y_1ST_STAGE_OF_ATTACK = 16,
		START_X_1ST_STAGE_OF_ATTACK = 20,
		START_Y_2ND_STAGE_OF_ATTACK = 21,
		START_X_2ND_STAGE_OF_ATTACK = 15,
	};
	int m_start_posY;
	int m_start_posX;
	int m_posY;
	int m_posX;
	int m_exp;
	int m_stage_of_fly;
	int m_stage_of_attack;
	bool m_sleep;
	bool m_isDead;
	bool m_isEmpty;
	bool m_isCatch;
	bool m_needRest;
	Levels m_level;
	bool m_isAttack;
	bool m_onTheRightSide;
};

class Spider
{
public:
	Spider(int y_, int x_) :
		m_start_posY{ y_ },
		m_start_posX{ x_ },
		m_posY{ m_start_posY },
		m_posX{ m_start_posX },
		m_exp{ 300 },
		m_stage_of_move{ 0 },
		m_stage_of_attack{ 0 },
		m_isDead{ false },
		m_isEmpty{ false },
		m_isCatch{ false },
		m_needRest{ false },
		m_isAttack{ true },
		m_onTheRightSide{ true },
		m_level{ Levels::CAVE }
	{
	}

	void putOnMap(World& lvl);

	void moveII(Player& pl);
	void attack(Player& pl);
	void rest();
	void isDead() { m_isDead = true; }
	int getPosX()const { return m_posX; }
	Levels checkLevel() const { return m_level; }
private:
	enum {
		ZERO = 0,
		MAX_STAGE_OF_MOVE = 8,
	};
	int m_start_posY;
	int m_start_posX;
	int m_posY;
	int m_posX;
	int m_exp;
	int m_stage_of_move;
	int m_stage_of_attack;
	bool m_isDead;
	bool m_isEmpty;
	bool m_isCatch;
	bool m_needRest;
	bool m_isAttack;
	bool m_onTheRightSide;
	Levels m_level;
};
//=============================================================================
void showScreen(World*, NPC*);
//=============================================================================