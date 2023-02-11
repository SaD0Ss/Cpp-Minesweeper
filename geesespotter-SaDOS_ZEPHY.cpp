#include "geesespotter_lib.h"

char *createBoard(std::size_t xdim, std::size_t ydim);
char *createBoard(std::size_t xdim, std::size_t ydim) {
    char *arr = new char[xdim * ydim]{};
    for (std::size_t i{0}; i <= (xdim * ydim); ++i) {
        arr[i] = 0;
    }
    return arr;
}

void cleanBoard(char *board);
void cleanBoard(char *board) {
    delete[] board;
    board = nullptr;
}

void printBoard(char *board, std::size_t xdim, std::size_t ydim);
void printBoard(char *board, std::size_t xdim, std::size_t ydim) {
    unsigned int mark{16};
    unsigned int hide{32};
    int index{0};
    for (std::size_t j{0}; j < ydim; ++j) {
        for (std::size_t k{0}; k < xdim; ++k) {
            if (board[index] & mark) {
                std::cout << "M";
            } else if (board[index] & hide) {
                std::cout << "*";
            } else {
                std::cout << (board[index] & 0b00001111);
            }
            ++index;    
        }
        std::cout << std::endl;
    }
}

void hideBoard(char *board, std::size_t xdim, std::size_t ydim);
void hideBoard(char *board, std::size_t xdim, std::size_t ydim) {
    unsigned int hide{32};
    for (std::size_t k{0}; k < (xdim * ydim); ++k) {
        board[k] |= hide;
    }   
}

int mark(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc);
int mark(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc) {
    unsigned int hide{32};
    unsigned int mark{16};
    if (!(board[xdim*yloc + xloc] & hide)) {
        return 2;
    } else {
        board[xdim*yloc + xloc] ^= mark;
    }
    return 0;
}

int reveal(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc);
int reveal(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc) {
    unsigned int hide{0b00100000};
    unsigned int change_hide{0b11011111};
    unsigned int mark{0b00010000};
    if ((board[xdim*yloc + xloc] & mark)) {
        return 1;
    } else if ((board[xdim*yloc + xloc] & (0b00001111)) == (0b00001001)) {
        board[xdim*yloc + xloc] &= change_hide;
        return 9;
    } else {
        if (((board[xdim*yloc + xloc])&(0b00001111)) == 0) {
            if (xloc != 0) {
                if (!((board[xdim*yloc + xloc-1] & mark))) {
                    board[xdim*yloc + xloc-1] &= change_hide;
                }
                if (yloc != 0) {
                    if (!((board[xdim*(yloc-1) + xloc] & mark))) {
                        board[xdim*(yloc-1) + xloc] &= change_hide;
                    }
                    if (!((board[xdim*(yloc-1) + xloc-1] & mark))) {
                        board[xdim*(yloc-1) + xloc-1] &= change_hide;
                    }
                }
                if (yloc != ydim-1) {
                    if (!((board[xdim*(yloc+1) + xloc-1] & mark))) {
                        board[xdim*(yloc+1) + xloc-1] &= change_hide;
                    }
                    if (!((board[xdim*(yloc+1) + xloc] & mark))) {
                        board[xdim*(yloc+1) + xloc] &= change_hide;
                    }
                }
            }
            if (xloc != xdim-1) {
                if (!((board[xdim*yloc + xloc-1] & mark))) {
                    board[xdim*yloc + xloc+1] &= change_hide;
                }
                if (yloc != 0) {
                    if (!((board[xdim*(yloc-1) + xloc+1] & mark))) {
                        board[xdim*(yloc-1) + xloc+1] &= change_hide;
                    }
                    if (!((board[xdim*(yloc-1) + xloc] & mark))) {
                        board[xdim*(yloc-1) + xloc] &= change_hide;
                    }
                }
                if (yloc != ydim-1) {
                    if (!((board[xdim*(yloc+1) + xloc+1] & mark))) {
                        board[xdim*(yloc+1) + xloc+1] &= change_hide;
                    }
                    if (!((board[xdim*(yloc+1) + xloc] & mark))) {
                        board[xdim*(yloc+1) + xloc] &= change_hide;
                    }
                }
            }
        }
        if (!(board[xdim*yloc + xloc] & hide)) {
            return 2;
        }
        board[xdim*yloc + xloc] &= change_hide;
        return 0; 
    }
}

bool isGameWon(char *board, std::size_t xdim, std::size_t ydim);
bool isGameWon(char *board, std::size_t xdim, std::size_t ydim) {
    unsigned int hide{0b00100000};
    // something wrong here
    int num{0};
    for (int i{0}; (i <= (xdim*ydim - 1)); i++){
        if (((board[i] & (0b00001111)) == (0b00001001)) || (!(board[i] & hide))) {
            ++num;
            if (num == (xdim*ydim)) {
                return true;
            }
        } else {
            return false;
        }
    }
    return false;
}

void computeNeighbors(char *board, std::size_t xdim, std::size_t ydim);
void computeNeighbors(char *board, std::size_t xdim, std::size_t ydim) {
    for (unsigned int j{0}; (j <= ((xdim*ydim)-1)); ++j){
        if ((board[j] & (0b00001111)) != (0b00001001)) {
            if (j == 0) {
                if ((board[j+1] & (0b00001111)) == 9){
                    board[j] += 0b1;
                }
                if ((board[j+xdim] & (0b00001111)) == 9){
                    board[j] += 0b1;
                }
                if ((board[j+xdim+1] & (0b00001111)) == 9){
                    board[j] += 0b1;
                }
            } else if ((((j % xdim) == 0) && (j != 0)) && (j != (xdim*(ydim-1)))) {
                if ((board[j+1] & (0b00001111)) == 9){
                    board[j] += 0b1;
                }
                if ((board[j+xdim] & (0b00001111)) == 9){
                    board[j] += 0b1;
                }
                if ((board[j+xdim+1] & (0b00001111)) == 9){
                    board[j] += 0b1;
                }
                if ((board[j-xdim] & (0b00001111)) == 9){
                    board[j] += 0b1;
                }
                if ((board[j-xdim+1] & (0b00001111)) == 9){
                    board[j] += 0b1;
                }
            } else if (j == (xdim*(ydim-1))) {
                if ((board[j+1] & (0b00001111)) == 9){
                    board[j] += 0b1;
                }
                if ((board[j-xdim] & (0b00001111)) == 9){
                    board[j] += 0b1;
                }
                if ((board[j-xdim+1] & (0b00001111)) == 9){
                    board[j] += 0b1;
                }
            } else if ((((j % xdim) != 0) && (((j+1) % xdim) != 0)) && (j > (xdim*(ydim-1)))) {
                if ((board[j+1] & (0b00001111)) == 9){
                    board[j] += 0b1;
                }
                if ((board[j-1] & (0b00001111)) == 9){
                    board[j] += 0b1;
                }
                if ((board[j-xdim] & (0b00001111)) == 9){
                    board[j] += 0b1;
                }
                if ((board[j-xdim-1] & (0b00001111)) == 9){
                    board[j] += 0b1;
                }
                if ((board[j-xdim+1] & (0b00001111)) == 9){
                    board[j] += 0b1;
                }
            } else if (j == ((xdim*ydim)-1)) {
                if ((board[j-1] & (0b00001111)) == 9){
                    board[j] += 0b1;
                }
                if ((board[j-xdim] & (0b00001111)) == 9){
                    board[j] += 0b1;
                }
                if ((board[(j-1)-xdim] & (0b00001111)) == 9){
                    board[j] += 0b1;
                }
            } else if ((((j-(xdim-1)) % xdim) == 0) && (j > xdim) && (j < ((xdim*ydim)-1))) {
                if (board[j-1] & ((0b00001111)) == 9){
                    board[j] += 0b1;
                }
                if (board[j-xdim] & ((0b00001111)) == 9){
                    board[j] += 0b1;
                }
                if (board[j+xdim] & ((0b00001111)) == 9){
                    board[j] += 0b1;
                }
                if (board[(j-1)-xdim] & ((0b00001111)) == 9){
                    board[j] += 0b1;
                }
                if (board[(j-1)+xdim] & ((0b00001111)) == 9){
                    board[j] += 0b1;
                }
            } else if (j == (xdim-1)) {
                if ((board[j-1] & (0b00001111)) == 9){
                    board[j] += 0b1;
                }
                if ((board[j+xdim] & (0b00001111)) == 9){
                    board[j] += 0b1;
                }
                if ((board[j+xdim-1] & (0b00001111)) == 9){
                    board[j] += 0b1;
                }
            } else if (((j != 0) && (j != (xdim-1))) && (j < xdim)) {
                if ((board[j+1] & (0b00001111)) == 9){
                    board[j] += 0b1;
                }
                if ((board[j-1] & (0b00001111)) == 9){
                    board[j] += 0b1;
                }
                if ((board[j+xdim] & (0b00001111)) == 9){
                    board[j] += 0b1;
                }
                if ((board[j+xdim-1] & (0b00001111)) == 9){
                    board[j] += 0b1;
                }
                if ((board[j+xdim+1] & (0b00001111)) == 9){
                    board[j] += 0b1;
                }
            } else {
                if ((board[j+1] & (0b00001111)) == 9){
                    board[j] += 0b1;
                }
                if ((board[j-1] & (0b00001111)) == 9){
                    board[j] += 0b1;
                }
                if ((board[j+xdim] & (0b00001111)) == 9){
                    board[j] += 0b1;
                }
                if ((board[j+xdim-1] & (0b00001111)) == 9){
                    board[j] += 0b1;
                }
                if ((board[j+xdim+1] & (0b00001111)) == 9){
                    board[j] += 0b1;
                }
                if ((board[j-xdim] & (0b00001111)) == 9){
                    board[j] += 0b1;
                }
                if ((board[j-xdim-1] & (0b00001111)) == 9){
                    board[j] += 0b1;
                }
                if ((board[j-xdim+1] & (0b00001111)) == 9){
                    board[j] += 0b1;
                }
            }
        } else {
            continue;
        }
    }
    return;
}
