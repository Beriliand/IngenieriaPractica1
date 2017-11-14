// Practica1.cpp : 1D Game

#include "stdafx.h"
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <cmath>
#include <ctime>
#define ESC            27
#define ORIGIN         0
#define ENDWORLD       60
#define ENEMYSPAWNTIME 100
#define ITEMSCORE      50
#define ITEMSPAWNTIME  150
#define PLAYERLIVES    3

void DeactivateEnemy(bool& spawn, int& counter);
void DeactivateItem(bool& spawn, int& counter);

int main() {
	int x			   = 0;
	int leftBulletPos  = 0;
	int rightBulletPos = 0;
	int enemyCounter   = ENEMYSPAWNTIME;
	int enemyPos       = -1;
	int score          = 0;
	int whileCounter   = 0;
	int itemPos        = -1;
	int itemCounter    = ITEMSPAWNTIME;
	int lives          = PLAYERLIVES;
	bool shotRight     = false;
	bool shotLeft      = false;
	bool spawnEnemy    = false;
	bool spawnedRight  = false;
	bool spawnItem     = false;

	srand(time(NULL));
	printf("\n\n\n\n\n\n\n\n\n\n\n\n");

	while (true) {
		//input
		if (_kbhit()) {
			char pressedKey = _getch();
			if (pressedKey == ESC)
				return 0;
			if (pressedKey == 'a' && x > ORIGIN)
				--x;
			if (pressedKey == 'd' && x < ENDWORLD)
				++x;
			if (pressedKey == 'f' && (!shotLeft && !shotRight)) {
				shotLeft = true;
				leftBulletPos = x - 1;
			}
			if (pressedKey == 'g' && (!shotLeft && !shotRight)) {
				shotRight = true;
				rightBulletPos = x + 1;
			}
		}

		//logica
		//logica de disparos
		if (shotLeft)
			--leftBulletPos;

		if (shotRight)
			++rightBulletPos;

		if (leftBulletPos < ORIGIN)
			shotLeft = false;

		if (rightBulletPos > ENDWORLD)
			shotRight = false;

		//logica de enemigo
		--enemyCounter;

		//spawn del enemigo
		if (!enemyCounter && !spawnEnemy) {
			spawnEnemy = true;
			enemyPos = rand() % 2 + 1;
			if (enemyPos == 2) {
				enemyPos = ENDWORLD;
				spawnedRight = true;
			}
			else {
				enemyPos = ORIGIN;
				spawnedRight = false;
			}
		}

		//destruccion de enemigo
		if (spawnEnemy) {
			if (enemyPos == x) {
				x = ORIGIN;
				--lives;
				enemyPos = -1;
				DeactivateEnemy(spawnEnemy, enemyCounter);
			} else if (shotLeft) {
				if (enemyPos == leftBulletPos) {
					shotLeft = false;
					DeactivateEnemy(spawnEnemy, enemyCounter);
				}
			}
			else if (shotRight) {
				if (enemyPos == rightBulletPos) {
					shotRight = false;
					DeactivateEnemy(spawnEnemy, enemyCounter);
				}
			}
		}

		//movimiento del enemigo
		if ((spawnEnemy && spawnedRight) && !(whileCounter % 3))
			--enemyPos;
		else if ((spawnEnemy && !spawnedRight) && !(whileCounter % 3))
			++enemyPos;

		++whileCounter;

		//logica de objeto
		//spawn de objeto
		if (!itemCounter) {
			spawnItem = true;
			itemPos = rand() % ENDWORLD + ORIGIN;
		}

		//destruccion de objeto
		if (spawnItem) {
			if (itemPos == x) {
				score += ITEMSCORE;
				DeactivateItem(spawnItem, itemCounter);
			} else if (shotLeft) {
				if (itemPos == leftBulletPos) {
					shotLeft = false;
					DeactivateItem(spawnItem, itemCounter);
				}
			} else if (shotRight) {
				if (itemPos == rightBulletPos) {
					shotRight = false;
					DeactivateItem(spawnItem, itemCounter);
				}
			}
		}

		--itemCounter;

		//comprobacion de vidas
		if (lives < 0)
			return 0;

		//pintado
		printf("Lifes: %i ", lives);

		for (int i = ORIGIN; i <= ENDWORLD; i++) {
			if (i == x)
				printf("X");
			else if (shotLeft && i == leftBulletPos)
				printf("<");
			else if (shotRight && i == rightBulletPos)
				printf(">");
			else if (i == enemyPos && spawnEnemy)
				printf("Y");
			else if (i == itemPos && spawnItem)
				printf(":");
			else
				printf("_");
		}

		printf(" SCORE: %i\r", score);

		//tiempo de espera
		Sleep(50);
	}

    return 0;
}

void DeactivateEnemy (bool& spawn, int& counter) {
	spawn = false;
	counter = ENEMYSPAWNTIME;
}

void DeactivateItem (bool& spawn, int& counter) {
	spawn = false;
	counter = ITEMSPAWNTIME;
}

