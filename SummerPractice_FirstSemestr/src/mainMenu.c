#include "include/mainMenu.h"
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>

int arrowMenu() {
	int choice = 1;
	int key;

	do {
		system("cls");
		printf("\t=== ���� ===\n");
		printf("%s1. ������ ������ �����\n", choice == 1 ? ">" : " ");
		printf("%s2. ������������� ������ �����\n", choice == 2 ? ">" : " ");
		printf("%s3. ������� ������ �� �����\n", choice == 3 ? ">" : " ");
		printf("%s4. �����\n", choice == 4 ? ">" : " ");

		key = _getch();

		if (key == 0 || key == 224) {
			key = _getch();
			switch (key) {
			case 72: // ������� �����
				if (choice > 1) choice--;
				break;
			case 80: // ������� ����
				if (choice < 4) choice++;
				break;
			}
		}
	} while (key != 13); // Enter

	return choice;
}
