#include "NPC.h"

void Spider::putOnMap(World& lvl)
{
	if (m_posX > 89) m_onTheRightSide = true;
	if (m_posX < 34) m_onTheRightSide = false;
	if (!m_isEmpty)
	{
		if (m_level == lvl.whatLevelOnScreen())
		{
			//if (m_isAttack)
				//lvl.setCharInLocation(m_posY - 2, m_posX, '!');
			if (!m_isDead && m_isAttack)
			{
				if (m_onTheRightSide)
				{
					switch (m_stage_of_move)
					{
					case 0:
						lvl.setCharInLocation(m_posY - 1, m_posX - 3, '/');
						lvl.setCharInLocation(m_posY - 1, m_posX - 2, '\\');
						lvl.setCharInLocation(m_posY - 1, m_posX - 1, '\\');
						lvl.setCharInLocation(m_posY - 1, m_posX, '_');
						lvl.setCharInLocation(m_posY - 1, m_posX + 1, '/');
						lvl.setCharInLocation(m_posY - 1, m_posX + 2, '/');
						lvl.setCharInLocation(m_posY - 1, m_posX + 3, '\\');

						lvl.setCharInLocation(m_posY, m_posX - 4, '/');
						lvl.setCharInLocation(m_posY, m_posX - 3, '/');
						lvl.setCharInLocation(m_posY, m_posX - 2, '(');		//   /\\_//\   
						lvl.setCharInLocation(m_posY, m_posX - 1, ';');		//  //(;;)~\\  
						lvl.setCharInLocation(m_posY, m_posX, ';');			// //       \\  
						lvl.setCharInLocation(m_posY, m_posX + 1, ')');
						lvl.setCharInLocation(m_posY, m_posX + 2, '~');
						lvl.setCharInLocation(m_posY, m_posX + 3, '\\');
						lvl.setCharInLocation(m_posY, m_posX + 4, '\\');

						lvl.setCharInLocation(m_posY + 1, m_posX - 5, '/');
						lvl.setCharInLocation(m_posY + 1, m_posX - 4, '/');
						lvl.setCharInLocation(m_posY + 1, m_posX + 4, '\\');
						lvl.setCharInLocation(m_posY + 1, m_posX + 5, '\\');
						++m_stage_of_move;
						break;
					case 1:
						lvl.setCharInLocation(m_posY - 2, m_posX - 3, '_');

						lvl.setCharInLocation(m_posY - 1, m_posX - 4, '/');
						lvl.setCharInLocation(m_posY - 1, m_posX - 2, '\\');
						lvl.setCharInLocation(m_posY - 1, m_posX - 1, '\\');
						lvl.setCharInLocation(m_posY - 1, m_posX, '_');
						lvl.setCharInLocation(m_posY - 1, m_posX + 1, '/');
						lvl.setCharInLocation(m_posY - 1, m_posX + 2, '/');
						lvl.setCharInLocation(m_posY - 1, m_posX + 4, '\\');

						lvl.setCharInLocation(m_posY, m_posX - 5, '/');
						lvl.setCharInLocation(m_posY, m_posX - 3, '/');		//   _
						lvl.setCharInLocation(m_posY, m_posX - 2, '(');		//  / \\_//\ 
						lvl.setCharInLocation(m_posY, m_posX - 1, ';');		// / /(;;)~\\ 
						lvl.setCharInLocation(m_posY, m_posX, ';');			//  /       \\ 
						lvl.setCharInLocation(m_posY, m_posX + 1, ')');
						lvl.setCharInLocation(m_posY, m_posX + 2, '~');
						lvl.setCharInLocation(m_posY, m_posX + 3, '\\');
						lvl.setCharInLocation(m_posY, m_posX + 5, '\\');

						lvl.setCharInLocation(m_posY + 1, m_posX - 4, '/');
						lvl.setCharInLocation(m_posY + 1, m_posX + 4, '\\');
						lvl.setCharInLocation(m_posY + 1, m_posX + 5, '\\');
						++m_stage_of_move;
						m_posX -= 1;
						break;
					case 2:
						lvl.setCharInLocation(m_posY - 1, m_posX - 4, '_');
						lvl.setCharInLocation(m_posY - 1, m_posX - 3, '_');
						lvl.setCharInLocation(m_posY - 1, m_posX - 2, '/');
						lvl.setCharInLocation(m_posY - 1, m_posX - 1, '\\');
						lvl.setCharInLocation(m_posY - 1, m_posX + 1, '_');
						lvl.setCharInLocation(m_posY - 1, m_posX + 2, '/');
						lvl.setCharInLocation(m_posY - 1, m_posX + 3, '\\');
						lvl.setCharInLocation(m_posY - 1, m_posX + 4, '_');

						lvl.setCharInLocation(m_posY, m_posX - 5, '/');
						lvl.setCharInLocation(m_posY, m_posX - 2, '(');		//   __/\ _/\_  
						lvl.setCharInLocation(m_posY, m_posX - 1, ';');		//  /  (;;)~ \\ 
						lvl.setCharInLocation(m_posY, m_posX, ';');			// /  |       \\  
						lvl.setCharInLocation(m_posY, m_posX + 1, ')');
						lvl.setCharInLocation(m_posY, m_posX + 2, '~');
						lvl.setCharInLocation(m_posY, m_posX + 4, '\\');
						lvl.setCharInLocation(m_posY, m_posX + 5, '\\');

						lvl.setCharInLocation(m_posY + 1, m_posX - 6, '/');
						lvl.setCharInLocation(m_posY + 1, m_posX - 3, '|');
						lvl.setCharInLocation(m_posY + 1, m_posX + 5, '\\');
						lvl.setCharInLocation(m_posY + 1, m_posX + 6, '\\');
						++m_stage_of_move;
						m_posX -= 1;
						break;
					case 3:
						lvl.setCharInLocation(m_posY - 2, m_posX + 4, '_');
						lvl.setCharInLocation(m_posY - 2, m_posX + 3, '_');

						lvl.setCharInLocation(m_posY - 1, m_posX - 3, '/');
						lvl.setCharInLocation(m_posY - 1, m_posX - 2, '\\');
						lvl.setCharInLocation(m_posY - 1, m_posX - 1, '/');
						lvl.setCharInLocation(m_posY - 1, m_posX, '\\');
						lvl.setCharInLocation(m_posY - 1, m_posX + 1, '_');
						lvl.setCharInLocation(m_posY - 1, m_posX + 2, '/');
						lvl.setCharInLocation(m_posY - 1, m_posX + 3, '_');
						lvl.setCharInLocation(m_posY - 1, m_posX + 4, '_');
						lvl.setCharInLocation(m_posY - 1, m_posX + 5, '\\');

						lvl.setCharInLocation(m_posY, m_posX - 4, '/');		//         __  
						lvl.setCharInLocation(m_posY, m_posX - 2, '(');		//   /\/\_/__\   
						lvl.setCharInLocation(m_posY, m_posX - 1, ';');		//  / (;;)~  \   
						lvl.setCharInLocation(m_posY, m_posX, ';');			// /  \       \  
						lvl.setCharInLocation(m_posY, m_posX + 1, ')');
						lvl.setCharInLocation(m_posY, m_posX + 2, '~');
						lvl.setCharInLocation(m_posY, m_posX + 5, '\\');

						lvl.setCharInLocation(m_posY + 1, m_posX - 5, '/');
						lvl.setCharInLocation(m_posY + 1, m_posX - 2, '\\');
						lvl.setCharInLocation(m_posY + 1, m_posX + 6, '\\');
						++m_stage_of_move;
						break;
					case 4:
						lvl.setCharInLocation(m_posY - 1, m_posX - 3, '/');
						lvl.setCharInLocation(m_posY - 1, m_posX - 2, '\\');
						lvl.setCharInLocation(m_posY - 1, m_posX - 1, '/');
						lvl.setCharInLocation(m_posY - 1, m_posX, '\\');
						lvl.setCharInLocation(m_posY - 1, m_posX + 1, '_');
						lvl.setCharInLocation(m_posY - 1, m_posX + 2, '/');
						lvl.setCharInLocation(m_posY - 1, m_posX + 3, '_');
						lvl.setCharInLocation(m_posY - 1, m_posX + 4, '_');

						lvl.setCharInLocation(m_posY, m_posX - 4, '/');
						lvl.setCharInLocation(m_posY, m_posX - 2, '(');		//   /\/\_/__ 
						lvl.setCharInLocation(m_posY, m_posX - 1, ';');		//  / (;;)/  \ 
						lvl.setCharInLocation(m_posY, m_posX, ';');			// /  \  /    \ 
						lvl.setCharInLocation(m_posY, m_posX + 1, ')');
						lvl.setCharInLocation(m_posY, m_posX + 2, '/');
						lvl.setCharInLocation(m_posY, m_posX + 5, '\\');

						lvl.setCharInLocation(m_posY + 1, m_posX - 5, '/');
						lvl.setCharInLocation(m_posY + 1, m_posX - 2, '\\');
						lvl.setCharInLocation(m_posY + 1, m_posX + 1, '/');
						lvl.setCharInLocation(m_posY + 1, m_posX + 6, '\\');
						++m_stage_of_move;
						m_posX -= 1;
						break;
					case 5:
						lvl.setCharInLocation(m_posY - 2, m_posX + 2, '_');
						lvl.setCharInLocation(m_posY - 2, m_posX + 3, '_');

						lvl.setCharInLocation(m_posY - 1, m_posX - 2, '/');
						lvl.setCharInLocation(m_posY - 1, m_posX - 1, '\\');
						lvl.setCharInLocation(m_posY - 1, m_posX, '_');
						lvl.setCharInLocation(m_posY - 1, m_posX + 1, '/');
						lvl.setCharInLocation(m_posY - 1, m_posX + 2, '/');
						lvl.setCharInLocation(m_posY - 1, m_posX + 3, '\\');
						lvl.setCharInLocation(m_posY - 1, m_posX + 4, '\\');

						lvl.setCharInLocation(m_posY, m_posX - 3, '/');
						lvl.setCharInLocation(m_posY, m_posX - 2, '(');
						lvl.setCharInLocation(m_posY, m_posX - 1, ';'); 
						lvl.setCharInLocation(m_posY, m_posX, ';');			//       __
						lvl.setCharInLocation(m_posY, m_posX + 1, ')');		//   /\_//\\ 
						lvl.setCharInLocation(m_posY, m_posX + 2, '~');		//  /(;;)~/ 
						lvl.setCharInLocation(m_posY, m_posX + 3, '/');		// /  \  / 	

						lvl.setCharInLocation(m_posY + 1, m_posX - 4, '/');
						lvl.setCharInLocation(m_posY + 1, m_posX - 1, '\\');
						lvl.setCharInLocation(m_posY + 1, m_posX + 2, '/');
						++m_stage_of_move;
						m_posX -= 1;
						break;
					case 6:
						lvl.setCharInLocation(m_posY - 2, m_posX - 3, '_');
						lvl.setCharInLocation(m_posY - 2, m_posX - 2, '_');

						lvl.setCharInLocation(m_posY - 1, m_posX - 4, '/');
						lvl.setCharInLocation(m_posY - 1, m_posX - 2, '/');
						lvl.setCharInLocation(m_posY - 1, m_posX - 1, '\\');
						lvl.setCharInLocation(m_posY - 1, m_posX, '_');
						lvl.setCharInLocation(m_posY - 1, m_posX + 1, '/');
						lvl.setCharInLocation(m_posY - 1, m_posX + 2, '\\');
						lvl.setCharInLocation(m_posY - 1, m_posX + 3, '\\');

						lvl.setCharInLocation(m_posY, m_posX - 2, '(');		
						lvl.setCharInLocation(m_posY, m_posX - 1, ';');
						lvl.setCharInLocation(m_posY, m_posX, ';');			//  __ 
						lvl.setCharInLocation(m_posY, m_posX + 1, ')');		// / /\_/\\ 
						lvl.setCharInLocation(m_posY, m_posX + 2, '/');		//   (;;)/| 
						lvl.setCharInLocation(m_posY, m_posX + 3, '|');		//  |   / | 

						lvl.setCharInLocation(m_posY + 1, m_posX - 3, '|');
						lvl.setCharInLocation(m_posY + 1, m_posX + 1, '/');
						lvl.setCharInLocation(m_posY + 1, m_posX + 3, '|');
						++m_stage_of_move;
						m_posX -= 1;
						break;
					case 7:
						lvl.setCharInLocation(m_posY - 1, m_posX - 3, '/');
						lvl.setCharInLocation(m_posY - 1, m_posX - 2, '\\');
						lvl.setCharInLocation(m_posY - 1, m_posX - 1, '_');
						lvl.setCharInLocation(m_posY - 1, m_posX, '/');
						lvl.setCharInLocation(m_posY - 1, m_posX + 1, '\\');
						lvl.setCharInLocation(m_posY - 1, m_posX + 2, '\\');

						lvl.setCharInLocation(m_posY, m_posX - 4, '/');
						lvl.setCharInLocation(m_posY, m_posX - 3, '\\');
						lvl.setCharInLocation(m_posY, m_posX - 2, '(');
						lvl.setCharInLocation(m_posY, m_posX - 1, ';');		
						lvl.setCharInLocation(m_posY, m_posX, ';');			//   __\_/\\  
						lvl.setCharInLocation(m_posY, m_posX + 1, ')');		//  /\(;;)~|\ 
						lvl.setCharInLocation(m_posY, m_posX + 2, '~');		// /       || 
						lvl.setCharInLocation(m_posY, m_posX + 3, '|');
						lvl.setCharInLocation(m_posY, m_posX + 4, '\\');

						lvl.setCharInLocation(m_posY + 1, m_posX - 5, '/');
						lvl.setCharInLocation(m_posY + 1, m_posX + 3, '|');
						lvl.setCharInLocation(m_posY + 1, m_posX + 4, '|');
						m_posX -= 1;
						m_stage_of_move = 1;
						break;
					default: break;
					}
				}
				else
				{
					switch (m_stage_of_move)
					{
					case 0:
						lvl.setCharInLocation(m_posY - 1, m_posX - 3, '/');
						lvl.setCharInLocation(m_posY - 1, m_posX - 2, '\\');
						lvl.setCharInLocation(m_posY - 1, m_posX - 1, '\\');
						lvl.setCharInLocation(m_posY - 1, m_posX, '_');
						lvl.setCharInLocation(m_posY - 1, m_posX + 1, '/');
						lvl.setCharInLocation(m_posY - 1, m_posX + 2, '/');
						lvl.setCharInLocation(m_posY - 1, m_posX + 3, '\\');

						lvl.setCharInLocation(m_posY, m_posX - 4, '/');
						lvl.setCharInLocation(m_posY, m_posX - 3, '/');
						lvl.setCharInLocation(m_posY, m_posX - 2, '~');		//   /\\_//\   
						lvl.setCharInLocation(m_posY, m_posX - 1, '(');		//  //~(;;)\\  
						lvl.setCharInLocation(m_posY, m_posX, ';');			// //       \\  
						lvl.setCharInLocation(m_posY, m_posX + 1, ';');
						lvl.setCharInLocation(m_posY, m_posX + 2, ')');
						lvl.setCharInLocation(m_posY, m_posX + 3, '\\');
						lvl.setCharInLocation(m_posY, m_posX + 4, '\\');

						lvl.setCharInLocation(m_posY + 1, m_posX - 4, '/');
						lvl.setCharInLocation(m_posY + 1, m_posX - 5, '/');
						lvl.setCharInLocation(m_posY + 1, m_posX + 4, '\\');
						lvl.setCharInLocation(m_posY + 1, m_posX + 5, '\\');
						++m_stage_of_move;
						break;
					case 1:
						lvl.setCharInLocation(m_posY - 2, m_posX + 3, '_');

						lvl.setCharInLocation(m_posY - 1, m_posX - 3, '/');
						lvl.setCharInLocation(m_posY - 1, m_posX - 2, '\\');
						lvl.setCharInLocation(m_posY - 1, m_posX - 1, '\\');
						lvl.setCharInLocation(m_posY - 1, m_posX, '_');
						lvl.setCharInLocation(m_posY - 1, m_posX + 1, '/');
						lvl.setCharInLocation(m_posY - 1, m_posX + 2, '/');
						lvl.setCharInLocation(m_posY - 1, m_posX + 4, '\\');

						lvl.setCharInLocation(m_posY, m_posX - 4, '/');
						lvl.setCharInLocation(m_posY, m_posX - 3, '/');		//           _
						lvl.setCharInLocation(m_posY, m_posX - 2, '~');		//     /\\_// \   
						lvl.setCharInLocation(m_posY, m_posX - 1, '(');		//    //~(;;)\ \ 
						lvl.setCharInLocation(m_posY, m_posX, ';');			//   //       \   
						lvl.setCharInLocation(m_posY, m_posX + 1, ';');
						lvl.setCharInLocation(m_posY, m_posX + 2, ')');
						lvl.setCharInLocation(m_posY, m_posX + 3, '\\');
						lvl.setCharInLocation(m_posY, m_posX + 5, '\\');

						lvl.setCharInLocation(m_posY + 1, m_posX - 5, '/');
						lvl.setCharInLocation(m_posY + 1, m_posX - 4, '/');
						lvl.setCharInLocation(m_posY + 1, m_posX + 4, '\\');
						++m_stage_of_move;
						m_posX += 1;
						break;
					case 2:
						lvl.setCharInLocation(m_posY - 1, m_posX - 4, '_');
						lvl.setCharInLocation(m_posY - 1, m_posX - 3, '/');
						lvl.setCharInLocation(m_posY - 1, m_posX - 2, '\\');
						lvl.setCharInLocation(m_posY - 1, m_posX - 1, '_');
						lvl.setCharInLocation(m_posY - 1, m_posX + 1, '/');
						lvl.setCharInLocation(m_posY - 1, m_posX + 2, '\\');
						lvl.setCharInLocation(m_posY - 1, m_posX + 3, '_');
						lvl.setCharInLocation(m_posY - 1, m_posX + 4, '_');

						lvl.setCharInLocation(m_posY, m_posX - 5, '/');
						lvl.setCharInLocation(m_posY, m_posX - 4, '/');		//          
						lvl.setCharInLocation(m_posY, m_posX - 2, '~');		//   _/\_ /\__   
						lvl.setCharInLocation(m_posY, m_posX - 1, '(');		//  // ~(;;)  \ 
						lvl.setCharInLocation(m_posY, m_posX, ';');			// //       |  \ 
						lvl.setCharInLocation(m_posY, m_posX + 1, ';');
						lvl.setCharInLocation(m_posY, m_posX + 2, ')');
						lvl.setCharInLocation(m_posY, m_posX + 5, '\\');

						lvl.setCharInLocation(m_posY + 1, m_posX - 6, '/');
						lvl.setCharInLocation(m_posY + 1, m_posX - 5, '/');
						lvl.setCharInLocation(m_posY + 1, m_posX + 3, '|');
						lvl.setCharInLocation(m_posY + 1, m_posX + 6, '\\');
						++m_stage_of_move;
						m_posX += 1;
						break;
					case 3:
						lvl.setCharInLocation(m_posY - 2, m_posX - 4, '_');
						lvl.setCharInLocation(m_posY - 2, m_posX - 3, '_');

						lvl.setCharInLocation(m_posY - 1, m_posX - 5, '/');
						lvl.setCharInLocation(m_posY - 1, m_posX - 4, '_');
						lvl.setCharInLocation(m_posY - 1, m_posX - 3, '_');
						lvl.setCharInLocation(m_posY - 1, m_posX - 2, '\\');
						lvl.setCharInLocation(m_posY - 1, m_posX - 1, '_');
						lvl.setCharInLocation(m_posY - 1, m_posX, '/');
						lvl.setCharInLocation(m_posY - 1, m_posX + 1, '\\');
						lvl.setCharInLocation(m_posY - 1, m_posX + 2, '/');
						lvl.setCharInLocation(m_posY - 1, m_posX + 3, '\\');

						lvl.setCharInLocation(m_posY, m_posX - 5, '/');		//    __       
						lvl.setCharInLocation(m_posY, m_posX - 2, '~');		//   /__\_/\/\  
						lvl.setCharInLocation(m_posY, m_posX - 1, '(');		//   /  ~(;;) \ 
						lvl.setCharInLocation(m_posY, m_posX, ';');			//  /       /  \ 
						lvl.setCharInLocation(m_posY, m_posX + 1, ';');
						lvl.setCharInLocation(m_posY, m_posX + 2, ')');
						lvl.setCharInLocation(m_posY, m_posX + 4, '\\');

						lvl.setCharInLocation(m_posY + 1, m_posX - 6, '/');
						lvl.setCharInLocation(m_posY + 1, m_posX + 2, '/');
						lvl.setCharInLocation(m_posY + 1, m_posX + 5, '\\');
						++m_stage_of_move;
						break;
					case 4:
						lvl.setCharInLocation(m_posY - 1, m_posX - 4, '_');
						lvl.setCharInLocation(m_posY - 1, m_posX - 3, '_');
						lvl.setCharInLocation(m_posY - 1, m_posX - 2, '\\');
						lvl.setCharInLocation(m_posY - 1, m_posX - 1, '_');
						lvl.setCharInLocation(m_posY - 1, m_posX, '/');
						lvl.setCharInLocation(m_posY - 1, m_posX + 1, '\\');
						lvl.setCharInLocation(m_posY - 1, m_posX + 2, '/');
						lvl.setCharInLocation(m_posY - 1, m_posX + 3, '\\');

						lvl.setCharInLocation(m_posY, m_posX - 5, '/');
						lvl.setCharInLocation(m_posY, m_posX - 2, '\\');	//     __\_/\/\  
						lvl.setCharInLocation(m_posY, m_posX - 1, '(');		//    /  \(;;) \ 
						lvl.setCharInLocation(m_posY, m_posX, ';');			//   /    \  /  \ 
						lvl.setCharInLocation(m_posY, m_posX + 1, ';');
						lvl.setCharInLocation(m_posY, m_posX + 2, ')');
						lvl.setCharInLocation(m_posY, m_posX + 4, '\\');

						lvl.setCharInLocation(m_posY + 1, m_posX - 6, '/');
						lvl.setCharInLocation(m_posY + 1, m_posX - 1, '\\');
						lvl.setCharInLocation(m_posY + 1, m_posX + 2, '/');
						lvl.setCharInLocation(m_posY + 1, m_posX + 5, '\\');
						++m_stage_of_move;
						m_posX += 1;
						break;
					case 5:
						lvl.setCharInLocation(m_posY - 2, m_posX - 3, '_');
						lvl.setCharInLocation(m_posY - 2, m_posX - 2, '_');

						lvl.setCharInLocation(m_posY - 1, m_posX - 4, '/');
						lvl.setCharInLocation(m_posY - 1, m_posX - 3, '/');
						lvl.setCharInLocation(m_posY - 1, m_posX - 2, '\\');
						lvl.setCharInLocation(m_posY - 1, m_posX - 1, '\\');
						lvl.setCharInLocation(m_posY - 1, m_posX, '_');
						lvl.setCharInLocation(m_posY - 1, m_posX + 1, '/');
						lvl.setCharInLocation(m_posY - 1, m_posX + 2, '\\');

						lvl.setCharInLocation(m_posY, m_posX - 3, '\\'); 	//       __       
						lvl.setCharInLocation(m_posY, m_posX - 2, '~');		//      //\\_/\ 
						lvl.setCharInLocation(m_posY, m_posX - 1, '(');		//       \~(;;)\ 
						lvl.setCharInLocation(m_posY, m_posX, ';');			//        \  /  \ 
						lvl.setCharInLocation(m_posY, m_posX + 1, ';');
						lvl.setCharInLocation(m_posY, m_posX + 2, ')');
						lvl.setCharInLocation(m_posY, m_posX + 3, '\\');

						lvl.setCharInLocation(m_posY + 1, m_posX - 2, '\\');
						lvl.setCharInLocation(m_posY + 1, m_posX + 1, '/');
						lvl.setCharInLocation(m_posY + 1, m_posX + 4, '\\');
						++m_stage_of_move;
						m_posX += 1;
						break;
					case 6:
						lvl.setCharInLocation(m_posY - 2, m_posX + 2, '_');
						lvl.setCharInLocation(m_posY - 2, m_posX + 3, '_');

						lvl.setCharInLocation(m_posY - 1, m_posX - 3, '/');
						lvl.setCharInLocation(m_posY - 1, m_posX - 2, '/');
						lvl.setCharInLocation(m_posY - 1, m_posX - 1, '\\');
						lvl.setCharInLocation(m_posY - 1, m_posX, '_');
						lvl.setCharInLocation(m_posY - 1, m_posX + 1, '/');
						lvl.setCharInLocation(m_posY - 1, m_posX + 2, '\\');
						lvl.setCharInLocation(m_posY - 1, m_posX + 4, '\\');

						lvl.setCharInLocation(m_posY, m_posX - 3, '|');		//        __ 
						lvl.setCharInLocation(m_posY, m_posX - 2, '\\');	//   //\_/\ \  
						lvl.setCharInLocation(m_posY, m_posX - 1, '(');		//   |\(;;)    
						lvl.setCharInLocation(m_posY, m_posX, ';');			//   | \   |    
						lvl.setCharInLocation(m_posY, m_posX + 1, ';');
						lvl.setCharInLocation(m_posY, m_posX + 2, ')');

						lvl.setCharInLocation(m_posY + 1, m_posX - 3, '|');
						lvl.setCharInLocation(m_posY + 1, m_posX - 1, '\\');
						lvl.setCharInLocation(m_posY + 1, m_posX + 3, '|');
						++m_stage_of_move;
						m_posX += 1;
						break;
					case 7:
						lvl.setCharInLocation(m_posY - 1, m_posX - 2, '/');
						lvl.setCharInLocation(m_posY - 1, m_posX - 1, '/');
						lvl.setCharInLocation(m_posY - 1, m_posX, '\\');
						lvl.setCharInLocation(m_posY - 1, m_posX + 1, '_');
						lvl.setCharInLocation(m_posY - 1, m_posX + 2, '/');
						lvl.setCharInLocation(m_posY - 1, m_posX + 3, '\\');

						lvl.setCharInLocation(m_posY, m_posX - 4, '/');
						lvl.setCharInLocation(m_posY, m_posX - 3, '|');
						lvl.setCharInLocation(m_posY, m_posX - 2, '~');		//    //\_/__  
						lvl.setCharInLocation(m_posY, m_posX - 1, '(');		//   /|~(;;)/\   
						lvl.setCharInLocation(m_posY, m_posX, ';');			//   ||       \   
						lvl.setCharInLocation(m_posY, m_posX + 1, ';');
						lvl.setCharInLocation(m_posY, m_posX + 2, ')');
						lvl.setCharInLocation(m_posY, m_posX + 3, '/');
						lvl.setCharInLocation(m_posY, m_posX + 4, '\\');

						lvl.setCharInLocation(m_posY + 1, m_posX - 4, '|');
						lvl.setCharInLocation(m_posY + 1, m_posX - 3, '|');
						lvl.setCharInLocation(m_posY + 1, m_posX + 5, '\\');
						m_posX += 1;
						m_stage_of_move = 1;
						break;
					default: break;
					}
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

void Spider::moveII(Player& pl)
{

}

void Spider::attack(Player& pl)
{

}

void Spider::rest()
{

}