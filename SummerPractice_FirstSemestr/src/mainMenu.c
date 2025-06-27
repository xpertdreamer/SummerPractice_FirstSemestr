#include "include/mainMenu.h"
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>

int arrowMenu() {
	int choice = 1;
	int key;

	do {
		system("cls");
		printf("\t=== МЕНЮ ===\n");
		printf("%s1. Ввести массив чисел\n", choice == 1 ? ">" : " ");
		printf("%s2. Сгенерировать массив чисел\n", choice == 2 ? ">" : " ");
		printf("%s3. Считать массив из файла\n", choice == 3 ? ">" : " ");
		printf("%s4. Выход\n", choice == 4 ? ">" : " ");

		key = _getch();

		if (key == 0 || key == 224) {
			key = _getch();
			switch (key) {
			case 72: // Стрелка вверх
				if (choice > 1) choice--;
				break;
			case 80: // Стрелка вниз
				if (choice < 4) choice++;
				break;
			}
		}
	} while (key != 13); // Enter

	return choice;
}
