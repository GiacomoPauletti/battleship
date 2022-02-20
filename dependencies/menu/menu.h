#include <stdio.h>

#include <errno.h>

#include "../map/map.h"
#include "../ship/ship.h"
#include "../common/common.h"
#include "../game/game.h"
#include "../database/database.h"
#include "../LAN_protocol/protocol.h"

#if !defined(MENU_H)
#define MENU_H


typedef struct {} MenuData;

void mainMenu( MenuData data);

#endif