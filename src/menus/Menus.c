#include <Uefi.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/BaseLib.h>
#include "Menus.h"

// Aici se face intrarea in functiile tuturor meniurilor posibile

MENU EnterMainMenu(BOOLEAN first);
MENU EnterSetupMenu();
MENU EnterBootMenu();
MENU EnterGameMenu();
MENU EnterLevelMenu();

void StartMenus() {
    MENU current_menu = MENU_MAIN_MENU;
    BOOLEAN first = TRUE;

    while(TRUE) {
        // choose the correct menu to display
        switch(current_menu) {
            case MENU_MAIN_MENU:
                current_menu = EnterMainMenu(first);
                break;

            case MENU_BOOT_MENU:
                current_menu = EnterBootMenu();
                break;

            case MENU_SETUP:
                current_menu = EnterSetupMenu();
                break;

            case MENU_SHUTDOWN:
                gRT->ResetSystem(EfiResetShutdown, 0, 0, "shutdown");
                CpuDeadLoop();
                break;

	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"


	    case MENU_GAME_EASY:
		current_menu = EnterGameMenuEasy();
		break;

	    case MENU_GAME_MEDIUM:
                current_menu = EnterGameMenuMedium();
                break;

	    case MENU_GAME_HARD:
                current_menu = EnterGameMenuHard();
                break;

	#pragma GCC diagnostic pop

	    case MENU_LEVEL:
		current_menu = EnterLevelMenu();
		break;
        }

        first = FALSE;
    }

}
