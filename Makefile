all: Snake_Game.v1.0

Snake_Game.v1.0: ./SourceCode/Snake_Game.v1.0.o ./SourceCode/TimeGame.o ./SourceCode/SnakeHead.o ./SourceCode/SnakeTail.o
	g++ ./SourceCode/Snake_Game.v1.0.o ./SourceCode/TimeGame.o ./SourceCode/SnakeHead.o ./SourceCode/SnakeTail.o -o Snake_Game.v1.0 -lsfml-graphics -lsfml-window -lsfml-system

./SourceCode/snake.v1.0.o: SourceCode/Snake_Game.v1.0.cpp
	g++ -c SourceCode/Snake_Game.v1.0.cpp -o ./SourceCode/Snake_Game.v1.0.o

./SourceCode/TimeGame.o: ./SourceCode/TimeGame.cpp
	g++ -c SourceCode/TimeGame.cpp -o ./SourceCode/TimeGame.o

./SourceCode/SnakeHead.o: ./SourceCode/SnakeHead.cpp
	g++ -c SourceCode/SnakeHead.cpp -o ./SourceCode/SnakeHead.o

./SourceCode/SnakeTail.o: ./SourceCode/SnakeTail.cpp
	g++ -c SourceCode/SnakeTail.cpp -o ./SourceCode/SnakeTail.o

clean:
	rm -rf *.o snake.v1.0
