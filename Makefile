build:
	g++ -w -std=c++14 -Wfatal-errors \
	./src/*.cpp ./src/components/*.cpp \
	-o game \
        -I"./src/include" \
	-I"./lib/lua" \
	-L"./lib/lua" \
	-llua \
	-lSDL2 \
	-lSDL2_image \
	-lSDL2_ttf \
	-lSDL2_mixer;

clean:
	rm ./game;

run:
	./game;
