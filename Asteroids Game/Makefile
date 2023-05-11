all: compile link

compile:
	g++ -c source\\*.cpp -I"C:\Users\kaich\Documents\VS_library\SFML-2.5.1\include" -DSFML_STATIC

link:
	g++ -o asteroid_game.exe *.o -L"C:\Users\kaich\Documents\VS_library\SFML-2.5.1\lib" -lstdc++fs -lsfml-graphics-s -lsfml-window-s -lsfml-audio-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm  -lopenal32 -lflac -lvorbisenc -lvorbisfile -lvorbis -logg -lgdi32 -lsfml-main -mwindows 

clean:
	rm -f main *.o