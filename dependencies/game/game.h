#include <stdlib.h>

#include <errno.h>

#include "../common/common.h"
#include "../map/map.h"
#include "../ship/ship.h"

#include "../LAN_protocol/protocol.h"

#define CURSOR_CHAR '+'


void playerArmySetup(Player* player, Army gameArmy);

int localGameHandler(Player *player1, Player *player2);

int hostGameHandler(Player *attacker, Player *defender);

int guestGameHandler(Player *onlinePlayer, Player *localPlayer);

int localGuestGameHandler(Player *localPlayer, Player *oppPlayer);

int isShipHitted(Player *player, Coordinate point);