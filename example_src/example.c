#include "cmenu.h"

bool say_hello();
bool c_to_f();
bool f_to_c();
bool quit();


int main(void) {
	Menu *menu = menuNew(4);

	menuAddItem(menu, "Say Hello", say_hello);
	menuAddItem(menu, "C to F", c_to_f);
	menuAddItem(menu, "F to C", f_to_c);
	menuAddItem(menu, "Quit", quit);

	menuRun(menu);
	menuFree(menu);
	
	return 0;
}


bool say_hello() {
	printf("Hello! o/\n");

	return false;
}

bool c_to_f() {
	float temp;
	printf("Enter temperature in degrees C: ");
	scanf("%f", &temp);
	printf("%.2f degrees C = %.2f degrees F\n", temp, temp*9/5 + 32);

	return false;
}

bool f_to_c() {
	float temp;
	printf("Enter temperature in degrees F: ");
	scanf("%f", &temp);
	printf("%.2f degrees F = %.2f degrees C\n", temp, (temp-32)*5/9);

	return false;
}

bool quit() {
	puts("Goodbye.");

	return true;
}

