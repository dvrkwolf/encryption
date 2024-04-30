#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define constants to regulate ascii values
#define MAX_ALPHA 90
#define MIN_ALPHA 65
#define MAX_BETA 122
#define MIN_BETA 97

char* readInput(int* inputLength);
char* encryptANDdecrypt(char* input, char* shifted, int randShiftBy, int encORdec);
void printOutput(char* input, int inputLength, int key, int encORdec);
int checkSpecial(char input, int encORdec);
int checkOverALPHA(char input, int randShiftBy, int encORdec);
int checkOverBETA(char input, int randShiftBy, int encORdec);
int charType(int specialChecked, int alphaChecked, int betaChecked);

int main (int argc, char* argv) {
	
	srand(time(NULL));
	int randShiftBy = rand() % 26 + 1;
	int quit = 0;
	int encORdec = 1;
	char chooseMode;
	int inputLength;
	int* lengthPointer;
	char* userInput;
	char* shifted;

	printf("Welcome to the Encryption/Decryption Machine. Would you like to Encrypt (E), Decrypt (D), or Quit (Q)?\n");
	
	while (quit != 1) {
		scanf("%c", &chooseMode);
		getchar();
		switch(chooseMode) {

			case 'E':
				encORdec = 0;

				inputLength = 0;
				lengthPointer = &inputLength;
				printf("You have chosen Encryption. Enter the text you wish to be encrypted:\n");
				userInput = readInput(lengthPointer);
				shifted = malloc(inputLength);
				encryptANDdecrypt(userInput, shifted, randShiftBy, encORdec);
				printOutput(shifted, inputLength, randShiftBy, encORdec);

				printf("Choose E, D, or Q again.\n");
				break;
			case 'D':
				encORdec = 1;

				inputLength = 0;
				lengthPointer = &inputLength;
				printf("You have chosen Decryption. Enter the text you wish decrypted:\n");
				userInput = readInput(lengthPointer);
				shifted = malloc(inputLength);
				printf("Enter your key:\n");
				scanf("%i", &randShiftBy);
				getchar();
				encryptANDdecrypt(userInput, shifted, randShiftBy, encORdec);
				printOutput(shifted, inputLength, randShiftBy, encORdec);

				printf("Choose E, D, or Q again.\n");
				break;

			case 'Q':
				printf("Quitting Now\n");
				quit = 1;
				break;

			default:
				printf("Invalid input. Try again.\n");
				break;
		}
	}

	return 0;

}


char* readInput(int* lengthPointer) {
	int index = 0;
	*lengthPointer = index;
	char bufferSize = 2;
	char* buffer;
	char* reallocBuffer;
	char charRead;

	buffer = malloc(bufferSize);

	while (charRead = fgetc(stdin), charRead != '\n' && charRead != EOF) {
	
		if (index == (bufferSize - 1)) {
			bufferSize *= 2;
			reallocBuffer = realloc(buffer, bufferSize);
			buffer = reallocBuffer;	
		}
		buffer[index] = charRead;
		index++;
		*lengthPointer = index;

	}

	if (index < (bufferSize - 1)) {
		reallocBuffer = realloc(buffer, (index + 1));
		buffer = reallocBuffer;
	}

	buffer[index] = '\n';
	*lengthPointer = index;
	return buffer;

}


char* encryptANDdecrypt(char* input, char* shifted, int randShiftBy, int encORdec) {
	int index = 0;
	int switchCheck;
	switch(encORdec) {

		case 0: // Encrypt
			while (input[index] != '\n' && input[index] != EOF) {
				switchCheck = charType(checkSpecial(input[index], encORdec), checkOverALPHA(input[index], randShiftBy, encORdec), checkOverBETA(input[index], randShiftBy, encORdec));
				switch(switchCheck) {
				
					case 1:
						shifted[index] = '-';
						index++;
						break;
					case 2:
						shifted[index] = MIN_ALPHA + (input[index]-MAX_ALPHA-1);
						shifted[index] += randShiftBy;
						index++;
						break;
					case 3:
						shifted[index] = MIN_BETA + (input[index]-MAX_BETA-1);
						shifted[index] += randShiftBy;
						index++;
						break;
					default:
						shifted[index] = input[index] + randShiftBy;
						index++;
						break;
				}

			

			}
			break;
		case 1: // Decrypt
			while (input[index] != '\n' && input[index] != EOF) {
				switchCheck = charType(checkSpecial(input[index], encORdec), checkOverALPHA(input[index], randShiftBy, encORdec), checkOverBETA(input[index], randShiftBy, encORdec));
				switch(switchCheck) {
				
					case 1:
						shifted[index] = ' ';
						index++;
						break;
					case 2:
						shifted[index] = MAX_ALPHA + (input[index]-MIN_ALPHA+1);
						shifted[index] -= randShiftBy;
						index++;
						break;
					case 3:
						shifted[index] = MAX_BETA + (input[index]-MIN_BETA+1);
						shifted[index] -= randShiftBy;
						index++;
						break;
					default:
						shifted[index] = input[index] - randShiftBy;
						index++;
						break;
				}

			

			}
			break;
		default:
			printf("An error occured. Terminating.\n");
			break;
	}

}


int checkSpecial(char input, int encORdec) {
	switch(encORdec) {
		case 0: //Encrypt
			if (!(65 <= input && input <= 90) && !(97 <= input && input <= 122)) {
				return 1;
			} else {
				return 0;
			}
			break;
		case 1: // Decrypt
			if (!(65 <= input && input <= 90) && !(97 <= input && input <= 122)) {
				return 1;
			} else {
				return 0;
			}
			break;
		default:
			printf("An error occured. Terminating.\n");
			break;
	}
		
			
}


int checkOverALPHA(char input, int randShiftBy, int encORdec) {
	switch(encORdec) {
			case 0: //Encrypt
				if ((input >= 65 && input <= 90 && input+randShiftBy > MAX_ALPHA)) {
					return 1;
				} else {
					return 0;
				}
				break;
			case 1: // Decrypt
				if ((input >= 65 && input <= 90 && input-randShiftBy < MIN_ALPHA)) {
					return 1;
				} else {
					return 0;
				}
				break;
			default:
				printf("An error occured. Terminating.\n");
				break;
		}


}

int checkOverBETA(char input, int randShiftBy, int encORdec) {
	switch(encORdec) {
		case 0: //Encrypt
			if ((input >= 96 && input <= 122 && input+randShiftBy > MAX_BETA)) {
				return 1;
			} else {
				return 0;
			}
			break;
		case 1: // Decrypt
			if ((input >= 96 && input <= 122 && input-randShiftBy < MIN_BETA)) {
				return 1;
			} else {
				return 0;
			}

			break;
		default:
			printf("An error occured. Terminating.\n");
			break;
	}

}


int charType(int specialChecked, int alphaChecked, int betaChecked) {
	if(specialChecked) {
		return 1;
	} else if(alphaChecked) {
		return 2;
	} else if(betaChecked) {
		return 3;
	} else {
	}

}


void printOutput(char* input, int inputLength, int key, int encORdec) {
	switch(encORdec) {
		case 0: //Encrypt
			printf("Your encrypted text is: ");
			for (int i = 0; i < inputLength; i++) {
				printf("%c", input[i]);
			}
			printf("\n");
			printf("Your KEY is: %i\n", key);
			break;
		case 1: // Decrypt
			printf("Your decrypted text with the KEY: %i is: ", key);
			for (int i = 0; i < inputLength; i++) {
				printf("%c", input[i]);
			}
			printf("\n");
			break;
		default:
			printf("An error occured. Terminating.\n");
			break;
	}
	

}