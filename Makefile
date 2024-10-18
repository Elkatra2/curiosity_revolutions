.PHONY: all clean

# Compilateur et les drapeaux
CFLAGS = -Wall -g
CC_DEFAULT = clang $(CFLAGS)

# Les modes disponibles d'affichage
# - GRAPHIQUE   		affichage graphique
# - par défaut 			affichage dans la sortie standart
MODE ?= MODE

ifeq ($(MODE), GRAPHIQUE) # Affichage graphique
    CC = $(CC_DEFAULT) -lraylib -DAFFICHE_GRAPH
else
    CC = $(CC_DEFAULT)
endif

EXEC = test_terrain test_robot robot_terrain

all: $(EXEC)

######################################################################
#                       Règles de compilation                        #
######################################################################

%.o: %.c
	$(CC) -c $<

# La programme principale de test_terrain
test_terrain.o: test_terrain.c terrain.h graphique.h

# La programme principale de test_robot
test_robot.o: test_robot.c robot.h graphique.h

# La programme principale de robot_terrain
robot_terrain.o: robot_terrain.c terrain.h robot.h graphique.h

######################################################################
#                       Règles d'édition de liens                    #
######################################################################

# La programme qui teste le terrain
test_terrain: test_terrain.o terrain.o graphique.o

# La programme qui teste le robot
test_robot: test_robot.o robot.o graphique.o

# La programme de simulation de robot
robot_terrain: robot_terrain.o terrain.o robot.o graphique.o

# supprime
clean:
	rm -f $(EXEC) *.o
