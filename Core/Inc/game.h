#ifndef INC_GAME_H_
#define INC_GAME_H_

#include "adc.h"
#include "gpio.h"
#include "ssd1306.h"
#include "math.h"

#define delay(ms)					HAL_Delay(ms)

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;

typedef unsigned char uch;
typedef char ch;

// ====================== GAME ENGINE DEFINES ======================

#define GAME_DIFFICULTY				1		// Affects the number of enemies and the boss's health points
#define GAME_LVL_PASS_SCORE			100000		// Account for passing the level

#define LVL_TEST_MP				1		// The number that determines the level of the start of the game
#define LVL_TEST_PASS				LVL_PASS	// LVL_PASS, BOSS_PASS or GAME_OVER only!

#define DISPLAY_WIDTH				128
#define DISPLAY_HEIGHT				64

#define SPRITE8					8
#define SPRITE16				16
#define SPRITE32				32
#define SPRITE64				64

#define STARSHIP_SPEED				2		// 1 -> 3
#define STARSHIP_SHIELD				100 		// 100 -> 300 (the less the more difficult)
#define STARSHIP_MAX_HP				5

#define BULLET_SPEED 				4		// 2 -> 4
#define BULLET_QUANTITY 			20		// Simultaneous number of bullets on the screen
#define BULLET_POWER				20

#define ENEMY_SPEED 				2		// 1 -> 3 (the more the harder)
#define ENEMY_MAX_QANT 				10		// 5 -> 30 (the more the harder)
#define ENEMY_APPEAR_PROBABILITY		400		// 100 -> 1000 (the less the more difficult)
#define ENEMY_KILL_SCORE			123
#define ENEMY_KILL_COLLISION_SCORE		ENEMY_KILL_SCORE / 2

#define CARE_SPEED 				1		// 1 -> 3
#define CARE_MAX_QANT 				1
#define CARE_APPEAR_PROBABILITY			500 		// 100 -> 500 (the less the more easy)
#define CARE_COLLISION_SCORE			20000

#define BOSS_HP					100	 	// 100 -> ...
#define BOSS_LVL_HP_ADD				50	 	// 10 -> ...
#define BOSS_SPEED				1
#define BOSS_X_POS_OFFSET			3 		// LEFT OFFSET
#define BOSS_HIT_SCORE				67

#define BOSS_BULLET_QUANTITY			30 		// 10 -> 30 (the more the harder)
#define BOSS_SHOOT_PROBABILITY			100		// 50 -> 300 (the less the more difficult)
#define BOSS_BULLET_SPEED			1

// =============== DRAW SPRITE DEFINES ===============

#define GUI_STARSHIP_DRAW			Sprites16x16[0]
#define GUI_STARSHIP_WSH_DRAW			Sprites16x16[1]

#define GUI_ENEMYS_PLANE_DRAW			Sprites8x8[0]
#define GUI_EXPLOSION_DRAW			Sprites8x8[1]
#define GUI_CARE_DRAW				Sprites8x8[2]
#define GUI_HEART_DRAW				Sprites8x8[3]

#define GUI_DRAW_BOSS_1LVL			Sprites16x16[5]
#define GUI_DRAW_BOSS_2LVL			Sprites16x16[6]
#define GUI_DRAW_BOSS_3LVL			Sprites16x16[7]
#define GUI_DRAW_BOSS_4LVL			Sprites24x24[1]
#define GUI_DRAW_BOSS_5LVL			Sprites24x24[2]
#define GUI_DRAW_BOSS_6LVL			Sprites24x24[3]
#define GUI_DRAW_BOSS_7LVL			Sprites32x32[1]
#define GUI_DRAW_BOSS_8LVL			Sprites32x32[2]
#define GUI_DRAW_BOSS_9LVL			Sprites8x8[5]
#define GUI_DRAW_BOSS_10LVL			Sprites32x32[3]

#define GUI_DRAW_NFILL_8x8			Sprites8x8[4]
#define GUI_DRAW_NFILL_16x16			Sprites16x16[4]
#define GUI_DRAW_NFILL_24x24			Sprites24x24[0]
#define GUI_DRAW_NFILL_32x32			Sprites32x32[0]

// ============= INTERFACE DRAW DEFINES =============

#define ERASE_BOTTOM				ssd1306_DrawFilledRectangle(0, 16, DISPLAY_WIDTH - 1, DISPLAY_HEIGHT, 0);
#define UI_BOSS_HP_X				45
#define UI_BOSS_HP_Y				1

#define UI_STARSHIP_HP_X			DISPLAY_WIDTH - ((SPRITE8 + 1) * STARSHIP_MAX_HP)
#define UI_STARSHIP_HP_Y			1

#define UI_LVL_X				DISPLAY_WIDTH - 7
#define UI_LVL_Y				DISPLAY_HEIGHT - 9

#define UI_SCORE_X				1
#define UI_SCORE_Y				1

// =============== GAME MACRO DEFINES ===============

typedef enum
{

	LVL_PASS,
	BOSS_PASS,
	GAME_OVER,
	VICTORY

} _GAMESTATE;

typedef enum
{

								MOVE_UP,

				MOVE_UP_LEFT,			 		MOVE_UP_RIGHT,

	MOVE_LEFT,						MOVE_NONE,				  MOVE_RIGHT,

				MOVE_DOWN_LEFT,			  		MOVE_DOWN_RIGHT,

								MOVE_DOWN

} _MOVE;


typedef enum
{

	DIR_UP,
	DIR_DOWN,
	DIR_NONE

} _DIRECTIONS;

typedef enum
{

	APPEAR,
	DISAPPEAR,
	EXPLOSION

} _EXISTENCE;


typedef enum
{

	OFF,
	ON

} _USERBUTT;


typedef enum
{

	BOSS_8 = 1,
	BOSS_16 = 2,
	BOSS_24 = 3,
	BOSS_32 = 4,
	BOSS_64 = 8

} _BOSSTYPES;


typedef enum
{

	NORMAL,
	WOUNDED

} _LIFESTATE;


typedef struct
{

	_GAMESTATE gameState;
	i32 score;
	u8 gameLVL;

} _GameFeature;


typedef struct
{

	i32 shield;
	i16 hitPoints;
	i8 x_cor;
	u8 y_cor;
	u8 x_old_cor, y_old_cor;
	u8 speed;
	u8 lvl;
	u8 initState;
	u8 bulletCount;
	_LIFESTATE wound;
	_DIRECTIONS dir;
	_BOSSTYPES type;
	_EXISTENCE app;
	_USERBUTT shotApply;

} _GameObject;

// =============== FUNCTION PROTOTYPES ===============

u16 ReadFromADC(u8 channel);

_USERBUTT ButtonHandler(void);
void _GameEngineBulletInit (_GameObject* objStarship, _GameObject* objBullet);
void _GameEngineBossBulletInit (_GameObject* objBoss, _GameObject* objBossBullet);
void _GameEngineBossInit (_GameFeature* game, _GameObject* objStarship, _GameObject* objBoss);
void _GameEngineBossAppear (_GameFeature* game, _GameObject* objStarship, _GameObject* objBoss);

_MOVE JoystickMoveHandler(void);
void _GameEngineJoystickHandler(_MOVE userMove, _GameFeature* game, _GameObject* objStarship, _GameObject* objBullet, _GameObject* objBoss);
void _GameEngineBulletsHandler (_GameObject* objBullet);
void _GameEngineEnemyesHandler (_GameFeature* game, _GameObject* objEnemy);
void _GameEngineCareHandler (_GameObject* objCare);
void _GameEngineBossHandler (_GameFeature* game, _GameObject* objStarship, _GameObject* objBullet, _GameObject* objEnemy, _GameObject* objCare, _GameObject* objBoss, _GameObject* objBossBullet);
void _GameEngineBossBulletsHandler (_GameObject* objBossBullet);

void _GameEngineColissionHandler (_GameFeature* game, _GameObject* objStarship, _GameObject* objBullet, _GameObject* objEnemy, _GameObject* objCare, _GameObject* objBoss, _GameObject* objBossBullet);
void _GameEngineScoreHandler (_GameFeature* game);
void _GameEngineLifeHandler (_GameFeature* game, _GameObject* objStarship);

void _GameEngineStarshipDraw (_GameObject* objStarship);
void _GameEngineBulletsDraw (_GameObject* objBullet);
void _GameEngineEnemyesDraw (_GameFeature* game, _GameObject* objEnemy);
void _GameEngineCareDraw (_GameObject* objCare);
void _GameEngineBossDraw (_GameObject* objBoss);
void _GameEngineBossBulletsDraw (_GameObject* objBossBullet);

void _GameEngineBulletsErase (_GameObject* objBullet);
void _GameEngineEnemyesErase (_GameFeature* game, _GameObject* objEnemy);
void _GameEngineBossErase (_GameObject* objBoss);

void _GameEngineScoreDraw (_GameFeature* game, _GameObject* objStarship);
void _GameEngineBossHPDraw (_GameFeature* game, _GameObject* objBoss);

void _GameEngineGameOver (_GameFeature* game);

void _GameEngineDrawObject8x8 (_GameObject* obj, const uint8_t* sprite);
void _GameEngineEraseObject8x8 (_GameObject* obj, const uint8_t* sprite);
void _GameEngineDrawObject16x16 (_GameObject* obj, const uint16_t* sprite);
void _GameEngineEraseObject16x16 (_GameObject* obj, const uint16_t* sprite);
void _GameEngineDrawObject24x24 (_GameObject* obj, const uint32_t* sprite);
void _GameEngineEraseObject24x24 (_GameObject* obj, const uint32_t* sprite);
void _GameEngineDrawObject32x32 (_GameObject* obj, const uint32_t* sprite);
void _GameEngineEraseObject32x32 (_GameObject* obj, const uint32_t* sprite);
void _GameEngineDrawObject32x64 (_GameObject* obj, const uint32_t* sprite, const uint32_t* sprite_2);
void _GameEngineEraseObject32x64 (_GameObject* obj, const uint32_t* sprite, const uint32_t* sprite_2);

// ====================== GUI SPRITES ======================

static const u8 Sprites8x8 [6][8] = {
{0x06, 0x0F, 0x1F, 0xFE, 0xFE, 0x1F, 0x0F, 0x06},	// ENEMYs PLANE
{0x42, 0x85, 0x50, 0x50, 0x36, 0x42, 0x10, 0x3C},	// EXPLOSION
{0x18, 0x18, 0x18, 0xFF, 0xFF, 0x18, 0x18, 0x18},	// CARE
{0x66, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0x18, 0x00},	// HEART
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// NOTHING
{0x03, 0x07, 0xFF, 0x1E, 0x1E, 0xFF, 0x07, 0x03}	// // BOSS 9_LVL (CANON)
};

static const u16 Sprites16x16 [8][16] = {
{0x4000, 0x7F00, 0x7000, 0x7800, 0x7C00, 0x3E00, 0xBF00, 0xFFFF, 0xFFFF, 0xBF00, 0x3E00, 0x7C00, 0x7800, 0x7000, 0x7F00, 0x4000},	// STARSHIP
{0x4018, 0x7F04, 0x7002, 0x7802, 0x7C01, 0x3E00, 0xBF00, 0xFFFF, 0xFFFF, 0xBF00, 0x3E00, 0x7C01, 0x7802, 0x7002, 0x7F04, 0x4018},	// STARSHIP with SHIELD
{0xFFFF, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0xFFFF},	// SQUARE
{0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF}, 	// FILLED SQUARE
{0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// NOTHING

{0x0039, 0x0013, 0x0017, 0x001F, 0x001F, 0x003F, 0x187F, 0xFFFE, 0xFFFE, 0x187F, 0x003F, 0x001F, 0x001F, 0x0017, 0x0013, 0x0039},	// BOSS 1_LVL ()
{0x0039, 0x01FB, 0x001F, 0x001F, 0x001F, 0x183F, 0x3C7F, 0xFFFF, 0xFFFF, 0x3C7F, 0x183F, 0x001F, 0x001F, 0x001F, 0x01FB, 0x0039},	// BOSS 2_LVL ()
{0x07F9, 0x07FB, 0x003F, 0x003F, 0x003F, 0x787F, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x787F, 0x003F, 0x003F, 0x003F, 0x07FB, 0x07F9}	// BOSS 3_LVL ()
};

static const u32 Sprites24x24 [4][24] = {
{0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000},			// NOTHING
{0x07FFFF, 0x0C0003, 0x140005, 0x240009, 0x440011, 0xFFFFE1, 0x840021, 0x840021, 0x840021, 0x840021, 0x840021, 0x840021,
 0x840021, 0x840021, 0x840021, 0x840021, 0x840021, 0x840021, 0x87FFFF, 0x880022, 0x900024, 0xA00028, 0xC00030, 0xFFFFE0},			// BOSS 4_LVL (CUBE)
{0x01FFE0, 0x022850, 0x046488, 0x08A304, 0x112302, 0x222481, 0x442441, 0x882421, 0x902411, 0xA02409, 0xC02405, 0x802403,
 0xC02401, 0xA02403, 0x902405, 0x882409, 0x842411, 0x822422, 0x812444, 0x40C488, 0x20C510, 0x112620, 0x0A1440, 0x07FF80},			// BOSS 5_LVL (HYPERCUBE)
{0x03FC01, 0x040A03, 0x081105, 0x102089, 0x3FC051, 0x20FFE1, 0x214051, 0x2240C9, 0x244145, 0x284243, 0x304441, 0x204841,
 0x405041, 0x8060A1, 0xFFE111, 0x80A209, 0x81140D, 0x820813, 0x841421, 0x8A2242, 0x914184, 0xA08088, 0xC10050, 0xFE0020}			// BOSS 6_LVL (...)
};

static const u32 Sprites32x32 [4][32] = {
{0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000}, 	// NOTHING
{0x001FFFFF, 0x0FFFFFFE, 0x001FFFFE, 0x000FFFFF, 0x0007FFFF, 0x000FFF7F, 0x003FFF3F, 0x000FFF9E, 0x00007FCC, 0x00003FE4, 0x00001FE2, 0x00003FC1, 0x00007F82, 0x2000FF04, 0x6001FE08, 0xFFFFFC10,
 0xFFFFFC10, 0x6001FE08, 0x2000FF04, 0x00007F82, 0x00003FC1, 0x00001FE2, 0x00003FC4, 0x00007F8C, 0x0000FF9E, 0x0001FF3F, 0x0003FFFF, 0x0007FFFF, 0x000FFFFF, 0x001FFFFE, 0x0FFFFFFE, 0x001FFFFF}, 	// BOSS 7_LVL (TANK)
{0xFFC1FFFC, 0xFFFFFFFE, 0xE1FFFFFF, 0xFFFFFFFF, 0xFFC1FF2F, 0x00000727, 0x00000327, 0x00000327, 0x00000727, 0x00600D27, 0x00C00D27, 0x01800D27, 0x03000D27, 0x06001D26, 0x06003D26, 0x0601FD26,
 0x0601FD26, 0x06003D26, 0x06001D26, 0x03000D27, 0x01800D27, 0x00C00D27, 0x00600D27, 0x00000727, 0x00000327, 0x00000327, 0x00000727, 0xFFC1FF2F, 0xFFFFFFFF, 0xE1FFFFFF, 0xFFFFFFFE, 0xFFC1FFFC},	// BOSS 8_LVL (RUKI-BAZUKI)
{0xFFFC71C7, 0x3FFC71C7, 0x0FFC71C7, 0x03FF8E38, 0x00FF8E38, 0x003F8E38, 0x000FFFC7, 0x0003FFC7, 0x0000FFC7, 0x00303FF8, 0x003C0FF8, 0x000F03F8, 0x0003C0FF, 0x0000F03F, 0x00003C0F, 0x00000F03,
 0x00000F03, 0x00003C0F, 0x0000F03F, 0x0003C0FF, 0x000F03FF, 0x003C0FFF, 0x00303FFF, 0x0000FE38, 0x0003FE38, 0x000FFE38, 0x003FF1C7, 0x00FFF1C7, 0x03FFF1C7, 0x0FE38E38, 0x3FE38E38, 0xFFE38E38}	// BOSS 10_LVL (...)
};

#endif /* INC_GAME_H_ */
