// Douglas Ramos Charqueiro
// 2023-10-30

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#define CLEAR_SCREEN system("cls")
#else
#define CLEAR_SCREEN system("clear")
#endif

#define DECK_SIZE 54
#define HAND_SIZE 7

typedef struct {
    char value[3];
    char color[7];
    char suit[9]; // Adicionado para armazenar o naipe
    int score;
} Card;

typedef struct {
    Card cards[HAND_SIZE];
    int cardCount;
    int score;
} Hand;

Card deck[DECK_SIZE];
Hand players[2];
Card table[DECK_SIZE];
int tableCardCount = 0;
int deckIndex = 0;

int combatWins = 0;

void initializeDeck()
{
    Card purpleCards[] = {{"r1", "purple"}, {"r1", "purple"}, {"r2", "purple"}, {"r2", "purple"}, {"r3", "purple"}, {"r3", "purple"}, {"r4", "purple"}, {"r5", "purple"}, {"r6", "purple"}, {"r7", "purple"}, {"J", "purple"}, {"Q", "purple"}, {"K", "purple"}, {"A", "purple"}};
    Card blackCards[] = {{"1", "black"}, {"1", "black"}, {"3", "black"}, {"3", "black"}, {"4", "black"}, {"4", "black"}, {"5", "black"}, {"5", "black"}, {"7", "black"}, {"C", "black"}, {"J", "black"}, {"Q", "black"}, {"K", "black"}, {"A", "black"}};
    Card redCards[] = {{"1", "red"}, {"1", "red"}, {"2", "red"}, {"2", "red"}, {"3", "red"}, {"4", "red"}, {"5", "red"}, {"J", "red"}, {"Q", "red"}, {"K", "red"}, {"A", "red"}};
    Card yellowCards[] = {{"2", "yellow"}, {"2", "yellow"}, {"2", "yellow"}, {"4", "yellow"}, {"4", "yellow"}, {"5", "yellow"}, {"5", "yellow"}, {"5", "yellow"}, {"J", "yellow"}, {"Q", "yellow"}, {"K", "yellow"}, {"A", "yellow"}};
    Card jokers[] = {{"J", "none"}, {"J", "none"}, {"J", "none"}};

    int index = 0;
    for (int i = 0; i < 14; i++)
    {
        deck[index++] = purpleCards[i];
        deck[index++] = blackCards[i];
        if (i < 11)
            deck[index++] = redCards[i];
        if (i < 12)
            deck[index++] = yellowCards[i];
    }
    for (int i = 0; i < 3; i++)
    {
        deck[index++] = jokers[i];
    }
}

void printCard(Card card) {
    printf("%s of %s %s", card.value, card.color, card.suit);
}

void shuffleDeck() {
    srand(time(NULL));
    for (int i = DECK_SIZE - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Card temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

void dealCards() {
    for (int i = 0; i < 2; i++) {
        players[i].cardCount = 0;
        for (int j = 0; j < HAND_SIZE; j++) {
            if (deckIndex < DECK_SIZE) {
                players[i].cards[j] = deck[deckIndex++];
                players[i].cardCount++;
            }
        }
    }
}

void printHand(Hand *hand) {
    printf("Suas cartas:\n");
    for (int i = 0; i < hand->cardCount; i++) {
        printf("%d: ", i + 1);
        printCard(hand->cards[i]);
        printf("\n");
    }
    printf("\n");
}

int countRedCardsOnTable() {
    int count = 0;
    for (int i = 0; i < tableCardCount; i++) {
        if (strcmp(table[i].color, "red") == 0) {
            count++;
        }
    }
    return count;
}

int getCardValue(Card card) {
    if (strcmp(card.value, "J") == 0) return 11;
    if (strcmp(card.value, "Q") == 0) return 12;
    if (strcmp(card.value, "K") == 0) return 13;
    if (strcmp(card.value, "A") == 0) return 14;
    if (strcmp(card.value, "C") == 0) return 10;
    return atoi(card.value);
}

void startCombat(int attackingPlayer, int defendingPlayer) {
    int totalAttackValue = 0;
    int cardIndex = 0;
    CLEAR_SCREEN;
    printf("Player %d, escolha cartas pretas para jogar no combate (0 para terminar): \n", attackingPlayer + 1);
    while(1) {
        printHand(&players[attackingPlayer]);
        printf("Escolha uma carta (1-%d) ou 0 para terminar: ", players[attackingPlayer].cardCount);
        scanf("%d", &cardIndex);
        if (cardIndex == 0) break;
        if (cardIndex > 0 && cardIndex <= players[attackingPlayer].cardCount) {
            Card chosenCard = players[attackingPlayer].cards[cardIndex - 1];
            if (strcmp(chosenCard.color, "black") == 0 || chosenCard.value[0] == 'C') {
                totalAttackValue += getCardValue(chosenCard);
                for (int i = cardIndex - 1; i < players[attackingPlayer].cardCount - 1; i++) {
                    players[attackingPlayer].cards[i] = players[attackingPlayer].cards[i + 1];
                }
                players[attackingPlayer].cardCount--;
            } else {
                printf("Você só pode escolher cartas pretas ou C para jogar no combate!\n");
            }
        } else {
            printf("Número inválido! Por favor, escolha um número de 1 a %d.\n", players[attackingPlayer].cardCount);
        }
    }

    int totalDefenseValue = 0;
    CLEAR_SCREEN;
    printf("Player %d, escolha cartas pretas para defender o combate (0 para terminar): \n", defendingPlayer + 1);
    while(1) {
        printHand(&players[defendingPlayer]);
        printf("Escolha uma carta (1-%d) ou 0 para terminar: ", players[defendingPlayer].cardCount);
        scanf("%d", &cardIndex);
        if (cardIndex == 0) break;
        if (cardIndex > 0 && cardIndex <= players[defendingPlayer].cardCount) {
            Card chosenCard = players[defendingPlayer].cards[cardIndex - 1];
            if (strcmp(chosenCard.color, "black") == 0 || chosenCard.value[0] == 'C') {
                totalDefenseValue += getCardValue(chosenCard);
                for (int i = cardIndex - 1; i < players[defendingPlayer].cardCount - 1; i++) {
                    players[defendingPlayer].cards[i] = players[defendingPlayer].cards[i + 1];
                }
                players[defendingPlayer].cardCount--;
            } else {
                printf("Você só pode escolher cartas pretas ou C para defender o combate!\n");
            }
        } else {
            printf("Número inválido! Por favor, escolha um número de 1 a %d.\n", players[defendingPlayer].cardCount);
        }
    }

    // Lógica para determinar o vencedor do combate
    if (totalAttackValue == totalDefenseValue && (totalAttackValue == 10 || totalDefenseValue == 10)) {
        printf("O combate empatou!\n");
    } else if (totalAttackValue == 14 && totalDefenseValue == 10) {
        printf("Player %d venceu o combate! (Rei vence Castelo)\n", attackingPlayer + 1);
        players[attackingPlayer].score += 3;
        combatWins++;
    } else if (totalDefenseValue > totalAttackValue) {
        printf("Player %d venceu o combate!\n", defendingPlayer + 1);
        players[defendingPlayer].score += 3;
    } else {
        printf("Player %d venceu o combate!\n", attackingPlayer + 1);
        players[attackingPlayer].score += 3;
        combatWins++;
    }

    // Distribuir cartas vermelhas na mesa entre os jogadores
    int redCards = countRedCardsOnTable();
    for (int i = 0; i < redCards; i++) {
        if (deckIndex < DECK_SIZE) {
            players[attackingPlayer].cards[players[attackingPlayer].cardCount++] = deck[deckIndex++];
        }
        if (deckIndex < DECK_SIZE) {
            players[defendingPlayer].cards[players[defendingPlayer].cardCount++] = deck[deckIndex++];
        }
    }
}

void printTable() {
    if (tableCardCount == 0) {
        printf("Não há cartas na mesa.\n");
    } else {
        printf("Cartas na mesa:\n");
        for (int i = 0; i < tableCardCount; i++) {
            printf("%d: ", i + 1);
            printCard(table[i]);
            printf("\n");
        }
    }
    printf("\n");
}

void playRound(int currentPlayer) {
    CLEAR_SCREEN;
    printf("Vez do Player %d:\n", currentPlayer + 1);
    printHand(&players[currentPlayer]);
    printf("Escolha uma opção:\n");
    printf("1: Jogar uma carta\n");
    printf("2: Mostrar as cartas na mesa\n");
    printf("3: Sair do jogo\n");
    int option;
    scanf("%d", &option);

    switch (option) {
        case 1:
            printf("Escolha uma carta para jogar (1-%d): ", players[currentPlayer].cardCount);
            int cardIndex;
            scanf("%d", &cardIndex);
            if (cardIndex >= 1 && cardIndex <= players[currentPlayer].cardCount) {
                Card playedCard = players[currentPlayer].cards[cardIndex - 1];

                table[tableCardCount++] = playedCard;

                for (int i = cardIndex - 1; i < players[currentPlayer].cardCount - 1; i++) {
                     players[currentPlayer].cards[i] = players[currentPlayer].cards[i + 1];
                }
                players[currentPlayer].cardCount--;

                if (strcmp(playedCard.color, "black") == 0 || playedCard.value[0] == 'C') {
                    int defendingPlayer = 1 - currentPlayer;
                    startCombat(currentPlayer, defendingPlayer);
                }
            } else {
                printf("Opção inválida! Tente novamente.\n");
                playRound(currentPlayer);
            }
            break;
        case 2:
            CLEAR_SCREEN;
            printTable();
            printf("Pressione ENTER para continuar...");
            getchar();  // Consome o '\n' deixado pelo scanf
            getchar();  // Aguarda o usuário pressionar ENTER
            playRound(currentPlayer);
            break;
        case 3:
            printf("Saindo do jogo...\n");
            exit(0);
        default:
            printf("Opção inválida! Tente novamente.\n");
            playRound(currentPlayer);
            break;
    }
}


int main() {
    initializeDeck();
    shuffleDeck();
    dealCards();

    int rounds = 0;
    int currentPlayer = 0;

    while (rounds < DECK_SIZE) {
        printf("Round %d\n", rounds + 1);
        playRound(currentPlayer);
        currentPlayer = 1 - currentPlayer;
        rounds++;
    }

    players[0].score += combatWins * 2;
    players[1].score += (rounds - combatWins) * 2;

    printf("Acabou o baralho de compra!:\n");
    printf("Final scores:\n");
    printf("Player 1: %d\n", players[0].score);
    printf("Player 2: %d\n", players[1].score);

    if (players[0].score > players[1].score) {
        printf("Player 1 venceu!\n");
    } else if (players[0].score < players[1].score) {
        printf("Player 2 venceu!\n");
    } else {
        printf("Foi empate :(\n");
    }
    getchar();
    getchar();
    return 0;
}