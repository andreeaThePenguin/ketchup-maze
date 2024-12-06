#include "GameUtils.c"

CHAR8 maze_color_medium = EFI_RED;

MENU EnterGameMenuMedium()
{

	ClearScreen(EFI_BLACK);
	DrawMazeColorm(maze_color_medium);

	// Preluare apasare tasta specifica
	WriteAt(30, 18, "Press p to play");

	// Schimbare culoare maze
	WriteAt(30, 21, "Press m to change maze color");
        EFI_INPUT_KEY k1 = getKey();

        if(k1.UnicodeChar == 'm') {
                WriteAt(30, 19, "Red (r)");
                WriteAt(30, 20, "Green (g)");
                EFI_INPUT_KEY k2 = getKey();
                if(k2.UnicodeChar == 'r') {
                        maze_color_medium = EFI_RED;
                        DrawMazeColorm(maze_color_medium);
                }
                if(k2.UnicodeChar == 'g') {
                        maze_color_medium = EFI_GREEN;
                        DrawMazeColorm(maze_color_medium);
                }
        }


	if(k1.UnicodeChar == 'p') { // daca am apasat PLAY
		MazeImagem[10*11 + 5] = 1; // plasam caracterul in joc
		ClearScreen(EFI_BLACK);
		DrawMazem();
		WriteAt(30, 17, "Use WASD keys to move"); // indicatie tastatura
		while(TRUE)	{
			int h = 11; // inaltimea imaginii maze
			int chars[4] = {1, 0, 0, 0};

			// Verificare fiecare pozitie de pe traseul maze-ului
			// si configurare mutari posibile
			int cp; // pozitie curenta, in caz ca o uitam

			cp = moveInMazem(10*h+5, h, chars);

			chars[0] = 0; // adaugam si tasta 's' ca mutare
			chars[1] = 1;
			chars[2] = 1;
			chars[3] = 1;
			cp = moveInMazem(9*h+5, h, chars);


			chars[0] = 1;
			chars[1] = 1;
			chars[2] = 0;
			chars[3] = 1;
			cp = moveInMaze(9*h+6, h, chars);

			chars[0] = 0;
                        chars[1] = 1;
                        chars[2] = 0;
                        chars[3] = 1;
                        cp = moveInMazem(9*h+7, h, chars);

			chars[0] = 1;
			chars[1] = 0;
			chars[2] = 0;
			chars[3] = 1;
			cp = moveInMazem(9*h+4, h, chars);


			chars[0] = 0;
                        chars[1] = 1;
                        chars[2] = 1;
                        chars[3] = 0;
                        cp = moveInMazem(8*h+4, h, chars);

			chars[0] = 1;
                        chars[1] = 0;
                        chars[2] = 0;
                        chars[3] = 1;
                        cp = moveInMazem(8*h+3, h, chars);

			chars[0] = 1;
                        chars[1] = 0;
                        chars[2] = 1;
                        chars[3] = 0;
                        cp = moveInMazem(7*h+3, h, chars);

			chars[0] = 0;
                        chars[1] = 1;
                        chars[2] = 1;
                        chars[3] = 1;
                        cp = moveInMazem(6*h+3, h, chars);

			// branch1
			chars[0] = 0;
                        chars[1] = 1;
                        chars[2] = 0;
                        chars[3] = 1;
                        cp = moveInMazem(6*h+2, h, chars);

			chars[0] = 1;
                        chars[1] = 0;
                        chars[2] = 1;
                        chars[3] = 1;
                        cp = moveInMazem(6*h+1, h, chars);

			chars[0] = 1;
                        chars[1] = 0;
                        chars[2] = 1;
                        chars[3] = 0;
                        cp = moveInMazem(7*h+1, h, chars);
			cp = moveInMazem(8*h+1, h, chars);
			cp = moveInMazem(5*h+1, h, chars);

			chars[2] = 0;
			cp = moveInMazem(9*h+1, h, chars);



			// branch2
			chars[0] = 0;
                        chars[1] = 1;
                        chars[2] = 0;
                        chars[3] = 1;
                        cp = moveInMazem(6*h+4, h, chars);

			chars[0] = 1;
                        chars[1] = 0;
                        chars[2] = 1;
                        chars[3] = 1;
                        cp = moveInMazem(4*h+1, h, chars);

			chars[0] = 0;
                        chars[1] = 1;
                        chars[2] = 0;
                        chars[3] = 1;
                        cp = moveInMazem(4*h+2, h, chars);

			chars[0] = 1;
                        chars[1] = 1;
                        chars[2] = 0;
                        chars[3] = 0;
                        cp = moveInMazem(4*h+3, h, chars);

			chars[0] = 1;
                        chars[1] = 0;
                        chars[2] = 1;
                        chars[3] = 0;
                        cp = moveInMazem(3*h+3, h, chars);

			chars[0] = 1;
                        chars[1] = 0;
                        chars[2] = 1;
                        chars[3] = 0;
                        cp = moveInMazem(2*h+3, h, chars);

			chars[0] = 1;
                        chars[1] = 0;
                        chars[2] = 1;
                        chars[3] = 1;
                        cp = moveInMazem(1*h+3, h, chars);

			// cp = moveInMaze(0*h + 1, h, chars);
			// Win part
			if (MazeImagem[0*h + 3] == 1)	{
				WriteAt(30, 18, "Congratulations! You finished the maze!");
				WriteAt(30, 19, "Press ENTER to return to main menu");
				EFI_INPUT_KEY kwin = getKey();
				if (kwin.UnicodeChar == 0x0d)	{ // enter MdeModule code (ref in README)
					MazeImagem[0*h + 3] = 0;
					return MENU_MAIN_MENU;
				}
			}
		}
	}
	return MENU_GAME_MEDIUM;
}
