CC=x86_64-w64-mingw32-g++
CFLAGS=-Wall -static -DNOMINMAX
DEPS = Block.hpp Color.hpp Display.hpp Hitbox.hpp Entity.hpp EntityManager.hpp \
	   PhysicalEntity.hpp Player.hpp Game.hpp GameState.hpp IntroState.hpp \
	   Rect.hpp State.hpp Texture.hpp Tile.hpp Transparency.hpp World.hpp TextureAtlas.hpp \
	   Item.hpp ItemStack.hpp Inventory.hpp ItemBlock.hpp
ODIR = obj
BDIR = bin

_OBJ = main.o Block.o Display.o Game.o GameState.o IntroState.o \
	   Texture.o World.o TextureAtlas.o PhysicalEntity.o Player.o \
	   ItemBlock.o Inventory.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	mkdir -p $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BDIR)/main.exe: $(OBJ)
	mkdir -p $(BDIR)
	$(CC) -o $@ $^ $(CFLAGS)

