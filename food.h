#ifndef DEF_FOOD

#define DEF_FOOD
#include <vector>
#include "constants.h"
#include <ncurses.h>
#include <experimental/random>
#include "snake.h"
using namespace std;


void init_food();
void paint_food();
bool try_consume_food(pair<int, int>);

#endif