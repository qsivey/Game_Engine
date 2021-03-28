/* This library is a complete mini-game engine. All game variables and
 * function prototypes are declared in "game.h" library.
 * The program does not use interrupts, does not work with timers or DMA.
 * Designed for educational and entertainment purposes only.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * 	1) The ReadFromADC() function is configured by default and reads the
 * X and Y values from the joystick. The button press is processed in the
 * ButtonHandler() function.
 * 	2) The calibration values in the JoystickMoveHandler () function can
 * be changed depending on the connected joystick. I used Amperka 3D
 * joystick.
 * 	3) The condition in the 307 line of code disables burst firing.
 * Erase it to enable this mode.
 *  4) If you are using a high resolution screen, it is better to use the
 * _Erase function for each object instead of erasing the entire screen.
 *  5) The values that change the score in _GameEngineColissionHandler()
 * function can be changed at your discretion.
 *  6) All delay() functions can be remade for internal timer.
 *  7) The rand() functions can be changed to the RNG() function of the
 * microcontroller.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "game.h"

// ========================= HARDWARE FUNCTIONS =========================

u16 ReadFromADC(u8 ADC_Channel)
{
	u16 value = 0;

	if (ADC_Channel == 1)
	{
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1, 100);
		value = HAL_ADC_GetValue(&hadc1);
		HAL_ADC_Stop(&hadc1);
	}

	else if (ADC_Channel == 2)
	{
		HAL_ADC_Start(&hadc3);
		HAL_ADC_PollForConversion(&hadc3, 100);
		value = HAL_ADC_GetValue(&hadc3);
		HAL_ADC_Stop(&hadc3);
	}

	return value;
}

// ====================== PROCESSING FUNCTIONS =========================

_USERBUTT ButtonHandler (void)
{
	if (HAL_GPIO_ReadPin(JOY_BUT_GPIO_Port, JOY_BUT_Pin))
		return ON;
	else
		return OFF;
}

void _GameEngineBulletInit ( _GameObject* objStarship, _GameObject* objBullet)
{
	objBullet[objStarship->bulletCount].speed = BULLET_SPEED;
	objBullet[objStarship->bulletCount].app = APPEAR;
	objBullet[objStarship->bulletCount].x_cor = objStarship->x_cor + SPRITE16;
	objBullet[objStarship->bulletCount].y_cor = objStarship->y_cor + SPRITE8 - 1;
}

void _GameEngineBossBulletInit (_GameObject* objBoss, _GameObject* objBossBullet)
{
	objBossBullet[objBoss->bulletCount].speed = BOSS_BULLET_SPEED * (objBoss->type - 1);

	if (objBoss->lvl == 9 || objBoss->lvl == 10)
		objBossBullet[objBoss->bulletCount].speed = BOSS_BULLET_SPEED * 3;

	objBossBullet[objBoss->bulletCount].app = APPEAR;
	objBossBullet[objBoss->bulletCount].x_cor = objBoss->x_cor - 2;

	if (objBoss->lvl != 10)
		objBossBullet[objBoss->bulletCount].y_cor = objBoss->y_cor + (objBoss->type * SPRITE8 / 2) - 1;

	else
		objBossBullet[objBoss->bulletCount].y_cor = objBoss->y_cor + (rand() % objBoss->type * SPRITE8);
}

void _GameEngineBossInit (_GameFeature* game, _GameObject* objStarship, _GameObject* objBoss)
{
	objBoss->app = APPEAR;
	objBoss->lvl++;
	objBoss->hitPoints = BOSS_HP * GAME_DIFFICULTY + (objBoss->lvl * BOSS_LVL_HP_ADD);
	objBoss->speed = round ((objBoss->lvl / 2) * BOSS_SPEED);

	if (objBoss->lvl == 1)
		objBoss->speed = BOSS_SPEED;

	objBoss->dir = DIR_UP;

	objBoss->x_cor = DISPLAY_WIDTH - 1;

	if (objBoss->lvl <= 3)
	{
		objBoss->type = BOSS_16;
		objBoss->y_cor = (DISPLAY_HEIGHT / 2) - SPRITE8;
	}

	else if (objBoss->lvl >= 4 && objBoss->lvl <= 6)
	{
		objBoss->type = BOSS_24;
		objBoss->y_cor = (DISPLAY_HEIGHT / 2) - (SPRITE8 + 4);
	}

	else if (objBoss->lvl >= 7 && objBoss->lvl <= 8)
	{
		objBoss->type = BOSS_32;
		objBoss->y_cor = (DISPLAY_HEIGHT / 2) - SPRITE16;
	}

	else if (objBoss->lvl == 9)
	{
		objBoss->type = BOSS_8;
		objBoss->y_cor = (DISPLAY_HEIGHT / 2) - SPRITE8 / 2;
	}

	else
	{
		objBoss->type = BOSS_64;
		objBoss->y_cor = (DISPLAY_HEIGHT / 2) - SPRITE32;
	}

	_GameEngineBossAppear(game, objStarship, objBoss);

	game->gameState = BOSS_PASS;
}

void _GameEngineBossAppear (_GameFeature* game, _GameObject* objStarship, _GameObject* objBoss)
{
	u8 boss_10_LVL_Dummy = 1;

	if (objBoss->lvl == 10)
		boss_10_LVL_Dummy = 2;

	_GameEngineScoreDraw(game, objStarship);
	_GameEngineStarshipDraw(objStarship);

	delay(100);

	ssd1306_DrawRectangle (UI_BOSS_HP_X, UI_BOSS_HP_Y, UI_BOSS_HP_X + 34, UI_BOSS_HP_Y + 7, 1);

	while (objBoss->x_cor > DISPLAY_WIDTH - (objBoss->type / boss_10_LVL_Dummy * SPRITE8) - BOSS_X_POS_OFFSET)
	{
		objBoss->x_old_cor = objBoss->x_cor;
		objBoss->y_old_cor = objBoss->y_cor;

		objBoss->x_cor--;

		_GameEngineBossErase(objBoss);
		_GameEngineBossDraw(objBoss);

		ssd1306_UpdateScreen();

		delay(20);
	}

	for (u16 i = 0; i <= 30; i++)
	{
		ssd1306_Line(UI_BOSS_HP_X + 2 + i, UI_BOSS_HP_Y + 2, UI_BOSS_HP_X + 2 + i, UI_BOSS_HP_Y + 5, 1);

		ssd1306_UpdateScreen();

		delay(15);
	}
}

_MOVE JoystickMoveHandler (void)
{
	// ADC HANDLER ============

	uint16_t adcValue_X = (ReadFromADC(1) + ReadFromADC(1) + ReadFromADC(1) + ReadFromADC(1) + ReadFromADC(1)) / 5;
	uint16_t adcValue_Y = (ReadFromADC(2) + ReadFromADC(2) + ReadFromADC(2) + ReadFromADC(2) + ReadFromADC(2)) / 5;

	_MOVE move;

	move = MOVE_NONE;

	if (adcValue_Y > 3895 && adcValue_X < 3548 && adcValue_X > 548)
		move = MOVE_UP;

	else if (adcValue_Y > 2848 && adcValue_X > 2748)
		move = MOVE_UP_RIGHT;

	else if (adcValue_Y > 2848 && adcValue_X < 1348)
		move = MOVE_UP_LEFT;

	// ===============================================================

	else if (adcValue_X > 3895 && adcValue_Y < 3548 && adcValue_Y > 548)
		move = MOVE_RIGHT;

	// ===============================================================

	else if (adcValue_Y < 200 && adcValue_X < 3548 && adcValue_X > 548)
			move = MOVE_DOWN;

	else if (adcValue_Y < 1348 && adcValue_X > 2748)
		move = MOVE_DOWN_RIGHT;

	else if (adcValue_Y < 1348 && adcValue_X < 1348)
		move = MOVE_DOWN_LEFT;

	// ===============================================================

	else if (adcValue_X < 200 && adcValue_Y < 3548 && adcValue_Y > 548)
		move = MOVE_LEFT;

	// ===============================================================

	else
		move = MOVE_NONE;

	return move;
}

void _GameEngineJoystickHandler (_MOVE userMove, _GameFeature* game, _GameObject* objStarship, _GameObject* objBullet, _GameObject* objBoss)
{
	if (!ButtonHandler())
		objStarship->shotApply = OFF;

	u8 x_cor_wall = 0;

	if (game->gameState == BOSS_PASS)
		x_cor_wall = objBoss->type * SPRITE8 + 5;

	objStarship->x_old_cor = objStarship->x_cor;
	objStarship->y_old_cor = objStarship->y_cor;

	switch (userMove)
	{
		case MOVE_UP:
		{
			if (objStarship->y_cor > 2)
				objStarship->y_cor -= STARSHIP_SPEED;
			break;
		}

		case MOVE_UP_RIGHT:
		{
			if (objStarship->y_cor > 2 && objStarship->x_cor < DISPLAY_WIDTH - 1 - SPRITE16 - x_cor_wall)
			{
				objStarship->y_cor -= STARSHIP_SPEED;
				objStarship->x_cor += STARSHIP_SPEED;
			}
			break;
		}

		case MOVE_UP_LEFT:
		{
			if (objStarship->y_cor > 2 && objStarship->x_cor > 1)
			{
				objStarship->y_cor -= STARSHIP_SPEED;
				objStarship->x_cor -= STARSHIP_SPEED;
			}
			break;
		}

		// ========================================================

		case MOVE_DOWN:
		{
			if (objStarship->y_cor < DISPLAY_HEIGHT - 1 - SPRITE16)
				objStarship->y_cor += STARSHIP_SPEED;
			break;
		}

		case MOVE_DOWN_RIGHT:
		{
			if (objStarship->y_cor < DISPLAY_HEIGHT - 1 - SPRITE16 && objStarship->x_cor < DISPLAY_WIDTH - 1 - SPRITE16 - x_cor_wall)
			{
				objStarship->y_cor += STARSHIP_SPEED;
				objStarship->x_cor += STARSHIP_SPEED;
			}
			break;
		}

		case MOVE_DOWN_LEFT:
		{
			if (objStarship->y_cor < DISPLAY_HEIGHT - 1 - SPRITE16 && objStarship->x_cor > 1)
			{
				objStarship->y_cor += STARSHIP_SPEED;
				objStarship->x_cor -= STARSHIP_SPEED;
			}
			break;
		}

		// ========================================================

		case MOVE_RIGHT:
		{
			if (objStarship->x_cor < DISPLAY_WIDTH - 1 - SPRITE16 - x_cor_wall)
				objStarship->x_cor += STARSHIP_SPEED;
			break;
		}

		case MOVE_LEFT:
		{
			if (objStarship->x_cor > 1)
				objStarship->x_cor -= STARSHIP_SPEED;
			break;
		}

		case MOVE_NONE:
		{
			break;
		}
	}

	if (objStarship->shotApply == OFF)		// *3
	{
		if (ButtonHandler() == ON)
		{
			if (objBullet[objStarship->bulletCount].app == DISAPPEAR)
			{
				_GameEngineBulletInit(objStarship, objBullet);
				objStarship->bulletCount++;
				objStarship->shotApply = ON;
			}
		}
	}

	if (objStarship->shield > 0)
		objStarship->shield--;

	if (objStarship->bulletCount > BULLET_QUANTITY - 1)
		objStarship->bulletCount = 0;
}

void _GameEngineBulletsHandler (_GameObject* objBullet)
{
	for (u8 i = 0; i < BULLET_QUANTITY; i++)
	{
		if (objBullet[i].app == APPEAR)
		{
			objBullet[i].x_old_cor = objBullet[i].x_cor;
			objBullet[i].x_cor += objBullet[i].speed;

			if (objBullet[i].x_cor > (DISPLAY_WIDTH - objBullet[i].speed))
				objBullet[i].app = DISAPPEAR;
		}
		else
			;
	}
}

void _GameEngineEnemyesHandler (_GameFeature* game, _GameObject* objEnemy)
{
	for (u8 i = 0; i < ENEMY_MAX_QANT + game->gameLVL; i++)
	{
		if (objEnemy[i].app == DISAPPEAR)
			if (!(rand() % ENEMY_APPEAR_PROBABILITY))
			{
				objEnemy[i].app = APPEAR;
				objEnemy[i].speed = ENEMY_SPEED + 1 - (rand() % 3);
				objEnemy[i].x_cor = DISPLAY_WIDTH - 1;
				objEnemy[i].y_cor = rand() % (DISPLAY_HEIGHT - SPRITE8 - 1);
			}

			else
				;
		else
		{
			objEnemy[i].x_cor -= objEnemy[i].speed;
			if (objEnemy[i].x_cor < 1 - SPRITE8)
			{
				objEnemy[i].app = DISAPPEAR;
				game->score -= ENEMY_KILL_SCORE * (ENEMY_SPEED + 2 - objEnemy[i].speed) * 25;
			}
		}

		if (objEnemy[i].app == EXPLOSION)
			objEnemy[i].app = DISAPPEAR;
	}
}

void _GameEngineCareHandler (_GameObject* objCare)
{
	if (objCare->app == DISAPPEAR)
		if (!(rand() % CARE_APPEAR_PROBABILITY))
		{
			objCare->app = APPEAR;
			objCare->speed = CARE_SPEED;
			objCare->x_cor = DISPLAY_WIDTH - 1;
			objCare->y_cor = rand() % (DISPLAY_HEIGHT - 1 - SPRITE8);
		}

		else
			;
	else
	{
		objCare->x_cor -= objCare->speed;
		if (objCare->x_cor < 1 - SPRITE8)
			objCare->app = DISAPPEAR;
	}
}

void _GameEngineBossHandler (_GameFeature* game, _GameObject* objStarship, _GameObject* objBullet, _GameObject* objEnemy, _GameObject* objCare, _GameObject* objBoss, _GameObject* objBossBullet)
{
	if (game->gameState == BOSS_PASS && objBoss->initState == 0)
	{
		_GameEngineBossInit(game, objStarship, objBoss);
		objBoss->initState = 1;
	}

	if (objBoss->hitPoints < 0)		// New LVL Pre-Init
	{
		if (game->gameLVL == 10)
			game->gameState = VICTORY;

		else
		{
			objBoss->app = DISAPPEAR;
			game->gameLVL++;
			game->gameState = LVL_PASS;

			for (u8 i = 0; i < BULLET_QUANTITY; i++)
				objBullet[i].app = DISAPPEAR;

			for (u8 i = 0; i < ENEMY_MAX_QANT + game->gameLVL; i++)
				objEnemy[i].app = DISAPPEAR;

			for (u8 i = 0; i < BOSS_BULLET_QUANTITY; i++)
				objBossBullet[i].app = DISAPPEAR;

			objCare->app = DISAPPEAR;

			objBoss->app = DISAPPEAR;
			objBoss->initState = 0;

			game->score += 15000;
		}
	}

	// =========================== BOSS MOVIES ===========================

	if (objBoss->lvl == 10 && DISPLAY_HEIGHT == 64)
		;

	else
	{
		if (objBoss->dir == DIR_UP && objBoss->y_cor < objBoss->speed)
			objBoss->dir = DIR_DOWN;

		else if (objBoss->dir == DIR_DOWN && objBoss->y_cor > DISPLAY_HEIGHT - objBoss->speed - (objBoss->type * SPRITE8))
				objBoss->dir = DIR_UP;

		if (objBoss->dir == DIR_UP)
			objBoss->y_cor -= objBoss->speed;

		else if (objBoss->dir == DIR_DOWN)
			objBoss->y_cor += objBoss->speed;
	}


	// ========================== BOSS SHOOTING ==========================

	if (!(rand() % (BOSS_SHOOT_PROBABILITY - (objBoss->lvl * ((BOSS_SHOOT_PROBABILITY / 10) - 1)))))
	{
		_GameEngineBossBulletInit(objBoss, objBossBullet);
		++objBoss->bulletCount;
	}

	if (objBoss->bulletCount > BOSS_BULLET_QUANTITY - 1)
		objBoss->bulletCount = 0;
}

void _GameEngineBossBulletsHandler (_GameObject* objBossBullet)
{
	for (u8 i = 0; i < BOSS_BULLET_QUANTITY; i++)
	{
		if (objBossBullet[i].app == APPEAR)
		{
			objBossBullet[i].x_old_cor = objBossBullet[i].x_cor;
			objBossBullet[i].x_cor -= objBossBullet[i].speed;

			if (objBossBullet[i].x_cor < objBossBullet[i].speed)
				objBossBullet[i].app = DISAPPEAR;
		}
		else
			;
	}
}

void _GameEngineColissionHandler (_GameFeature* game, _GameObject* objStarship, _GameObject* objBullet, _GameObject* objEnemy, _GameObject* objCare, _GameObject* objBoss, _GameObject* objBossBullet)
{
	objStarship->wound = NORMAL;
	objBoss->wound = NORMAL;

	u8 boss_10_LVL_Dummy = 1;

	if (objBoss->lvl == 10)
		boss_10_LVL_Dummy = 2;

	if (game->gameState == LVL_PASS)
	{
		for (u8 i = 0; i < ENEMY_MAX_QANT  + game->gameLVL; i++)
		{
			for (u8 k = 0; k < BULLET_QUANTITY; k++) 																							// BULLET & ENEMYES COLLISION
			{
				if (objEnemy[i].app == APPEAR && objBullet[k].app == APPEAR)																	// **************************
				{
					if (objEnemy[i].x_cor - objBullet[k].x_cor < 1)																				// **************************
					{
						if ((objEnemy[i].y_cor - 2 <= objBullet[k].y_cor) && (objEnemy[i].y_cor + SPRITE8 >= objBullet[k].y_cor))				// **************************
						{
							objEnemy[i].app = EXPLOSION;																						// **************************
							objBullet[k].app = DISAPPEAR;
																																				// **************************
							game->score += (ENEMY_KILL_SCORE * objEnemy[i].speed * (objEnemy[i].x_cor + objEnemy[i].speed));
						}																														// **************************

						else
							;
					}

					else
						;
				}
			}

			if (objEnemy[i].app == APPEAR)																										// ENEMYES & STARSHIP COLLISION
			{
				if(objEnemy[i].x_cor - objStarship->x_cor - SPRITE16 < objEnemy[i].speed && objStarship->x_cor - objEnemy[i].x_cor < SPRITE8)	// ****************************
				{
					if (objStarship->y_cor - objEnemy[i].y_cor < SPRITE8 && objEnemy[i].y_cor - objStarship->y_cor < SPRITE16)					// ****************************
					{
						objEnemy[i].app = EXPLOSION;																							// ****************************

						if (!(objStarship->shield))																								// ****************************
						{
							objStarship->wound = WOUNDED;																						// ****************************
							--objStarship->hitPoints;
							game->score -= ENEMY_KILL_SCORE * (ENEMY_SPEED + 2 - objEnemy[i].speed) * 100;										// ****************************

							objStarship->shield = STARSHIP_SHIELD;																				// ****************************
						}
																																				// ****************************
						else
							game->score += (ENEMY_KILL_COLLISION_SCORE * objEnemy[i].speed * (objEnemy[i].x_cor + objEnemy[i].speed));			// ****************************
					}
				}
			}
		}

		if (objCare->app == APPEAR)																												// STARSHIP & CARE COLLISION
		{
			if(objCare->x_cor - objStarship->x_cor - SPRITE16 < CARE_SPEED && objStarship->x_cor - objCare->x_cor < SPRITE8)					// *************************
			{
				if (objStarship->y_cor - objCare->y_cor < SPRITE8 && objCare->y_cor - objStarship->y_cor < SPRITE16)							// *************************
				{
					objCare->app = DISAPPEAR;																									// *************************
					game->score += CARE_COLLISION_SCORE;
					objStarship->shield = STARSHIP_SHIELD;																						// *************************
					if (objStarship->hitPoints < STARSHIP_MAX_HP)
						objStarship->hitPoints++;																								// *************************
				}
			}																																	// *************************
		}
	}

	else if(game->gameState == BOSS_PASS)																										// BOSS BULLET & BULLET COLLISION
	{
		for (u8 i = 0; i < BULLET_QUANTITY; i++)																								// ******************************
		{
			for (u8 k = 0; k < BOSS_BULLET_QUANTITY; k++)																						// ******************************
			{
				if (objBullet[i].app == APPEAR && objBossBullet[k].app == APPEAR)																// ******************************
				{
					if (objBossBullet[k].x_cor - objBullet[i].x_cor < objBullet[i].speed + objBossBullet[k].speed)								// ******************************
					{
						if ((objBullet[i].y_cor - 2 <= objBossBullet[k].y_cor) && (objBullet[i].y_cor + 3 >= objBossBullet[k].y_cor))			// ******************************
						{
							objBullet[i].app = DISAPPEAR;																						// ******************************
							objBossBullet[k].app = DISAPPEAR;
																																				// ******************************
							game->score += (ENEMY_KILL_SCORE * objBossBullet[k].speed);
						}																														// ******************************

						else
							;
					}

					else
						;
				}
			}
		}

		for (u8 i = 0; i < BULLET_QUANTITY; i++)																								// SH BULLET & BOSS COLLISION
		{
			if (objBullet[i].app == APPEAR)																										// **************************
			{
				if (objBullet[i].x_cor >= DISPLAY_WIDTH - (objBoss->type / boss_10_LVL_Dummy * SPRITE8))										// **************************
				{
					if ((objBoss->y_cor - 2 <= objBullet[i].y_cor) && (objBoss->y_cor + (objBoss->type * SPRITE8) >= objBullet[i].y_cor))		// **************************
					{
						objBoss->wound = WOUNDED;																								// **************************
						objBullet[i].app = DISAPPEAR;
						objBoss->hitPoints -= BULLET_POWER;																						// **************************
						game->score += (BOSS_HIT_SCORE * BULLET_POWER);
					}																															// **************************
				}
			}
		}

		for (u8 i = 0; i < BOSS_BULLET_QUANTITY; i++)																							// BOSS BULLET & SH COLLISION
		{
			if (objBossBullet[i].app == APPEAR)																									// **************************
			{
				if (objBossBullet[i].x_cor - objStarship->x_cor - SPRITE16 < objBossBullet[i].speed)											// **************************
				{
					if (objStarship->y_cor - objBossBullet[i].y_cor < 3 && objBossBullet[i].y_cor - objStarship->y_cor < SPRITE16)				// **************************
					{
						objBossBullet[i].app = DISAPPEAR;																						// **************************

						if (!(objStarship->shield))																								// **************************
						{
							objStarship->wound = WOUNDED;																						// **************************
							--objStarship->hitPoints;
							game->score -= objBoss->lvl * ENEMY_KILL_COLLISION_SCORE * 10;														// **************************

							objStarship->shield = STARSHIP_SHIELD;																				// **************************
						}

						else
							;
					}
				}
			}
		}
	}
}

void _GameEngineScoreHandler (_GameFeature* game)
{
	if (game->score < 0)
		game->score = 0;

	else if (game->score > GAME_DIFFICULTY * GAME_LVL_PASS_SCORE * game->gameLVL)
		if (game->gameState != BOSS_PASS)
			game->gameState = BOSS_PASS;
}

void _GameEngineLifeHandler (_GameFeature* game, _GameObject* objStarship)
{
	if (objStarship->hitPoints < 1)
		game->gameState = GAME_OVER;
		//objStarship->hitPoints = 1;		// Cheat ON :)
}

// ========================= DRAW FUNCTIONS =========================

void _GameEngineStarshipDraw (_GameObject* objStarship)
{
	if(objStarship->shield)
		ssd1306_DrawSprite16x16(objStarship->x_cor, objStarship->y_cor, GUI_STARSHIP_WSH_DRAW, 1);
	else
		ssd1306_DrawSprite16x16(objStarship->x_cor, objStarship->y_cor, GUI_STARSHIP_DRAW, 1);
}

void _GameEngineBulletsDraw (_GameObject* objBullet)
{
	for (u8 i = 0; i < BULLET_QUANTITY; i++)
	{
		if (objBullet[i].app == APPEAR)
		{
			ssd1306_DrawPixel(objBullet[i].x_cor, objBullet[i].y_cor, 1);
			ssd1306_DrawPixel(objBullet[i].x_cor + 1, objBullet[i].y_cor, 1);
			ssd1306_DrawPixel(objBullet[i].x_cor, objBullet[i].y_cor + 1, 1);
			ssd1306_DrawPixel(objBullet[i].x_cor + 1, objBullet[i].y_cor + 1, 1);
		}
	}
}

void _GameEngineEnemyesDraw (_GameFeature* game, _GameObject* objEnemy)
{
	for (u8 i = 0; i < ENEMY_MAX_QANT + game->gameLVL; i++)
	{
		if (objEnemy[i].app == APPEAR)
			_GameEngineDrawObject8x8(&objEnemy[i], GUI_ENEMYS_PLANE_DRAW);

		else if (objEnemy[i].app == EXPLOSION)
			_GameEngineDrawObject8x8(&objEnemy[i], GUI_EXPLOSION_DRAW);
	}
}

void _GameEngineCareDraw (_GameObject* objCare)
{
	if (objCare->app == APPEAR)
		_GameEngineDrawObject8x8(objCare, GUI_CARE_DRAW);
}

void _GameEngineBossDraw (_GameObject* objBoss)
{
	if (objBoss->app == APPEAR)
		switch (objBoss->lvl)
		{
			case 1:
			{
				if (objBoss->wound == WOUNDED)
					_GameEngineDrawObject16x16(objBoss, GUI_DRAW_NFILL_16x16);
				else
					_GameEngineDrawObject16x16(objBoss, GUI_DRAW_BOSS_1LVL);
				break;
			}

			case 2:
			{
				if (objBoss->wound == WOUNDED)
					_GameEngineDrawObject16x16(objBoss, GUI_DRAW_NFILL_16x16);
				else
					_GameEngineDrawObject16x16(objBoss, GUI_DRAW_BOSS_2LVL);
				break;
			}

			case 3:
			{
				if (objBoss->wound == WOUNDED)
					_GameEngineDrawObject16x16(objBoss, GUI_DRAW_NFILL_16x16);
				else
					_GameEngineDrawObject16x16(objBoss, GUI_DRAW_BOSS_3LVL);
				break;
			}

			case 4:
			{
				if (objBoss->wound == WOUNDED)
					_GameEngineDrawObject24x24(objBoss, GUI_DRAW_NFILL_24x24);
				else
					_GameEngineDrawObject24x24(objBoss, GUI_DRAW_BOSS_4LVL);
				break;
			}

			case 5:
			{
				if (objBoss->wound == WOUNDED)
					_GameEngineDrawObject24x24(objBoss, GUI_DRAW_NFILL_24x24);
				else
					_GameEngineDrawObject24x24(objBoss, GUI_DRAW_BOSS_5LVL);
				break;
			}

			case 6:
			{
				if (objBoss->wound == WOUNDED)
					_GameEngineDrawObject24x24(objBoss, GUI_DRAW_NFILL_24x24);
				else
					_GameEngineDrawObject24x24(objBoss, GUI_DRAW_BOSS_6LVL);
				break;
			}

			case 7:
			{
				if (objBoss->wound == WOUNDED)
					_GameEngineDrawObject32x32(objBoss, GUI_DRAW_NFILL_32x32);
				else
					_GameEngineDrawObject32x32(objBoss, GUI_DRAW_BOSS_7LVL);
				break;
			}

			case 8:
			{
				if (objBoss->wound == WOUNDED)
					_GameEngineDrawObject32x32(objBoss, GUI_DRAW_NFILL_32x32);
				else
					_GameEngineDrawObject32x32(objBoss, GUI_DRAW_BOSS_8LVL);
				break;
			}

			case 9:
			{
				if (objBoss->wound == WOUNDED)
					_GameEngineDrawObject8x8(objBoss, GUI_DRAW_NFILL_8x8);
				else
					_GameEngineDrawObject8x8(objBoss, GUI_DRAW_BOSS_9LVL);
				break;
			}

			case 10:
			{
				if (objBoss->wound == WOUNDED)
					_GameEngineDrawObject32x64(objBoss, GUI_DRAW_NFILL_32x32, GUI_DRAW_NFILL_32x32);

				else
					_GameEngineDrawObject32x64(objBoss, GUI_DRAW_BOSS_10LVL, GUI_DRAW_BOSS_10LVL);
				break;
			}
		}
}

void _GameEngineBossBulletsDraw (_GameObject* objBossBullet)
{
	for (u8 i = 0; i < BOSS_BULLET_QUANTITY; i++)
	{
		if (objBossBullet[i].app == APPEAR)
		{
			ssd1306_DrawPixel(objBossBullet[i].x_cor, objBossBullet[i].y_cor, 1);
			ssd1306_DrawPixel(objBossBullet[i].x_cor + 1, objBossBullet[i].y_cor, 1);
			ssd1306_DrawPixel(objBossBullet[i].x_cor, objBossBullet[i].y_cor + 1, 1);
			ssd1306_DrawPixel(objBossBullet[i].x_cor + 1, objBossBullet[i].y_cor + 1, 1);
			ssd1306_DrawPixel(objBossBullet[i].x_cor + 2, objBossBullet[i].y_cor, 1);
			ssd1306_DrawPixel(objBossBullet[i].x_cor, objBossBullet[i].y_cor + 2, 1);
			ssd1306_DrawPixel(objBossBullet[i].x_cor + 1, objBossBullet[i].y_cor + 2, 1);
			ssd1306_DrawPixel(objBossBullet[i].x_cor + 2, objBossBullet[i].y_cor + 1, 1);
			ssd1306_DrawPixel(objBossBullet[i].x_cor + 2, objBossBullet[i].y_cor + 2, 1);
		}
	}
}

void _GameEngineBossErase (_GameObject* objBoss)
{
	switch (objBoss->lvl)
	{
		case 1:
		{
			_GameEngineEraseObject16x16(objBoss, GUI_DRAW_BOSS_1LVL);
			break;
		}

		case 2:
		{
			_GameEngineEraseObject16x16(objBoss, GUI_DRAW_BOSS_2LVL);
			break;
		}

		case 3:
		{
			_GameEngineEraseObject16x16(objBoss, GUI_DRAW_BOSS_3LVL);
			break;
		}

		case 4:
		{
			_GameEngineEraseObject24x24(objBoss, GUI_DRAW_BOSS_4LVL);
			break;
		}

		case 5:
		{
			_GameEngineEraseObject24x24(objBoss, GUI_DRAW_BOSS_5LVL);
			break;
		}

		case 6:
		{
			_GameEngineEraseObject24x24(objBoss, GUI_DRAW_BOSS_6LVL);
			break;
		}

		case 7:
		{
			_GameEngineEraseObject32x32(objBoss, GUI_DRAW_BOSS_7LVL);
			break;
		}

		case 8:
		{
			_GameEngineEraseObject32x32(objBoss, GUI_DRAW_BOSS_8LVL);
			break;
		}

		case 9:
		{
			_GameEngineEraseObject8x8(objBoss, GUI_DRAW_BOSS_9LVL);
			break;
		}

		case 10:
		{
			_GameEngineEraseObject32x64(objBoss, GUI_DRAW_BOSS_10LVL, GUI_DRAW_BOSS_10LVL);
			break;
		}
	}
}

void _GameEngineBulletsErase (_GameObject* objBullet)
{
	for (u8 i = 0; i < BULLET_QUANTITY; i++)
	{
		if (objBullet[i].app == DISAPPEAR)
		{
			ssd1306_DrawPixel(objBullet[i].x_old_cor, objBullet[i].y_old_cor, 0);
			ssd1306_DrawPixel(objBullet[i].x_old_cor + 1, objBullet[i].y_old_cor, 0);
			ssd1306_DrawPixel(objBullet[i].x_old_cor, objBullet[i].y_old_cor + 1, 0);
			ssd1306_DrawPixel(objBullet[i].x_old_cor + 1, objBullet[i].y_old_cor + 1, 0);
		}
	}
}

void _GameEngineEnemyesErase (_GameFeature* game, _GameObject* objEnemy)
{
	for (u8 i = 0; i < ENEMY_MAX_QANT  + game->gameLVL; i++)
	{
		if (objEnemy[i].app == DISAPPEAR)
		{
			_GameEngineEraseObject8x8(&objEnemy[i], GUI_ENEMYS_PLANE_DRAW);
		}
	}
}

void _GameEngineScoreDraw (_GameFeature* game, _GameObject* objStarship)
{
	char score [8];
	char lvl [3];

	sprintf (score, "%07d", game->score);
	sprintf (lvl, "%d", game->gameLVL);

	ssd1306_WriteText(UI_SCORE_X, UI_SCORE_Y, score, Font_6x8, 1);

	if (game->gameLVL < 10)
	{
		ssd1306_DrawFilledRectangle(UI_LVL_X, UI_LVL_Y - 1, UI_LVL_X + 6, UI_LVL_Y + 8, 0);
		ssd1306_WriteText(UI_LVL_X, UI_LVL_Y, &lvl[0], Font_6x8, 1);
	}

	else
	{
		ssd1306_DrawFilledRectangle(UI_LVL_X - 6, UI_LVL_Y - 1, UI_LVL_X + 6, UI_LVL_Y + 8, 0);
		ssd1306_WriteText(UI_LVL_X - 6, UI_LVL_Y, &lvl[0], Font_6x8, 1);
	}

	for (u8 i = 0; i < objStarship->hitPoints; i++)
		ssd1306_DrawSprite8x8 (UI_STARSHIP_HP_X + (i * (SPRITE8 + 1)), UI_STARSHIP_HP_Y, GUI_HEART_DRAW, 1);
}

void _GameEngineBossHPDraw (_GameFeature* game, _GameObject* objBoss)
{
	u16 maxHP = BOSS_HP * GAME_DIFFICULTY + (objBoss->lvl * BOSS_LVL_HP_ADD);
	float coeffHP;

	ssd1306_DrawRectangle (UI_BOSS_HP_X, UI_BOSS_HP_Y, UI_BOSS_HP_X + 34, UI_BOSS_HP_Y + 7, 1);

	for (u16 i = 0; i <= 30; i++)
	{
		coeffHP = maxHP / 30;

		if (objBoss->hitPoints / coeffHP > (maxHP / coeffHP) - i - 1)
			ssd1306_Line(UI_BOSS_HP_X + 2 + (30 - i), UI_BOSS_HP_Y + 2, UI_BOSS_HP_X + 2 + (30 - i), UI_BOSS_HP_Y + 5, 1);

		else
			ssd1306_Line(UI_BOSS_HP_X + 2 + (30 - i), UI_BOSS_HP_Y + 2, UI_BOSS_HP_X + 2 + (30 - i), UI_BOSS_HP_Y + 5, 0);
	}
}

void _GameEngineGameOver (_GameFeature* game)
{
	ssd1306_Fill(0);
	ssd1306_UpdateScreen();

	HAL_Delay (300);

	char score [8];

	sprintf (score, "%d", game->score);

	ssd1306_WriteText (1, 1, "Your score:", Font_7x10, 1);
	ssd1306_WriteText(80, 1, score, Font_7x10, 1);

	if (game->gameState == GAME_OVER)
	{
		while (!ButtonHandler())
		{
			ssd1306_WriteText(4, 21, "G A M E   O V E R", Font_7x10, 1);
			ssd1306_WriteText(4, 40, "Press   Joy   Key", Font_7x10, 1);
			ssd1306_WriteText(4, 51, "to start New Game", Font_7x10, 1);

			ssd1306_UpdateScreen();
			HAL_Delay(200);
			ERASE_BOTTOM;
			ssd1306_UpdateScreen();
			HAL_Delay(300);
		}
	}

	else
	{
		while (!ButtonHandler())
		{
			ssd1306_WriteText(4, 21, "V I C T O R Y ! !", Font_7x10, 1);
			ssd1306_WriteText(4, 40, "Press   Joy   Key", Font_7x10, 1);
			ssd1306_WriteText(4, 51, "to start New Game", Font_7x10, 1);

			ssd1306_UpdateScreen();
			HAL_Delay(200);
			ERASE_BOTTOM;
			ssd1306_UpdateScreen();
			HAL_Delay(300);
		}
	}
}

void _GameEngineDrawObject8x8 (_GameObject* obj, const uint8_t* sprite)
{
	ssd1306_DrawSprite8x8(obj->x_cor, obj->y_cor, sprite, 1);
}

void _GameEngineEraseObject8x8 (_GameObject* obj, const uint8_t* sprite)
{
	ssd1306_DrawSprite8x8(obj->x_old_cor, obj->y_old_cor, sprite, 0);
}

void _GameEngineDrawObject16x16 (_GameObject* obj, const uint16_t* sprite)
{
	ssd1306_DrawSprite16x16(obj->x_cor, obj->y_cor, sprite, 1);
}

void _GameEngineEraseObject16x16 (_GameObject* obj, const uint16_t* sprite)
{
	ssd1306_DrawSprite16x16(obj->x_old_cor, obj->y_old_cor, sprite, 0);
}

void _GameEngineDrawObject24x24 (_GameObject* obj, const uint32_t* sprite)
{
	ssd1306_DrawSprite24x24(obj->x_cor, obj->y_cor, sprite, 1);
}

void _GameEngineEraseObject24x24 (_GameObject* obj, const uint32_t* sprite)
{
	ssd1306_DrawSprite24x24(obj->x_old_cor, obj->y_old_cor, sprite, 0);
}

void _GameEngineDrawObject32x32 (_GameObject* obj, const uint32_t* sprite)
{
	ssd1306_DrawSprite32x32(obj->x_cor, obj->y_cor, sprite, 1);
}

void _GameEngineEraseObject32x32 (_GameObject* obj, const uint32_t* sprite)
{
	ssd1306_DrawSprite32x32(obj->x_old_cor, obj->y_old_cor, sprite, 0);
}

void _GameEngineDrawObject32x64 (_GameObject* obj, const uint32_t* sprite_1, const uint32_t* sprite_2)
{
	ssd1306_DrawSprite32x32(obj->x_cor, obj->y_cor, sprite_1, 1);
	ssd1306_DrawSprite32x32(obj->x_cor, obj->y_cor + SPRITE32, sprite_2, 1);
}

void _GameEngineEraseObject32x64 (_GameObject* obj, const uint32_t* sprite_1, const uint32_t* sprite_2)
{
	ssd1306_DrawSprite32x32(obj->x_old_cor, obj->y_old_cor, sprite_1, 0);
	ssd1306_DrawSprite32x32(obj->x_old_cor, obj->y_old_cor + SPRITE32, sprite_2, 0);
}

//========== qsivey@gmail.com	==========
