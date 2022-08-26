
PROJECT_NAME = mini_game_01
SRC          = ./src
INCLUDE      = ./include
RAYLIB_SRC   = C:/raylib-4.2.0/src
LIB          = ./lib

all :
	gcc main.c $(SRC)/*.c -o $(PROJECT_NAME).exe -O1 -Wall -std=c99 -Wno-missing-braces -I $(INCLUDE)/ -I $(RAYLIB_SRC)/ -L $(LIB)/ -lraylib -lopengl32 -lgdi32 -lwinmm


run :
	./$(PROJECT_NAME).exe


# clean :
# 	del mini_game_01.exe
