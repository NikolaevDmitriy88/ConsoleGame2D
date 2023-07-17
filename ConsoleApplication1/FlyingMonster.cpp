#include "NPC.h"
void FlyingMonster::putOnMap(World& lvl)
{
	if (!m_isEmpty)
	{
		if (m_level == lvl.whatLevelOnScreen())
		{
			//if (m_isAttack)
				//lvl.setCharInLocation(m_posY - 2, m_posX, '!');
			if (!m_isDead)
			{
				switch (m_stage_of_fly)
				{
				case 0:
					lvl.setCharInLocation(m_posY + 1, m_posX - 1, '\"');
					lvl.setCharInLocation(m_posY + 1, m_posX + 1, '\"');
					lvl.setCharInLocation(m_posY - 1, m_posX - 3, '^');
					lvl.setCharInLocation(m_posY - 1, m_posX + 3, '^');
					lvl.setCharInLocation(m_posY - 1, m_posX - 2, '\\');
					lvl.setCharInLocation(m_posY - 1, m_posX + 2, '/');	// ^\   /^
					lvl.setCharInLocation(m_posY, m_posX - 1, '\\');	//   \@/
					lvl.setCharInLocation(m_posY, m_posX, '@');			//   " "
					lvl.setCharInLocation(m_posY, m_posX + 1, '/');
					++m_posY;
					break;
				case 1:
					lvl.setCharInLocation(m_posY + 1, m_posX - 1, '\"');
					lvl.setCharInLocation(m_posY + 1, m_posX + 1, '\"');
					lvl.setCharInLocation(m_posY - 1, m_posX - 3, '\\');
					lvl.setCharInLocation(m_posY - 1, m_posX + 3, '/');
					lvl.setCharInLocation(m_posY - 1, m_posX - 2, '_');
					lvl.setCharInLocation(m_posY - 1, m_posX + 2, '_'); // \_   _/ 
					lvl.setCharInLocation(m_posY, m_posX - 1, '\\');	//   \@/   
					lvl.setCharInLocation(m_posY, m_posX, '@');			//   " "   
					lvl.setCharInLocation(m_posY, m_posX + 1, '/');
					break;
				case 2:
					lvl.setCharInLocation(m_posY + 1, m_posX - 1, '\"');
					lvl.setCharInLocation(m_posY + 1, m_posX + 1, '\"');
					lvl.setCharInLocation(m_posY, m_posX - 3, '\\');
					lvl.setCharInLocation(m_posY, m_posX + 3, '/');
					lvl.setCharInLocation(m_posY, m_posX - 2, '_');
					lvl.setCharInLocation(m_posY, m_posX + 2, '_');
					lvl.setCharInLocation(m_posY, m_posX - 1, '_');	 // \__@__/ 
					lvl.setCharInLocation(m_posY, m_posX, '@');		 //   " "   
					lvl.setCharInLocation(m_posY, m_posX + 1, '_');
					++m_posY;
					break;
				case 3:
					lvl.setCharInLocation(m_posY + 1, m_posX - 1, '\"');
					lvl.setCharInLocation(m_posY + 1, m_posX + 1, '\"');
					lvl.setCharInLocation(m_posY, m_posX - 1, '/');	 //   /@\   
					lvl.setCharInLocation(m_posY, m_posX, '@');		 // _/" "\_ 
					lvl.setCharInLocation(m_posY, m_posX + 1, '\\');
					lvl.setCharInLocation(m_posY + 1, m_posX - 2, '/');
					lvl.setCharInLocation(m_posY + 1, m_posX + 2, '\\');
					lvl.setCharInLocation(m_posY + 1, m_posX - 3, '_');
					lvl.setCharInLocation(m_posY + 1, m_posX + 3, '_');
					m_posY -= 2;
					break;
				case 4:
					lvl.setCharInLocation(m_posY + 1, m_posX - 1, '\"');
					lvl.setCharInLocation(m_posY + 1, m_posX + 1, '\"');
					lvl.setCharInLocation(m_posY, m_posX - 1, '-');	 //  _-@-_  
					lvl.setCharInLocation(m_posY, m_posX, '@');		 // / " " \ 
					lvl.setCharInLocation(m_posY, m_posX + 1, '-');
					lvl.setCharInLocation(m_posY, m_posX - 2, '_');
					lvl.setCharInLocation(m_posY, m_posX + 2, '_');
					lvl.setCharInLocation(m_posY + 1, m_posX - 3, '/');
					lvl.setCharInLocation(m_posY + 1, m_posX + 3, '\\');
					break;
				default: break;
				}
			}
			if (m_isDead)
			{
				m_posY < 23 ? ++m_posY : m_posY = 23;
				m_isAttack = false;
				lvl.setCharInLocation(m_posY + 1, m_posX - 2, '}');
				lvl.setCharInLocation(m_posY + 1, m_posX - 1, '@');	 // }@^\\ 
				lvl.setCharInLocation(m_posY + 1, m_posX, '^');		 //    
				lvl.setCharInLocation(m_posY + 1, m_posX + 1, '\\');
				lvl.setCharInLocation(m_posY + 1, m_posX + 2, '\\');
			}
		}
	}
}

void FlyingMonster::moveII(Player& pl)
{
	if (!m_isDead)
	{
		(m_stage_of_fly < MAX_STAGE_OF_FLY) ? ++m_stage_of_fly : m_stage_of_fly = ZERO;
		if (!m_needRest && !m_isCatch && !pl.checkIsDead()
			&& m_level == pl.checkLevel())
		{
			if (!m_stage_of_attack)
			{
				int temp_posY = m_posY - pl.getPosY();
				int temp_posX = m_posX - pl.getPosX();
				pl.getPosX() < m_start_posX ? m_onTheRightSide = true : m_onTheRightSide = false;
				int temp_distance = (int)sqrt((temp_posX * temp_posX) + (temp_posY * temp_posY));
				temp_distance < MAX_DISTANCE ? m_isAttack = true : m_isAttack = false;
				if (m_isAttack)
				{
					m_stage_of_attack = MAX_STAGE_OF_ATTACK;
					attack(pl);
				}
			}
			else attack(pl);
		}
		else if (m_isCatch && !pl.checkIsDead())
		{
			pl.setPosY(m_posY);
			if (m_posY > 6)
				--m_posY;
			else
				isCatch(pl);
		}
		else
			rest();
	}
	else
	{
		if (m_exp)
		{
			pl.setExp(m_exp);
			m_exp = 0;
		}
	}
}

void FlyingMonster::attack(Player& pl)
{
	if (!m_isCatch && !pl.checkIsDead() && pl.getPosX() < 94)
	{
		int temp_posX;
		switch (m_stage_of_attack)
		{
		case 3:
			(m_onTheRightSide)
				? temp_posX = pl.getPosX() + START_X_1ST_STAGE_OF_ATTACK
				: temp_posX = pl.getPosX() - START_X_1ST_STAGE_OF_ATTACK;
			moveTo(START_Y_1ST_STAGE_OF_ATTACK, temp_posX);
			if (m_posY == START_Y_1ST_STAGE_OF_ATTACK
				&& (m_posX < temp_posX + 2 && m_posX > temp_posX - 2))
				--m_stage_of_attack;
			break;
		case 2:
			(m_onTheRightSide)
				? temp_posX = pl.getPosX() + START_X_2ND_STAGE_OF_ATTACK
				: temp_posX = pl.getPosX() - START_X_2ND_STAGE_OF_ATTACK;
			moveTo(START_Y_2ND_STAGE_OF_ATTACK, temp_posX);
			if (m_posY == START_Y_2ND_STAGE_OF_ATTACK
				&& (m_posX < temp_posX + 2 && m_posX > temp_posX - 2))
				--m_stage_of_attack;
			break;
		case 1:
			temp_posX = m_posX - pl.getPosX();
			if (abs(temp_posX) > 2)
			{
				if (m_onTheRightSide)
				{
					(temp_posX > 2) ? m_posX -= 3 : ++m_posX;
				}
				else
				{
					(abs(temp_posX) > 2) ? m_posX += 3 : --m_posX;
				}
			}
			else
			{
				--m_stage_of_attack;
				m_posY = 22;
				if (!pl.checkBlock()
					|| (pl.checkBlock() && (pl.checkDirection() != m_onTheRightSide)))
				{
					m_isAttack = false;
					pl.liftUp();
					m_posX = pl.getPosX();
					m_isCatch = true;
					//	isCatch(pl);
				}
			}
		default:
			break;
		}
	}
	else
		rest();
}

void FlyingMonster::moveTo(int y_, int x_)
{
	if (m_posY != y_)
	{
		if (m_posY > y_ + 2)
		{
			m_posY -= 3;
		}
		else if (m_posY == y_ + 2)
		{
			m_posY -= 2;
		}
		else if (m_posY == y_ + 1)
		{
			--m_posY;
		}
		else if (m_posY < y_)
		{
			++m_posY;
		}
	}
	if (m_posX != x_)
	{
		if (m_posX > x_ + 2)
		{
			m_posX -= 3;
		}
		else if (m_posX == x_ + 2)
		{
			m_posX -= 2;
		}
		else if (m_posX == x_ + 1)
		{
			--m_posX;
		}
		else if (m_posX < x_ - 2)
		{
			m_posX += 3;
		}
		else if (m_posX == x_ - 2)
		{
			m_posX += 2;
		}
		else if (m_posX == x_ - 1)
		{
			++m_posX;
		}
	}
}

void FlyingMonster::isCatch(Player& pl)
{
	m_isCatch = false;
	pl.setDirection();
	pl.fall();
	m_needRest = true;
	--m_posY;
}

void FlyingMonster::rest()
{
	m_stage_of_attack = 0;
	m_needRest = true;
	if (m_needRest)
	{
		if (m_posY == m_start_posY && m_posX == m_start_posX)
			m_needRest = false;
		else
			moveTo(m_start_posY, m_start_posX);
	}
}