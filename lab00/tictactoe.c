#include <stdlib.h>  /* exit() y EXIT_FAILURE */
#include <stdio.h>   /* printf(), scanf()     */
#include <stdbool.h> /* Tipo bool             */

#include <assert.h> /* assert() */

#define BOARD_SIZE 3
#define CELL_MAX (BOARD_SIZE * BOARD_SIZE - 1)

void print_board(char board[BOARD_SIZE][BOARD_SIZE])
{
    int cell = 0;
    printf("\t .................................................\n");
    for (int row = 0; row < BOARD_SIZE; ++row)
    {
        for (int column = 0; column < BOARD_SIZE; ++column)
        {
            printf("\t | %d: %c ", cell, board[row][column]);
            ++cell;
        }
        printf("\t | \n");
        printf("\t .................................................\n");
    }
}

char get_winner(char board[BOARD_SIZE][BOARD_SIZE])
{
    char winner = '-';
    int val;
    int i = 0;
    int j = 1;

    // Determina si hay un ganador en las filas
    while (i < BOARD_SIZE)
    {
        if (board[i][0] != '-')
        {
            val = board[i][0];
            winner = val;
            while (j < BOARD_SIZE)
            {
                if (val != board[i][j])
                {
                    winner = '-';
                    break;
                }
                ++j;
            }
            if (winner != '-')
            {
                return winner;
            }
        }
        ++i;
    }
    i = 1;
    j = 0;

    // Determina si hay un ganador en las columnas
    while (j < BOARD_SIZE)
    {
        if (board[0][j] != '-')
        {
            val = board[0][j];
            winner = val;
            while (i < BOARD_SIZE)
            {
                if (val != board[i][j])
                {
                    winner = '-';
                    break;
                }
                ++i;
            }
            if (winner != '-')
            {
                return winner;
            }
        }
        ++j;
    }

    // Determina si hay un ganador en la diagonal
    unsigned int d = 1u;
    if (board[0][0] != '-')
    {
        val = board[0][0];
        winner = val;
        while (d < BOARD_SIZE)
        {
            if (val != board[d][d])
            {
                winner = '-';
                break;
            }
            ++d;    
        }
        if(winner != '-') {
            return winner;
        }
    }

    // Determina si hay un ganador en la anti-diagonal
    int h = BOARD_SIZE - 1;
    j = 0;
    if (board[BOARD_SIZE - 1][0] != '-')
    {
        val = board[BOARD_SIZE - 1][0];
        winner = val;
        while (h >= 0)
        {
            if (val != board[h][j])
            {
                winner = '-';
                break;
            } 
            --h;
            ++j;
        }
        if(winner != '-') {
            return winner;
        }
    }

    return '-';
}

bool has_free_cell(char board[BOARD_SIZE][BOARD_SIZE])
{
    unsigned int i = 0u;
    unsigned int j = 0u;
    while (i < BOARD_SIZE)
    {
        j = 0u;
        while (j < BOARD_SIZE)
        {
            if (board[i][j] == '-')
            {
                return true;
            }
            
            ++j;
        }
        ++i;
    }
    return false;
}

int main(void)
{
    printf("TicTacToe [InCoMpLeTo :'(]\n");

    char board[BOARD_SIZE][BOARD_SIZE] = {
        {'-', '-', '-'},
        {'-', '-', '-'},
        {'-', '-', '-'}};

    char turn = 'X';
    char winner = '-';
    int cell = 0;
    while (winner == '-' && has_free_cell(board))
    {
        print_board(board);
        printf("\nTurno %c - Elija posición (número del 0 al 8): ",
               turn);
        int scanf_result = scanf("%d", &cell);
        if (scanf_result <= 0)
        {
            printf("Error al leer un número desde teclado\n");
            exit(EXIT_FAILURE);
        }
        if (cell >= 0 && cell <= CELL_MAX)
        {
            int row = cell / BOARD_SIZE;
            int colum = cell % BOARD_SIZE;
            if (board[row][colum] == '-')
            {
                board[row][colum] = turn;
                turn = turn == 'X' ? 'O' : 'X';
                winner = get_winner(board);
            }
            else
            {
                printf("\nCelda ocupada!\n");
            }
        }
        else
        {
            printf("\nCelda inválida!\n");
        }
    }
    print_board(board);
    if (winner == '-')
    {
        printf("Empate!\n");
    }
    else
    {
        printf("Ganó %c\n", winner);
    }
    return 0;
}
