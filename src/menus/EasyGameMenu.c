#include "GameUtils.c"

CHAR8 maze_color_easy = EFI_RED;

MENU EnterGameMenuEasy()
{
	ClearScreen(EFI_BLACK);
        DrawMazeColor(maze_color_easy);

        // Preluare apasare tasta specifica
        WriteAt(1, 5, "Press p to play");

        // Schimbare culoare maze
        WriteAt(1, 6, "Press m to change maze color");
        EFI_INPUT_KEY k1 = getKey();

        if(k1.UnicodeChar == 'm') {
                WriteAt(1, 7, "Red (r)");
                WriteAt(1, 8, "Green (g)");
                EFI_INPUT_KEY k2 = getKey();
                if(k2.UnicodeChar == 'r') {
                        maze_color_easy = EFI_RED;
                        DrawMazeColor(maze_color_easy);
                }
                if(k2.UnicodeChar == 'g') {
                        maze_color_easy = EFI_GREEN;
                        DrawMazeColor(maze_color_easy);
                }
        }


	if(k1.UnicodeChar == 'p') { // daca am apasat PLAY
		MazeImage[10*11 + 2] = 1; // plasam caracterul in joc
		ClearScreen(EFI_BLACK);
		DrawMaze();
		WriteAt(1, 6, "Use WASD keys to move"); // indicatie tastatura
		while(TRUE)	{
			int h = 11; // inaltimea imaginii maze
			int chars[4] = {1, 0, 0, 0};

			// Verificare fiecare pozitie de pe traseul maze-ului
			// si configurare mutari posibile
			int cp; // pozitie curenta, in caz ca o uitam

			cp = moveInMaze(10*h+2, h, chars);

			chars[2] = 1; // adaugam si tasta 's' ca mutare

			// Exemplu: nu conteaza ordinea functiilor... tot se vor executa corect :)
			cp = moveInMaze(8*h+2, h, chars);
			cp = moveInMaze(9*h+2, h, chars);
                        // cp = moveInMaze(8*11+2, h, chars);
			cp = moveInMaze(7*h + 2, h, chars);

			chars[0] = 0;
			chars[3] = 1;
			cp = moveInMaze(6*h + 2, h, chars);
			chars[2] = 0;
			chars[1] = 1;
			cp = moveInMaze(6*h + 3, h, chars);
			chars[0] = 1;
			chars[3] = 0;
			cp = moveInMaze(6*h + 4, h, chars);
			chars[1] = 0;
			chars[2] = 1;
			cp = moveInMaze(5*h + 4, h, chars);
			chars[0] = 0;
			chars[1] = 1;
			cp = moveInMaze(4*h + 4, h, chars);
			chars[2] = 0;
			chars[3] = 1;
			cp = moveInMaze(4*h + 3, h, chars);
			cp = moveInMaze(4*h + 2, h, chars);
			chars[0] = 1;
			chars[1] = 0;
                        cp = moveInMaze(4*h + 1, h, chars);
			chars[3] = 0;
			chars[2] = 1;
			cp = moveInMaze(3*h + 1, h, chars);
                        cp = moveInMaze(2*h + 1, h, chars);
			cp = moveInMaze(1*h + 1, h, chars);
			chars[0] = 0;
			// cp = moveInMaze(0*h + 1, h, chars);
			// Win part
			if (MazeImage[0*h + 1] == 1)	{
				WriteAt(1, 7, "Congratulations!");
				WriteAt(1, 8, "You finished the maze!");
				WriteAt(1, 9, "Press ENTER to return");
				EFI_INPUT_KEY kwin = getKey();
				if (kwin.UnicodeChar == 0x0d)	{ // enter MdeModule code (ref in README)
					MazeImage[0*h + 1] = 0;
					return MENU_MAIN_MENU;
				}
			}
		}
	}
	return MENU_GAME_EASY;
}
