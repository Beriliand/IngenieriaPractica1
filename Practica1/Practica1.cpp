// Practica1.cpp : 1D Game

#include "stdafx.h"
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <cmath>
#include <ctime>
#include <list>
#define ESC            27
#define ORIGIN         0
#define ENDWORLD       60
#define ENEMYSPAWNTIME 100
#define ITEMSCORE      50
#define ITEMSPAWNTIME  150
#define PLAYERLIVES    3
#define LEFT           -1
#define RIGHT		   1

void DeactivateEnemy(bool& spawn, int& counter);
void DeactivateItem(bool& spawn, int& counter);

int main() {
	int x			   = 0;
	int enemyCounter   = ENEMYSPAWNTIME;
	int enemyPos       = -1;
	int score          = 0;
	int whileCounter   = 0;
	int itemPos        = -1;
	int itemCounter    = ITEMSPAWNTIME;
	int lives          = PLAYERLIVES;
	bool spawnEnemy    = false;
	bool spawnedRight  = false;
	bool spawnItem     = false;

	struct bullet {
		int x;
		int dir;
	};
	std::list <bullet> bullets;

	struct enemy {
		int x;
		int dir;
	};
	std::list <enemy> enemies;
	

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
			if (pressedKey == 'f') {
				bullet l;
				l.x = x;
				l.dir = LEFT;
				bullets.push_back(l);
			}
			if (pressedKey == 'g') {
				bullet r;
				r.x = x;
				r.dir = RIGHT;
				bullets.push_back(r);
			}
		}

		//logica
		//logica de disparos
		for (auto it = bullets.begin(); it != bullets.end(); it++) {
			if (it->dir == LEFT) {
				--it->x;
				if (it->x < ORIGIN) {
					it = bullets.erase(it);
					if (it == bullets.end())
						break;
				}
			} else {
				++it->x;
				if (it->dir >= ENDWORLD)
					it = bullets.erase(it);
			}
		}

		//logica de enemigo
		--enemyCounter;

		//movimiento de enemigos
		if (!(whileCounter % 3)) {
			for (auto it = enemies.begin(); it != enemies.end(); it++) {
				if (it->dir == LEFT) {
					--it->x;
					if (it->x < ORIGIN) {
						it = enemies.erase(it);
						if (it == enemies.end())
							break;
					}
				} else
					++it->x;
			}
		}

		//spawn del enemigo
		if (!enemyCounter) {
			enemyPos = rand() % 2 + 1;
			enemy e;
			if (enemyPos == 2) {
				e.x = ENDWORLD;
				e.dir = LEFT;
			}
			else {
				e.x = ORIGIN;
				e.dir = RIGHT;
			}

			enemies.push_back(e);
			enemyCounter = ENEMYSPAWNTIME;
		}

		//destruccion de enemigo
		/*if (spawnEnemy) {
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
		}*/

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
			}/* else if (shotLeft) {
				if (itemPos == leftBulletPos) {
					shotLeft = false;
					DeactivateItem(spawnItem, itemCounter);
				}
			} else if (shotRight) {
				if (itemPos == rightBulletPos) {
					shotRight = false;
					DeactivateItem(spawnItem, itemCounter);
				}
			}*/
		}

		--itemCounter;

		//deteccion de colisiones
		for (auto it = bullets.begin(); it != bullets.end(); it++) {
			for (auto ite = enemies.begin(); ite != enemies.end(); ite++) {
				if (ite->x == it->x+1 || ite->x == ite->x-1) {
					it = bullets.erase(it);
					ite = enemies.erase(ite);
				}
				if (ite == enemies.end()) {
					break;
				}
			}
			if (it == bullets.end()) {
				break;
			}
		}

		//comprobacion de vidas
		if (lives < 0)
			return 0;

		//pintado
		printf("Lifes: %i ", lives);

		for (int i = ORIGIN; i <= ENDWORLD; i++) {
			bool printed = false;

			if (i == x && !printed) {
				printf("X");
				printed = true;
			}

			if (enemies.size() && !printed) {
				for (auto it = enemies.begin(); it != enemies.end(); it++) {
					if (i == it->x) {
						printf("Y");
						printed = true;
					}
				}
			}

			if (i == itemPos && spawnItem && !printed) {
				printf(":");
				printed = true;
			}

			if (bullets.size() && !printed) {
				for (auto it = bullets.begin(); it != bullets.end(); it++) {
					if (i == it->x) {
						if (it->dir == LEFT)
							printf("<");
						else
							printf(">");
							
						printed = true;
					}
				}
			}

			if (!printed) {
				printf("_");
			}
			
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

