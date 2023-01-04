all: Snake_Game.v1.0

Snake_Game.v1.0: ./SourceCode/Snake_Game.v1.0.o ./SourceCode/TimeGame.o ./SourceCode/SnakeHead.o ./SourceCode/SnakeTail.o ./SourceCode/SnakeOBJ.o ./SourceCode/TextGame.o ./SourceCode/Background.o ./SourceCode/BackgroundLevel.o ./SourceCode/Menu.o ./SourceCode/Food.o
	g++ ./SourceCode/Snake_Game.v1.0.o ./SourceCode/TimeGame.o ./SourceCode/SnakeHead.o ./SourceCode/SnakeTail.o ./SourceCode/SnakeOBJ.o ./SourceCode/TextGame.o ./SourceCode/Background.o ./SourceCode/BackgroundLevel.o ./SourceCode/Menu.o ./SourceCode/Food.o -o Snake_Game.v1.0 -lsfml-graphics -lsfml-window -lsfml-system


./SourceCode/snake.v1.0.o: SourceCode/Snake_Game.v1.0.cpp
	g++ -c SourceCode/Snake_Game.v1.0.cpp -o ./SourceCode/Snake_Game.v1.0.o

./SourceCode/TimeGame.o: ./SourceCode/TimeGame.cpp
	g++ -c SourceCode/TimeGame.cpp -o ./SourceCode/TimeGame.o

./SourceCode/SnakeHead.o: ./SourceCode/SnakeHead.cpp
	g++ -c SourceCode/SnakeHead.cpp -o ./SourceCode/SnakeHead.o

./SourceCode/SnakeTail.o: ./SourceCode/SnakeTail.cpp
	g++ -c SourceCode/SnakeTail.cpp -o ./SourceCode/SnakeTail.o

./SourceCode/SnakeOBJ.o: ./SourceCode/SnakeOBJ.cpp
	g++ -c SourceCode/SnakeOBJ.cpp -o ./SourceCode/SnakeOBJ.o

./SourceCode/TextGame.o: ./SourceCode/TextGame.cpp
	g++ -c SourceCode/TextGame.cpp -o ./SourceCode/TextGame.o

./SourceCode/Background.o: ./SourceCode/Background.cpp
	g++ -c SourceCode/Background.cpp -o ./SourceCode/Background.o

./SourceCode/BackgroundLevel.o: ./SourceCode/BackgroundLevel.cpp
	g++ -c SourceCode/BackgroundLevel.cpp -o ./SourceCode/BackgroundLevel.o

./SourceCode/Menu.o: ./SourceCode/Menu.cpp
	g++ -c SourceCode/Menu.cpp -o ./SourceCode/Menu.o

./SourceCode/Food.o: ./SourceCode/Food.cpp
	g++ -c SourceCode/Food.cpp -o ./SourceCode/Food.o

clean:
	rm -rf *.o snake.v1.0
