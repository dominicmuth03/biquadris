CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD
OBJECTS = biquadris.o board.o boardstate.o abstractboard.o player.o commands.o exceptions.o block.o iblock.o jblock.o lblock.o oblock.o sblock.o tblock.o zblock.o square.o coordinates.o level.o levelzero.o levelone.o leveltwo.o levelthree.o levelfour.o random.o blind.o force.o heavy.o effectdecorator.o subject.o game.o graphics.o text.o window.o observer.o
EXEC = biquadris

DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11
-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
