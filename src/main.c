#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "test.h" // custom testing file
#define VALUE 15

// Global variables

Rectangle screen, boundary, top, bottom, ball, leftbat, rightbat;
int rightbatScore = 0, leftbatScore = 0;
int scoreWidth, winner;
Color Blue = {0, 137, 255, 255}; // External colour module

// User-defined types
typedef enum GameScreen
{
	TITLE = 0,
	GAMEPLAY,
	CREDITS,
	ENDING
} GameScreen;

typedef enum Direction
{
	UP = 0,
	DOWN
} Direction;

// Functions
void InitializeElements(void);

void MoveBat(Rectangle *pBat, Direction pDir);
void CpuBat(Rectangle *pBat);

void ThrowBall(void);
void MoveBall(void);

// Initialize window and primary game elements.

void InitializeElements(void)
{
	InitWindow(0, 0, "Ping - Pong! by Darshan");
	// Calculate size, position and inner size of window.
	screen = (Rectangle){0, 0, GetScreenWidth() / 2, GetScreenHeight() / 2};

	boundary = (Rectangle){VALUE, VALUE, screen.width - (2 * VALUE), screen.height - (2 * VALUE)};
	top = (Rectangle){screen.x, screen.y, boundary.width, boundary.y};
	bottom = (Rectangle){screen.x, boundary.height + VALUE, screen.width, screen.y};

	SetWindowPosition(screen.width / 2, screen.height / 2);
	SetWindowSize(screen.width, screen.height);

	SetTargetFPS(60);

	// Initialize elements.
	ball = (Rectangle){5 * VALUE, boundary.height, VALUE, VALUE};

	leftbat = (Rectangle){boundary.x + VALUE, (boundary.height / 2) - (5 * VALUE / 2), VALUE, 5 * VALUE};
	rightbat = (Rectangle){boundary.width - VALUE, (boundary.height / 2) - (5 * VALUE / 2), VALUE, 5 * VALUE};

	scoreWidth = MeasureText("00", 60);
}

// Ball movement

void MoveBall(void)
{
	static int xdir = VALUE / 2;
	static int ydir = VALUE / 2;

	Sound hit = LoadSound("/Projects/RaylibCG/resources/hit.wav");

	// Ball movement physics with Bat
	if ((CheckCollisionRecs(ball, leftbat) && ball.x < leftbat.x + leftbat.width) || (CheckCollisionRecs(ball, rightbat) && ball.x > rightbat.x - rightbat.width))
	{
		xdir = -xdir;
		PlaySound(hit);
	}
	else if (CheckCollisionRecs(ball, top) || CheckCollisionRecs(ball, bottom))
		ydir = -ydir;
	else
	{
		// Score.
		if (ball.x < screen.x)
		{
			++rightbatScore;
			ThrowBall();
		}
		else if (ball.x > screen.width)
		{
			++leftbatScore;
			ThrowBall();
		}
	}

	// Move ball.
	ball.x += xdir; // x and y move by 7 units
	ball.y += ydir;
}
// Throw ball after scoring.

void ThrowBall(void)
{
	ball.x = boundary.width / 2;
	ball.y = GetRandomValue(boundary.y + 10, boundary.height);
}
// Bat movement.

void MoveBat(Rectangle *pBat, Direction pDir)
{
	int step = (pDir == UP) ? -VALUE / 2 : VALUE / 2; // ternary operator used to make code more readable

	if ((CheckCollisionRecs(top, *pBat) && pDir == UP) || (CheckCollisionRecs(bottom, *pBat) && pDir == DOWN))
		return;
	pBat->y += step;

	if (rightbat.y >= screen.height - 6 * VALUE)
	{
		rightbat.y = screen.height - 6 * VALUE;
	}
}

// CPU rightbat Bat

void CpuBat(Rectangle *pBat)
{	
	// Logic to move the Bat
	int grand = GetRandomValue(4, 7);
	if (rightbat.y >= ball.y)
	{
		rightbat.y = rightbat.y - grand;
	}
	if (rightbat.y <= ball.y)
	{
		rightbat.y = rightbat.y + grand;
	}
}

// Start game.

int main(void)
{
	GameScreen currentScreen = TITLE;
	InitializeElements();
	InitAudioDevice();
	START1();

	Sound menu_music = LoadSound("/Projects/RaylibCG/resources/hero.wav");
	Sound win = LoadSound("/Projects/RaylibCG/resources/win.wav");
	Sound lose = LoadSound("/Projects/RaylibCG/resources/lose.wav");

	SetSoundVolume(menu_music, 0.2);
	SetSoundVolume(win, 1.0);
	PlaySound(menu_music);

	// Main loop.
	while (!WindowShouldClose()) // Checks if ESC key is pressed
	{

		// Updating to corresponding screens screens
		switch (currentScreen)
		{
		case TITLE:
		{

			if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
			{
				currentScreen = GAMEPLAY;
			}
		}
		break;
		case GAMEPLAY:
		{
			StopSound(menu_music);
			MoveBall();
			CpuBat(&rightbat);

			// Player Bat keys.
			if (IsKeyDown(KEY_Q))
				MoveBat(&leftbat, UP);
			else if (IsKeyDown(KEY_A))
				MoveBat(&leftbat, DOWN);

			// Following code can be used to have a 2 player Match
			//  if (IsKeyDown(KEY_P))
			//      MoveBat(&rightbat, UP);
			//  else if (IsKeyDown(KEY_L))
			//      MoveBat(&rightbat, DOWN);

			if ((leftbatScore >= 5) || (rightbatScore >= 5))
			{

				if (leftbatScore > rightbatScore)
				{
					PlaySound(win);
					winner = 1;
				}
				else
				{
					PlaySound(lose);
					winner = 2;
				}
				rightbatScore = leftbatScore = 0; // Reset Scores
				currentScreen = ENDING;
			}
		}
		break;
		case ENDING:
		{
			if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
				currentScreen = GAMEPLAY;
		}
		break;
		default:
			break;
		}

		// Rendering the game
		BeginDrawing();
		switch (currentScreen)
		{
		case TITLE:
		{
			ClearBackground(GREEN);

			DrawRectangle(screen.x, screen.y, screen.width, screen.height, DARKGREEN);
			DrawRectangle(screen.x, boundary.y, screen.width, boundary.height, GREEN);
			DrawText("PING - PONG!", 100, 20, 120, RED);
			DrawText("SCORE 5 POINTS TO WIN!", 100, 140, 50, BLACK);
			DrawText("- Darshan", 800, 220, 20, BLACK);
			DrawText("PLAYER 1 : KEYS Q, A", 100, 400, 30, DARKGREEN);
			DrawText("PLAYER 2 : CPU", 500, 400, 30, DARKGREEN);
			DrawText("ENTER TO PLAY", 100, 460, 30, RED);
			DrawText("ESCAPE TO QUIT", 100, 490, 30, RED);
		}
		break;
		case GAMEPLAY:
		{
			// Generating court
			DrawRectangle(screen.x, screen.y, screen.width, screen.height, DARKGREEN);
			DrawRectangle(screen.x, boundary.y, screen.width, boundary.height, GREEN);
			DrawRectangle((screen.width / 2) - 5, boundary.y, VALUE, boundary.height, YELLOW);

			// Scores

			DrawText(TextFormat("%02d", leftbatScore), (screen.width / 2) - 50 - scoreWidth, 50, 60, RED);
			DrawText(TextFormat("%02d", rightbatScore), (screen.width / 2) + 50, 50, 60, RED);

			// Ball

			DrawCircle(ball.x, ball.y, 10, RED);
			// Bats
			// The following code creates rectangular bats which have been replaced by rounded rectangles
			// DrawRectangle(leftbat.x, leftbat.y, leftbat.width, leftbat.height, WHITE);
			// DrawRectangle(rightbat.x, rightbat.y, rightbat.width, rightbat.height, WHITE);

			DrawRectangleRounded(rightbat, 0.8, 0, WHITE);
			DrawRectangleRounded(leftbat, 0.8, 0, WHITE);
		}
		break;
		case ENDING:
		{
			ClearBackground(GREEN);
			DrawRectangle(screen.x, screen.y, screen.width, screen.height, DARKGREEN);
			DrawRectangle(screen.x, boundary.y, screen.width, boundary.height, GREEN);
			DrawText(TextFormat("Winner is Player %d!", winner), 120, 50, 60, RED);
			if (winner == 1)
			{

				DrawText(TextFormat("HUMAN : These funny looking robots cannot beat us!", winner), 120, 120, 30, RED);
			}
			else
			{

				DrawText(TextFormat("AI : You humans cannot fathom our POWER!", winner), 120, 120, 30, RED);
			}
			DrawText("Press ENTER to PLAY AGAIN", 120, 420, 20, RED);
			DrawText("Press ESCAPE to QUIT", 120, 450, 20, DARKGREEN);
		}
		break;
		default:
			break;
		}
		EndDrawing();
	}

	// Deinitialization
	CloseWindow();
	// UnloadSound(menu_music);
	// UnloadSound(win);
	// UnloadSound(lose);
	CloseAudioDevice();

	return 0;
}

/*
Current Bugs:

1. Ball getting stuck to Bat or playable boundary limit.
2. Random jittering of ball causing Bat to jitter with it.
3. CPU bat goes out of boundary ( may be fixed by adding movement limit )

Future updates:

1. Adding sprites and animation.
2. Better looking user interface.

*/