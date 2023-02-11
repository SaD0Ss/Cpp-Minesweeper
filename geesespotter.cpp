#include "geesespotter_lib.h"


char *createBoard(std::size_t xdim, std::size_t ydim);
void cleanBoard(char *board);
void printBoard(char *board, std::size_t xdim, std::size_t ydim);
void hideBoard(char *board, std::size_t xdim, std::size_t ydim);
int mark(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc);
int mark(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc) {
    return 0;
}
void computeNeighbors(char *board, std::size_t xdim, std::size_t ydim);
void computeNeighbors(char *board, std::size_t xdim, std::size_t ydim) {}
int reveal(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc);
int reveal(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc) {
    return 0;
}
bool isGameWon(char *board, std::size_t xdim, std::size_t ydim);
bool isGameWon(char *board, std::size_t xdim, std::size_t ydim) {
    return 0;
}

char *createBoard(std::size_t xdim, std::size_t ydim) {
    int size = xdim * ydim;
    char arr[size] {0};
    char *array;
    array = arr;
    return array;
}

void cleanBoard(char *board) {
    delete board;
    board = nullptr;
}