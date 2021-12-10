main: main.o dependencies/common/common.o dependencies/game/game.o dependencies/map/map.o dependencies/menu/menu.o dependencies/ship/ship.o
	gcc -o main main.o dependencies/common/common.o dependencies/game/game.o dependencies/map/map.o dependencies/menu/menu.o dependencies/ship/ship.o

main.o: main.c dependencies/common/common.h dependencies/game/game.h dependencies/map/map.h dependencies/menu/menu.h dependencies/ship/ship.h
	gcc -c main.c

# maybe adding down here: dependencies/map/map.h dependencies/ship/ship.h dependencies/common/common.h
dependencies/menu/menu.o: dependencies/menu/menu.c dependencies/menu/menu.h 
	gcc -c dependencies/menu/menu.c -o dependencies/menu/menu.o 

# maybe adding down here: dependencies/map/map.h dependencies/ship/ship.h dependencies/common/common.h
dependencies/game/game.o: dependencies/game/game.c dependencies/game/game.h
	gcc -c dependencies/game/game.c -o dependencies/game/game.o 

# maybe adding down here: dependencies/map/map.h  dependencies/common/common.h
dependencies/ship/ship.o: dependencies/ship/ship.c dependencies/ship/ship.h
	gcc -c dependencies/ship/ship.c -o dependencies/ship/ship.o 

# maybe adding down here: dependencies/map/map.h dependencies/ship/ship.h 
dependencies/common/common.o: dependencies/common/common.c dependencies/common/common.h
	gcc -c dependencies/common/common.c -o dependencies/common/common.o 

dependencies/map/map.o: dependencies/map/map.c dependencies/map/map.h
	gcc -c dependencies/map/map.c -o dependencies/map/map.o 
