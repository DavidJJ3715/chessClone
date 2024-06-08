noflags =
flags = -g -fsanitize=leak
errflags = -Wall -Wextra
linkedLibraries = -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -lmingw32
dependencies = Makefile main.cpp definitions.h initObjects.h king.h queen.h knight.h bishop.h rook.h pawn.h piece.h
shareLinkedLibraries = SDL2_image.dll SDL2_ttf.dll SDL2.dll

main: $(dependencies)
	g++ $(errflags) main.cpp -o main -IC:\Users\david\Downloads\Code\SDL2\include -LC:\Users\david\Downloads\Code\SDL2\lib $(linkedLibraries)

chess: $(dependencies)
	g++ $(errflags) -static main.cpp -o chess $(shareLinkedLibraries)
	powershell Remove-Item C:\Users\david\Desktop\share\chess.exe
	powershell move chess.exe C:\Users\david\Desktop\share
	powershell Remove-Item C:\Users\david\Desktop\chess.zip
	powershell Compress-Archive C:\Users\david\Desktop\share C:\Users\david\Desktop\chess.zip
	powershell clear

.PHONY: clean

clean:
	rm -f main.exe