main.exe: Display.o Game.o IntroState.o GameState.o IntroState.o Texture.o World.o Block.o main.o
	wineg++ Display.o Game.o IntroState.o GameState.o Texture.o World.o Block.o main.o -o main.exe

main.o: main.cpp Chunk.hpp Color.hpp Display.hpp Entity.hpp Game.hpp GameState.hpp IntroState.hpp Rect.hpp State.hpp Texture.hpp Tile.hpp Transparency.hpp World.hpp
	wineg++ -c main.cpp -o main.o

Display.o: Display.cpp Chunk.hpp Color.hpp Display.hpp Entity.hpp Game.hpp GameState.hpp IntroState.hpp Rect.hpp State.hpp Texture.hpp Tile.hpp Transparency.hpp World.hpp
	wineg++ -c Display.cpp -o Display.o

Game.o: Game.cpp Chunk.hpp Color.hpp Display.hpp Entity.hpp Game.hpp GameState.hpp IntroState.hpp Rect.hpp State.hpp Texture.hpp Tile.hpp Transparency.hpp World.hpp
	wineg++ -c Game.cpp -o Game.o

GameState.o: GameState.cpp Chunk.hpp Color.hpp Display.hpp Entity.hpp Game.hpp GameState.hpp IntroState.hpp Rect.hpp State.hpp Texture.hpp Tile.hpp Transparency.hpp World.hpp
	wineg++ -c GameState.cpp -o GameState.o

IntroState.o: IntroState.cpp Chunk.hpp Color.hpp Display.hpp Entity.hpp Game.hpp GameState.hpp IntroState.hpp Rect.hpp State.hpp Texture.hpp Tile.hpp Transparency.hpp World.hpp
	wineg++ -c IntroState.cpp -o IntroState.o

Texture.o: Texture.cpp Chunk.hpp Color.hpp Display.hpp Entity.hpp Game.hpp GameState.hpp IntroState.hpp Rect.hpp State.hpp Texture.hpp Tile.hpp Transparency.hpp World.hpp
	wineg++ -c Texture.cpp -o Texture.o

World.o: World.cpp Chunk.hpp Color.hpp Display.hpp Entity.hpp Game.hpp GameState.hpp IntroState.hpp Rect.hpp State.hpp Texture.hpp Tile.hpp Transparency.hpp World.hpp
	wineg++ -c World.cpp -o World.o

Block.o: Block.cpp Block.hpp Chunk.hpp Color.hpp Display.hpp Entity.hpp Game.hpp GameState.hpp IntroState.hpp Rect.hpp State.hpp Texture.hpp Tile.hpp Transparency.hpp World.hpp
	wineg++ -c Block.cpp -o Block.o
