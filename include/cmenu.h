#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char *name;
	bool (*func)();
} MenuItem;

typedef struct {
	int maxItems;
	int numItems;
	MenuItem items[];
} Menu;


/*
 * Allocates memory for a new Menu capable of holding numItems menu items, and returns
 * a pointer to it if successful.
 *
 * Returns NULL if any memory allocation fails or if numItems is less than 1
 * (a menu must have at least 1 option)
 */
Menu *menuNew(int numItems);


/*
 * Adds a new menu item to a menu.
 *
 * Takes the name of the menu item (which is the string that will be displayed)
 * and a function pointer taking no parameters and returning a bool. The function
 * is executed when the user selects this particular menu item from the menu. It
 * returns true if the menu should exit and stop prompting the user for input, and
 * false otherwise.
 *
 * This function returns true on a success,
 * and false on a failure (indicating memory allocation failed)
 */
bool menuAddItem(Menu *menu, char *name, bool (*func)());


/*
 * Runs the menu until one of its menu items returns true after it finishes executing.
 *
 * Does nothing if menu is NULL or if it does not contain any menu items.
 */
void menuRun(Menu *menu);


/*
 * Frees all memory associated with a menu.
 *
 * Does nothing if menu is NULL.
 */
void menuFree(Menu *menu);

