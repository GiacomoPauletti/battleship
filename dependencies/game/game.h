#include <stdlib.h>
#include "../common/common.h"
#include "../map/map.h"
#include "../ship/ship.h"

#define CURSOR_CHAR '+'

void playerArmySetup(Player* player, Army gameArmy);

int localGameHandler(Player *player1, Player *player2);