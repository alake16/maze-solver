/* maze.c
 * Andrew Lake
 * COMP 310
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <unistd.h>

typedef struct {
	char* fileName;
	size_t rows;
	size_t cols;
	int** solution;
	int** visited;
	int startX;
	int startY;
	int endX;
	int endY;
	FILE* journalFile;
	char *journalFileName;
} Maze;

typedef struct {
	int row;
	int col;
	int previousVal;
	int newVal;
} JournalEntryValues;

void preprocessMazeFile(Maze* maze);
void allocate2DArrays(Maze* maze);
void firstRunThrough(Maze* maze);
void findMazeExit(Maze* maze);
bool isValidMove(Maze* maze, int x, int y);
int min(int a, int b);
void solveMaze(Maze *maze, int x, int y, int currentDistance);
int countDigits(int num);
void printMaze(Maze* maze);
void writeToJournal(Maze* maze, int x, int y, int previousVal, int newVal);
void solveMazeFromJournal(Maze* maze);
void updateMazeFromEntry(Maze *maze, char* entry);
JournalEntryValues parseEntry(Maze* maze, char* entry);

int main(int argc, char* argv[]) {
	Maze maze;
	int opt = 0;
	bool inputSpecified = false;
	bool loadFromJournalFlag = false;
	bool writeToJournalFlag = false;
	while ((opt = getopt(argc, argv, "i:j:o:")) != -1) {
		switch(opt) {
			case 'i':
				printf("input file name %s \n", optarg);
				inputSpecified = true;
				maze.fileName = optarg;
				break;
			case 'j':
				loadFromJournalFlag = true;
				maze.journalFileName = optarg;
				break;
			case 'o':
				writeToJournalFlag = true;
				maze.journalFileName = optarg;
				break;
			case ':':  
                printf("option needs a value\n");  
                break; 
			case '?':
				printf("unkown option: %c \n", optopt);
				break;
			default:
				break;
		}
	}

	if (!inputSpecified) {
		printf("ERROR: must specify an input file as following:\n-i [file_name]\n");
		exit(1);
	}

	if (!loadFromJournalFlag && !writeToJournalFlag) {
		printf("ERROR: must specify either -j [file_name] OR -o [file_name}:\n");
		exit(1);
	}

    if (loadFromJournalFlag) {
    	printf("loadFromJournalFlag set to true\n");
    }
    else if (writeToJournalFlag) {
    	printf("writeToJournalFlag set to true\n");
    }
	printf("===== Preprocessing Maze File =====\n");
	preprocessMazeFile(&maze);
	printf("===== Allocating Appropriate Array =====\n");
	allocate2DArrays(&maze);
	firstRunThrough(&maze);
	findMazeExit(&maze);
	printf("Starting x coord: %i\n", maze.startX);
	printf("Starting y coord: %i\n", maze.startY);
	printf("Maze end X: %i\n", maze.endX);
	printf("Maze end Y: %i\n", maze.endY);
	printf("# Cols (including null terminating characater): %zu\n", maze.cols);
	printf("===== Solving Maze =====\n");
	if (writeToJournalFlag) {
		solveMaze(&maze, maze.startX, maze.startY, 0);
	}
	else {
		solveMazeFromJournal(&maze);
	}
	printf("===== Printing Solved Maze =====\n");
	printMaze(&maze);
	return 0;
}

void preprocessMazeFile(Maze* maze) {
	FILE *fp; 
	fp = fopen(maze -> fileName,"r");
	// count number of rows and cols in maze file
	char *line = NULL;
    size_t len = 0;
    size_t cols = 0;
    size_t rows = 0;
	while(getline(&line, &len, fp)) {
		if (strcmp(line, "") != 0) {
			size_t length = strlen(line);
			if (length > cols) {
				cols = length;
			}
			rows++;
		}
		// at eof
		else {
			break;
		}
	}
	maze -> cols = cols;
	maze -> rows = rows;
	fclose(fp);
	return;
}

void allocate2DArrays(Maze* maze) {
	// allocate 2D array for solution
	int** a = (int**)malloc(maze -> rows * sizeof(int*));
	for (int row = 0; row < maze -> rows; row++) {
		a[row] = (int*)malloc(maze -> cols * sizeof(int));
	}
	// allocate 2D array for visited
	int** b = (int**)malloc(maze -> rows * sizeof(int*));
	for (int row = 0; row < maze -> rows; row++) {
		b[row] = (int*)malloc(maze -> cols * sizeof(int));
	}
	maze -> solution = a;
	maze -> visited = b;
	return;
}

// fills maze array with appropriate values to begin solving algorithm
void firstRunThrough(Maze* maze) {
	FILE *fp; 
	fp = fopen(maze -> fileName,"r");
	for (int row = 0; row < maze -> rows; row++) {
		char *line = NULL;
    	size_t len = 0;
    	getline(&line, &len, fp);
		for (int col = 0; col < maze -> cols - 1; col++) {
			if (line[col] == 'b') {
				maze -> solution[row][col] = -1;
			}
			else if (line[col] == 's') {
				maze -> solution[row][col] = 0;
				maze -> startX = row;
				maze -> startY = col;
			}
			// check if it's unreachable
			else {
				maze -> solution[row][col] = INT_MAX;
			}
		}
	}
	fclose(fp);
}

void findMazeExit(Maze* maze) {
	// check if maze exit is in first or last row
	for (int row = 0; row < maze -> rows; row += maze -> rows - 1) {
		for (int col = 0; col < maze -> cols - 1; col++) {
			if (maze -> solution[row][col] == INT_MAX) {
				maze -> endX = row;
				maze -> endY = col;
				return;
			}
		}
	}
	// check if maze exit is in first or last col
	for (int col = 0; col < maze -> cols - 1; col += maze -> cols - 2) {
		for (int row = 0; row < maze -> rows; row++) {
			if (maze -> solution[row][col] == INT_MAX) {
				maze -> endX = row;
				maze -> endY = col;
				return;
			}
		}
	}
	return;
}

bool isValidMove(Maze* maze, int x, int y) {
	// check that coord is within bounds
	if (x >= 0 && x < maze -> rows && y >= 0 && y < (maze -> cols - 1)) {
		// check that coord is not a barrier and hasn't already been visited
		if (maze -> solution[x][y] != -1 && maze -> visited[x][y] != 1) {
			return true;
		}
		return false;
	}
	return false;
}

int min(int a, int b) {
	return a < b ? a : b;
}

void solveMaze(Maze *maze, int x, int y, int currentDistance) {
	// update distance and call for all valid positions
	int previousDistance = maze -> solution[x][y];
	int newDistance = min(maze -> solution[x][y], currentDistance);
	writeToJournal(maze, x, y, previousDistance, newDistance);
	maze -> solution[x][y] = newDistance;
	// printMaze(maze);
	// printf("\n");
	// printf("\n");
	if (x == maze -> endX && y == maze -> endY) {
		return;
	}
	maze -> visited[x][y] = 1;

	// move left
	if (isValidMove(maze, x, y - 1)) {
		solveMaze(maze, x, y - 1, currentDistance + 1);
	}
	// move right
	if (isValidMove(maze, x, y + 1)) {
		solveMaze(maze, x, y + 1, currentDistance + 1);
	}
	// move up
	if (isValidMove(maze, x - 1, y)) {
		solveMaze(maze, x - 1, y, currentDistance + 1);
	}
	// move down
	if (isValidMove(maze, x + 1, y)) {
		solveMaze(maze, x + 1, y, currentDistance + 1);
	}
	maze -> visited[x][y] = 0;
}

// counts number of digits in a number for better formatted printing of solution array
int countDigits(int num) {
	int count = 0;
	if (num == -1) {
		return 2;
	}
	while (num != 0) {
		num /= 10;
		count++;
	}
	return count;
}

void printMaze(Maze* maze) {
	for (int row = 0; row < maze -> rows; row++) {
		for (int col = 0; col < maze -> cols - 1; col++) {
			// update value of unreachable spots
			if (maze -> solution[row][col] == INT_MAX) {
				maze -> solution[row][col] = 404;
			}
			if (col != 0) {
				switch(countDigits(maze -> solution[row][col])) {
					case 0: 
						printf("    ");
						break;
					case 1:
						printf("    ");
						break;
					case 2: 
						printf("   ");
						break;
					case 3:
						printf("  ");
						break;
				}
			}
			printf("%i", maze -> solution[row][col]);
		}
		printf("\n");
	}
}

void writeToJournal(Maze* maze, int x, int y, int previousVal, int newVal) {
	// <row> <column> <previous cell value> <new cell value>
	maze -> journalFile = fopen(maze -> journalFileName, "a");
	fprintf (maze -> journalFile, "%i %i %i %i\n",  x, y, previousVal, newVal);
	fclose(maze -> journalFile);
	return;
}

void solveMazeFromJournal(Maze* maze) {
	maze -> journalFile = fopen(maze -> journalFileName, "r");
    char entry[100];
	while (fgets(entry, 1000, maze -> journalFile) != NULL) {
		updateMazeFromEntry(maze, entry);
	}
    fclose(maze -> journalFile);
}

void updateMazeFromEntry(Maze *maze, char* entry) {
	JournalEntryValues values = parseEntry(maze, entry);
	if (isValidMove(maze, values.row, values.col)) {
		maze -> solution[values.row][values.col] = values.newVal;
	}
	else {
		printf("ERROR: invalid move given from journal\n");
		exit(1);
	}
}

JournalEntryValues parseEntry(Maze* maze, char* entry) {
	char* token;
	const char delim[2] = " ";
	token = strtok(entry, delim);
	JournalEntryValues values;

	for (int i = 0; i < 4; i++) {
		switch(i) {
			case 0:
				values.row = atoi(token);
				break;
			case 1: 
				values.col = atoi(token);
				break;
			case 2:
				values.previousVal = atoi(token);
				break;
			case 3:
				values.newVal = atoi(token);
				break;
			default:
				break;
		}
		// update the maze and make sure to check for walls n stuff
		token = strtok(NULL, delim);
	}
	return values;
}