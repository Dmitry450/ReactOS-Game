CC=x86_64-w64-mingw32-g++
CFLAGS=-Wall -static
DEPS = Block.hpp Chat.hpp Chunk.hpp Color.hpp Display.hpp Entity.hpp Game.hpp GameState.hpp IntroState.hpp Rect.hpp State.hpp Texture.hpp Tile.hpp Transparency.hpp World.hpp TextureAtlas.hpp
OBJ = main.o Block.o Display.o Game.o GameState.o IntroState.o Texture.o World.o TextureAtlas.o


%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main.exe: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

