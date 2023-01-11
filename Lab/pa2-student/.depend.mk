card.o: card.cpp card.h location.h game-common.h util-common.h \
 game-observer.h link.h infrastructure.h player.h industry.h \
 player-network.h
location.o: location.cpp location.h game-common.h util-common.h \
 game-observer.h link.h infrastructure.h player.h
util-common.o: util-common.cpp util-common.h game-common.h
game-observer.o: game-observer.cpp game-observer.h game-common.h \
 util-common.h
link.o: link.cpp link.h game-common.h location.h util-common.h \
 game-observer.h infrastructure.h player.h
link-todo.o: link-todo.cpp link.h game-common.h location.h util-common.h \
 game-observer.h infrastructure.h player.h
infrastructure.o: infrastructure.cpp infrastructure.h player.h \
 util-common.h game-common.h
player.o: player.cpp player.h util-common.h game-common.h player-hand.h \
 card.h location.h game-observer.h link.h infrastructure.h industry.h \
 player-network.h player-unbuilt.h
industry.o: industry.cpp industry.h location.h game-common.h \
 util-common.h game-observer.h link.h infrastructure.h player.h
player-network.o: player-network.cpp player-network.h location.h \
 game-common.h util-common.h game-observer.h link.h infrastructure.h \
 player.h industry.h
player-unbuilt.o: player-unbuilt.cpp player-unbuilt.h link.h \
 game-common.h location.h util-common.h game-observer.h infrastructure.h \
 player.h industry.h
player-hand.o: player-hand.cpp player-hand.h card.h location.h \
 game-common.h util-common.h game-observer.h link.h infrastructure.h \
 player.h industry.h player-network.h
industry-location.o: industry-location.cpp industry-location.h location.h \
 game-common.h util-common.h game-observer.h link.h infrastructure.h \
 player.h industry.h
industry-todo.o: industry-todo.cpp industry.h location.h game-common.h \
 util-common.h game-observer.h link.h infrastructure.h player.h
