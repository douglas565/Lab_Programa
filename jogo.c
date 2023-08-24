#include <stdio.h>

// Função para verificar se algum jogador ganhou
char checkWinner(char board[3][3]) {
    // Verificação das linhas, colunas e diagonais
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return board[i][0];
        }
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            return board[0][i];
        }
    }
    
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return board[0][0];
    }
    
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return board[0][2];
    }
    
    // Caso não haja vencedor
    return ' ';
}

int main() {
    char board[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };
    
    int moves = 0;
    char currentPlayer = 'X';
    
    while (moves < 9) {
        int row, col;
        
        // Exibir o tabuleiro
        printf("  1 2 3\n");
        for (int i = 0; i < 3; i++) {
            printf("%d", i + 1);
            for (int j = 0; j < 3; j++) {
                printf(" %c", board[i][j]);
            }
            printf("\n");
        }
        
        // Fazer uma jogada
        printf("Jogador %c, digite a linha e a coluna da sua jogada: ", currentPlayer);
        scanf("%d %d", &row, &col);
        
        if (row < 1 || row > 3 || col < 1 || col > 3 || board[row - 1][col - 1] != ' ') {
            printf("Jogada inválida! Tente novamente.\n");
            continue;
        }
        
        board[row - 1][col - 1] = currentPlayer;
        moves++;
        
        // Verificar se há um vencedor
        char winner = checkWinner(board);
        if (winner != ' ') {
            printf("Parabéns! Jogador %c venceu!\n", winner);
            break;
        }
        
        // Trocar de jogador
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
    
    if (moves == 9) {
        printf("Empate! O jogo terminou sem vencedor.\n");
    }
    
    return 0;
}
