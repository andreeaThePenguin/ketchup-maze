#ifndef __MENUS_MENUS_H__
#define __MENUS_MENUS_H__

#include <ProcessorBind.h>

typedef enum _MENU {
    MENU_MAIN_MENU,
    MENU_BOOT_MENU,
    MENU_SETUP,
    MENU_SHUTDOWN,
    MENU_GAME_EASY,
    MENU_GAME_MEDIUM,
    MENU_GAME_HARD,
    MENU_LEVEL
} MENU;

void StartMenus();

#endif //__MENUS_MENUS_H__
