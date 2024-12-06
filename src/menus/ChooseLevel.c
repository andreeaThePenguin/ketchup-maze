#include "GameUtils.c"

MENU EnterLevelMenu()
{
	ClearScreen(EFI_TEXT_ATTR(EFI_LIGHTGRAY, EFI_RED));
	DrawDot();
	gST->ConOut->OutputString(gST->ConOut, L"Choose level (Press indicated key):");
	// WriteAt(1, 1, "Choose level (press the indicated key): ");
	WriteAt(10, 11, "Easy (e)");
	WriteAt(10, 12, "Medium (m)");
	WriteAt(10, 13, "Hard (h)");
	EFI_INPUT_KEY k1 = getKey();
	if (k1.UnicodeChar == 'e')	{
		return MENU_GAME_EASY;
	}
	if (k1.UnicodeChar == 'm')      {
                return MENU_GAME_MEDIUM;
        }
	if (k1.UnicodeChar == 'h')      {
                return MENU_GAME_HARD;
        }
	return MENU_LEVEL;

}
