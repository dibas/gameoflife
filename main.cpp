/* Conway's Game of Life - Implementation in C++
 * Author: dibas
 * Started and finished on: 6 Dec 2016
 */
#include <iostream>
#include <cstdlib>
#include <ctime>

#include <chrono>
#include <thread>

#define FIELD_WIDTH 64
#define FIELD_HEIGHT 32

using namespace std;

void printField();
void copyTempArrayToField();
int getNeighbourCount(int x, int y);

int stepCycle();

char field[FIELD_HEIGHT][FIELD_WIDTH];

char temp_field[FIELD_HEIGHT][FIELD_WIDTH];


int generation = 0;
int alive = 0;

int main(int argc, char* argv[]) {
	srand(time(0));

	// Fill field randomly
	for(int i = 0; i < FIELD_HEIGHT; i++) {
		for(int j = 0; j < FIELD_WIDTH; j++) {
			field[i][j] = rand() % 2;
		}
	}

	printField();
	getchar();	// Wait for input before starting cycle

	while(true) {
		printField();

		memset(temp_field, 0, sizeof(temp_field));
		
		stepCycle();
		
		memset(field, 0, sizeof(field));		
		copyTempArrayToField();

		generation += 1;

		this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

int stepCycle() {
	alive = 0;

	for(int i = 0; i < FIELD_HEIGHT; i++) {
		for(int j = 0; j < FIELD_WIDTH; j++) {
			int neighbourCells = getNeighbourCount(i, j);

			if(neighbourCells == 3) {
				temp_field[i][j] = 1;
				alive += 1;
			}
			else if(neighbourCells == 2) {
				if(field[i][j] == 1) {
					temp_field[i][j] = 1;
					alive += 1;
				}
			}
			else if(neighbourCells < 2) {
				temp_field[i][j] = 0;
			}
			else if(neighbourCells > 3) {
				temp_field[i][j] = 0;
			}
		}
	}

	return alive;
}

void printField() {
	system("clear");

	cout << "--------------------------------------------------------------------" << endl;
	cout << "|           Conway's Game of Life     |     by dibas               |" << endl;
	cout << "|         Gen: " << generation << "                      |     Alive: " << alive << "               |" << endl;
	cout << "--------------------------------------------------------------------" << endl;

	for(int i = 0; i < FIELD_HEIGHT; i++) {
		for(int j = 0; j < FIELD_WIDTH; j++) {
			if(field[i][j] == 0) {
				cout << " -";
			}
			else {
				cout << " *";
			}
		}
		
		cout << endl;
	}
}

int getNeighbourCount(int i, int j) {	// Where i is row and j is column
	if(i >= FIELD_HEIGHT) { return 0; }
	if(j >= FIELD_WIDTH) { return 0; }

	int result = 0;

	if(i > 0 && j > 0) {
		result += field[i-1][j-1];	// Top left
	}

	if(j > 0) {
		result += field[i][j-1];	// Center left
	}

	if(i > 0 && j < (FIELD_WIDTH - 1)) {
		result += field[i-1][j+1];	// Top right
	}

	if(i > 0) {
		result += field[i-1][j];	// Top center
	}

	if(j < (FIELD_WIDTH - 1)) {
		result += field[i][j+1];	// Center right
	}

	if(i < (FIELD_HEIGHT -1) && j > 0) {
		result += field[i+1][j-1];	// Bottom left
	}

	if(i < (FIELD_HEIGHT - 1)) {
		result += field[i+1][j];	// Bottom center
	}

	if(i < (FIELD_HEIGHT - 1) && j < (FIELD_WIDTH -1)) {
		result += field[i+1][j+1];	// Bottom right

	}

	return result;
}

void copyTempArrayToField() {

	for(int i = 0; i < FIELD_HEIGHT; i++) {
		for(int j = 0; j < FIELD_WIDTH; j++) {
			field[i][j] = temp_field[i][j];
		}
	}
}
