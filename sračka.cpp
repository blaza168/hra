#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ERRORS 10


void renderProgress(int errors)
{
	switch(errors) {
		case 2:
			printf(" //		  \\\\\n");
		case 1:
			printf("//			\\\\");
			break;
	}
}

void initScreen(int errors, char* shown) {
	system("cls");
	printf("Pocet chyb: %d/%d", errors, MAX_ERRORS);
	printf("\n");
	printf("Slovo: %s", shown);
	printf("\n");
	printf("Slovo ma %d znaku", strlen(shown));
	printf("\n\n\n");
	renderProgress(errors);
}

char* getText() {
	char buffer[101]; // 100 chars + enter
	
	printf("Zadej text k uhadnuti: ");
	scanf("%100[^\n]s", buffer);
	
	char* text = (char*)malloc(strlen(buffer) * sizeof(char));
	strcpy(text, buffer);

	return text;
}

void renderLoseScreen() {
	printf("Prohráls");
}

void renderWinScreen() {
	printf("Vyhráls");
}

char loadChar() {
	getchar(); // Fucking enters ...
	char c = ' ';
	printf("Zadej znak:");
	scanf("%c", &c);
	printf("%c", c);
}

bool isInWord(char* text, char c) {
	for (int i = 0; i < strlen(text); i++) {
		if (text[i] == c) {
			return true;
		}
	}
	
	return false;
}

void applyChanges(char* text, char* shown, char c) {
	for (int i = 0; i < strlen(text); i++) {
		if (text[i] == c) {
			shown[i] = c;
		}
	}
}

char* createShown(char* text) {
	char* shown = (char*)malloc(strlen(text));
	for (int i = 0; i < strlen(text); i++) {
		shown[i] = '_';
	}
	return shown;
}

int main()
{
	int errors = 0;
	int success = 0;
	char* text = getText();
	char* shown = createShown(text);
	printf("%d", strlen(text));
	
	while (errors != MAX_ERRORS && success != strlen(text)) {
		initScreen(errors, shown);
		char c = loadChar();
		if (isInWord(text, c)) {
			applyChanges(text, shown, c);
			success++;
		} else {
			errors++;
		}
	}
	
	if (errors == MAX_ERRORS) {
		renderLoseScreen();
	} else {
		renderWinScreen();
	}
	
	printf("\n\n\n");
	system("pause");
}

