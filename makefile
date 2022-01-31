main: main.o dependencies/common/common.o dependencies/game/game.o dependencies/map/map.o dependencies/menu/menu.o dependencies/ship/ship.o dependencies/database/database.o dependencies/filesystem/filesystem.o dependencies/LAN_protocol/protocol.o
	gcc -o main main.o dependencies/common/common.o dependencies/game/game.o dependencies/map/map.o dependencies/menu/menu.o dependencies/ship/ship.o dependencies/database/database.o dependencies/filesystem/filesystem.o dependencies/LAN_protocol/protocol.o
	x86_64-w64-mingw32-gcc -lerrno.h -ldirect.h -o wmain.exe wmain.o dependencies/common/wcommon.o dependencies/game/wgame.o dependencies/map/wmap.o dependencies/menu/wmenu.o dependencies/ship/wship.o dependencies/database/wdatabase.o dependencies/filesystem/wfilesystem.o dependencies/LAN_protocol/wprotocol.o

#problem with linking (and finding) errno (and maybe also direct) headers

main.o: main.c dependencies/common/common.h dependencies/game/game.h dependencies/map/map.h dependencies/menu/menu.h dependencies/ship/ship.h
	gcc -c main.c
	x86_64-w64-mingw32-gcc -c main.c -o wmain.o

# maybe adding down here: dependencies/map/map.h dependencies/ship/ship.h dependencies/common/common.h
dependencies/menu/menu.o: dependencies/menu/menu.c dependencies/menu/menu.h dependencies/database/database.h dependencies/LAN_protocol/protocol.h
	gcc -c dependencies/menu/menu.c -o dependencies/menu/menu.o
	x86_64-w64-mingw32-gcc -c dependencies/menu/menu.c -o dependencies/menu/wmenu.o

# maybe adding down here: dependencies/map/map.h dependencies/ship/ship.h dependencies/common/common.h
dependencies/game/game.o: dependencies/game/game.c dependencies/game/game.h
	gcc -c dependencies/game/game.c -o dependencies/game/game.o 
	x86_64-w64-mingw32-gcc -c dependencies/game/game.c -o dependencies/game/wgame.o 

# maybe adding down here: dependencies/map/map.h  dependencies/common/common.h
dependencies/ship/ship.o: dependencies/ship/ship.c dependencies/ship/ship.h
	gcc -c dependencies/ship/ship.c -o dependencies/ship/ship.o 
	x86_64-w64-mingw32-gcc  -c dependencies/ship/ship.c -o dependencies/ship/wship.o 

# maybe adding down here: dependencies/map/map.h dependencies/ship/ship.h 
dependencies/common/common.o: dependencies/common/common.c dependencies/common/common.h
	gcc -c dependencies/common/common.c -o dependencies/common/common.o 
	x86_64-w64-mingw32-gcc -l conio.h -c dependencies/common/common.c -o dependencies/common/wcommon.o 

dependencies/database/database.o: dependencies/database/database.c dependencies/database/database.h dependencies/filesystem/filesystem.h
	gcc -c dependencies/database/database.c -o dependencies/database/database.o 
	x86_64-w64-mingw32-gcc -c dependencies/database/database.c -o dependencies/database/wdatabase.o

dependencies/filesystem/filesystem.o: dependencies/filesystem/filesystem.c dependencies/filesystem/filesystem.h
	gcc -c dependencies/filesystem/filesystem.c -o dependencies/filesystem/filesystem.o
	x86_64-w64-mingw32-gcc -c dependencies/filesystem/filesystem.c -o dependencies/filesystem/wfilesystem.o

dependencies/map/map.o: dependencies/map/map.c dependencies/map/map.h
	gcc -c dependencies/map/map.c -o dependencies/map/map.o 
	x86_64-w64-mingw32-gcc -c dependencies/map/map.c -o dependencies/map/wmap.o 

dependencies/LAN_protocol/protocol.o: dependencies/LAN_protocol/protocol.c  dependencies/LAN_protocol/protocol.h
	gcc -c dependencies/LAN_protocol/protocol.c -o dependencies/LAN_protocol/protocol.o
	x86_64-w64-mingw32-gcc -lws2_32 -c dependencies/LAN_protocol/protocol.c -o  dependencies/LAN_protocol/wprotocol.o
