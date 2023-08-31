// l123b aula 6 exercicio
//imprimir em hexadecimal, com 2 dígitos. Só vai poder imprimir valores menores que 256. Os dígitos de 10 a 15 são representados pelos símbolos 'A' a 'F'. Atenção que na tabela ASCII o valor para o símbolo 'A' não é um a mais que o valor para o símbolo '9'. Descubra porque 186 é o número do gaúcho nerd.
// Douglas Ramos Charqueiro
// 2023/08/28

#include <stdio.h>

int main()
{
    int num = 186;

    if (num < 0) {
        putchar('-');
        num = -num;
    }

    int div = num / 16;
    int sobra = num % 16;

    if (div >= 10) {
        putchar(div - 10 + 'A');
    } else {
        putchar(div + '0');
    }

    if (sobra >= 10) {
        putchar(sobra - 10 + 'A');
    } else {
        putchar(sobra + '0');
    }

    printf("\n");

    return 0;
}
