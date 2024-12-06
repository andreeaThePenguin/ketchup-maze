#include "Menus.h"

#include <util/MemUtils.c>
#include <util/DrawUtils.h>

#include <config/BootConfig.h>
#include <config/BootEntries.h>

#include <Uefi.h>
#include <Protocol/LoadedImage.h>
#include <Protocol/GraphicsOutput.h>
#include <Protocol/DevicePathToText.h>
#include <Library/DebugLib.h>
#include <Library/UefiRuntimeServicesTableLib.h> // de aici putem folosi lucruri ca gST = SystemTable etc.
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DevicePathLib.h>
#include <Library/MemoryAllocationLib.h>
#include <loaders/Loaders.h>

// imagine maze 11 x 11
#define C EFI_RED
	static CHAR8 MazeImageR[] = {
        C, 0, C, C, C, C, C, C, C, C, C,
        C, 0, C, 0, C, 0, C, C, 0, 0, C,
        C, 0, C, 0, 0, 0, 0, C, C, 0, C,
        C, 0, C, C, C, C, 0, 0, 0, 0, C,
        C, 0, 0, 0, 0, C, C, C, C, 0, C,
        C, C, C, C, 0, C, 0, 0, 0, 0, C,
        C, C, 0, 0, 0, C, 0, C, C, C, C,
        C, C, 0, C, C, C, 0, C, C, C, C,
        C, C, 0, C, 0, 0, 0, 0, 0, 0, C,
        C, C, 0, C, C, C, C, C, C, C, C,
        C, C, 0, C, C, C, C, C, C, C, C,
        };


#undef C

#define C EFI_GREEN
	static CHAR8 MazeImageG[] = {
        C, 0, C, C, C, C, C, C, C, C, C,
        C, 0, C, 0, C, 0, C, C, 0, 0, C,
        C, 0, C, 0, 0, 0, 0, C, C, 0, C,
        C, 0, C, C, C, C, 0, 0, 0, 0, C,
        C, 0, 0, 0, 0, C, C, C, C, 0, C,
        C, C, C, C, 0, C, 0, 0, 0, 0, C,
        C, C, 0, 0, 0, C, 0, C, C, C, C,
        C, C, 0, C, C, C, 0, C, C, C, C,
        C, C, 0, C, 0, 0, 0, 0, 0, 0, C,
        C, C, 0, C, C, C, C, C, C, C, C,
        C, C, 0, C, C, C, C, C, C, C, C,
        };
#undef C

#define c EFI_RED
	static CHAR8 MazeImagem[] = {
	c, c, c, 0, c, c, c, c, c, c, c,
	c, 0, c, 0, 0, 0, c, 0, c, 0, c,
	c, 0, c, 0, c, 0, c, 0, 0, 0, c,
	c, 0, c, 0, c, 0, c, 0, c, 0, c,
	c, 0, 0, 0, c, 0, 0, 0, c, 0, c,
	c, 0, c, c, c, c, c, c, c, 0, c,
	c, 0, 0, 0, 0, 0, 0, c, 0, 0, c,
	c, 0, c, 0, c, c, 0, c, 0, 0, c,
	c, 0, c, 0, 0, c, 0, c, c, 0, c,
	c, 0, c, c, 0, 0, c, c, 0, 0, c,
	c, c, c, c, c, 0, c, c, c, c, c
	};
#undef c

static CHAR8 MazeImage[121]; // 11 x 11



// imagine selectare caracter
#define X EFI_GREEN
static CHAR8 Character[] = {
	X
};
#undef X

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"


static void DrawDot()
{
        // Curatare ecran + culori tematice
        //ClearScreen(EFI_TEXT_ATTR(EFI_WHITE, EFI_BLACK));

        // Desenare img
        UINTN width = 1;
        UINTN height = 1;
        UINTN wdraw = 1;
        UINTN hdraw = 1;
        DrawImage(wdraw+1, hdraw, Character, width, height);
}

static void DrawMaze()
{
        // Curatare ecran + culori tematice
        //ClearScreen(EFI_TEXT_ATTR(EFI_WHITE, EFI_BLACK));

        // Desenare maze easy
       	UINTN width = 11;
       	UINTN height = 11;
        UINTN wdraw = 1;
        UINTN hdraw = 1;
        DrawImage(wdraw+30, hdraw, MazeImage, width, height);
}

static void DrawMazeColor(CHAR8 maze_color)
{
        // Curatare ecran + culori tematice
        //ClearScreen(EFI_TEXT_ATTR(EFI_WHITE, EFI_BLACK));

        // Desenare maze
        UINTN width = 11;
        UINTN height = 11;
        UINTN wdraw = 1;
        UINTN hdraw = 1;
	if (maze_color == EFI_RED) {
 		DrawImage(wdraw+30, hdraw, MazeImageR, width, height);
		memcpy(MazeImage, MazeImageR, 121);
	} else if (maze_color == EFI_GREEN) {
		DrawImage(wdraw+30, hdraw, MazeImageG, width, height);
                memcpy(MazeImage, MazeImageG, 121);
	}
}

static void DrawMazem()
{
	UINTN width = 11;
	UINTN height = 11;
	UINTN wdraw = 1;
	UINTN hdraw = 1;
	DrawImage(wdraw + 30, hdraw, MazeImagem, width, height);
}

static void DrawMazeColorm(CHAR8 maze_color)
{
        // Curatare ecran + culori tematice
        //ClearScreen(EFI_TEXT_ATTR(EFI_WHITE, EFI_BLACK));

        // Desenare maze
        UINTN width = 11;
        UINTN height = 11;
        UINTN wdraw = 1;
        UINTN hdraw = 1;
        if (maze_color == EFI_RED) {
                DrawImage(wdraw + 30, hdraw, MazeImagem, width, height);
//                memcpy(MazeImagem, MazeImagem, 255);
        } else if (maze_color == EFI_GREEN) {
                DrawImage(wdraw + 30, hdraw, MazeImagem, width, height);
//                memcpy(MazeImagem, MazeImagem, 255);
        }
}



// preia tasta
static EFI_INPUT_KEY getKey()
{
        UINTN which = 0; // for error check
        ASSERT_EFI_ERROR(gBS->WaitForEvent(1, &gST->ConIn->WaitForKey, &which)); // error check
        EFI_INPUT_KEY key = {}; // declarare input
        EFI_STATUS status;
        status = gST->ConIn->ReadKeyStroke(gST->ConIn, &key); // primire tasta, returneaza EFI_STATUS
        return key;
}

// Functie pentru mutarea caracterului in maze
// Pos - pozitia pentru care se definesc mutarile posibile
// Height - inaltimea maze-ului
// Moves[] = array in care se stocheaza mutarile posibile
// Ordinea este w, a, s, d; de ex.: moves = 1, 0, 1, 0 - mutari posibile in sus (w) si jos (s) (in stanga si dreapta sunt pereti)
// Returneaza noua pozitie, in cazul in care o uitam

// Aveam warning de "unused function", dar functia e folosita in GameMenu.c

static int moveInMaze(int pos, int height, int moves[4])       {
        if(MazeImage[pos] == 1)   { // verificare fiecare pozitie posibila in maze
                EFI_INPUT_KEY key = getKey();
                if(moves[0] == 1)
                        if(key.UnicodeChar == L'w')      {
                                 MazeImage[pos] = 0;
                                 MazeImage[pos - height] = 1; // inaltimea maze-ului
                                 WriteAt(30, 15, "w");
                                 DrawMaze();
                                 return pos - height;
                         }
                if(moves[1] == 1)
                        if(key.UnicodeChar == L'a')      {
                                 MazeImage[pos] = 0;
                                 MazeImage[pos - 1] = 1;
                                 WriteAt(30, 15, "a");
                                 DrawMaze();
                                 return pos - 1;
                         }

                if(moves[2] == 1)
                        if(key.UnicodeChar == L's')      {
                                 MazeImage[pos] = 0;
                                 MazeImage[pos + height] = 1;
                                 WriteAt(30, 15, "s");
                                 DrawMaze();
                                 return pos + height;
                         }
                if(moves[3] == 1)
                        if(key.UnicodeChar == L'd')      {
                                 MazeImage[pos] = 0;
                                 MazeImage[pos + 1] = 1;
                                 WriteAt(30, 15, "d");
                                 DrawMaze();
                                 return pos + 1;
                         }
         }
        return -1;
}

static int moveInMazem(int pos, int height, int moves[4])       {
        if(MazeImagem[pos] == 1)   { // verificare fiecare pozitie posibila in maze
                EFI_INPUT_KEY key = getKey();
                if(moves[0] == 1)
                        if(key.UnicodeChar == L'w')      {
                                 MazeImagem[pos] = 0;
                                 MazeImagem[pos - height] = 1; // inaltimea maze-ului
                                 WriteAt(30, 15, "w");
                                 DrawMazem();
                                 return pos - height;
                         }
                if(moves[1] == 1)
                        if(key.UnicodeChar == L'a')      {
                                 MazeImagem[pos] = 0;
                                 MazeImagem[pos - 1] = 1;
                                 WriteAt(30, 15, "a");
                                 DrawMazem();
                                 return pos - 1;
                         }

                if(moves[2] == 1)
                        if(key.UnicodeChar == L's')      {
                                 MazeImagem[pos] = 0;
                                 MazeImagem[pos + height] = 1;
                                 WriteAt(30, 15, "s");
                                 DrawMazem();
                                 return pos + height;
                         }
                if(moves[3] == 1)
                        if(key.UnicodeChar == L'd')      {
                                 MazeImagem[pos] = 0;
				 MazeImagem[pos + 1] = 1;
                                 WriteAt(30, 15, "d");
                                 DrawMazem();
                                 return pos + 1;
                         }
         }
        return -1;
}


#pragma GCC diagnostic pop
