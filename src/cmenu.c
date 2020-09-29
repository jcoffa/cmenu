#include "cmenu.h"


/***************************************
 * STATIC (PRIVATE) INTERNAL FUNCTIONS *
 ***************************************/

/*
 * Continually prompts the user until they enter a valid index for one of the menu items.
 * Menu items are indexed starting from 1 (... at least from the users persepctive.
 * They are indexed from 0 internally like normal arrays).
 *
 * The numItems parameter must be >= 1.
 */
static int getItemInput_(int numItems) {
	bool redo;
	int choice;

	do {
		printf("Select [1-%d]> ", numItems);
		scanf("%d", &choice);
		redo = choice < 1 || choice > numItems;

		if (redo) {
			printf("Invalid option '%d'\n", choice);
		}
	} while (redo);

	return choice;
}


/**************************
 * API (PUBLIC) FUNCTIONS *
 **************************/


Menu *menuNew(int numItems) {
	if (numItems < 1) {
		return NULL;
	}

	Menu *toReturn = malloc(sizeof(Menu) + (numItems * sizeof(MenuItem)));
	if (!toReturn) {
		return NULL;
	}

	toReturn->maxItems = numItems;
	toReturn->numItems = 0;

	return toReturn;
}

bool menuAddItem(Menu *menu, char *name, bool (*func)()) {
	if (!menu || !name || !func || menu->numItems == menu->maxItems) {
		return false;
	}

	MenuItem item;
	item.name = malloc(strlen(name) + 1);
	if (!item.name) {
		return false;
	}
	strcpy(item.name, name);
	item.func = func;

	menu->items[(menu->numItems)++] = item;
	return true;
}

void menuRun(Menu *menu) {
	if (!menu || menu->numItems <= 0) {
		return;
	}

	bool stop;
	int choice;

	do {
		for (int i = 0; i < menu->numItems; i++) {
			printf("%2d. %s\n", i+1, menu->items[i].name);
		}

		choice = getItemInput_(menu->numItems);

		printf("\n");
		stop = (menu->items[choice-1]).func();
	} while (!stop);
}

void menuFree(Menu *menu) {
	if (!menu) {
		return;
	}

	for (int i = 0; i < menu->numItems; i++) {
		free(menu->items[i].name);
	}
	free(menu);
}

