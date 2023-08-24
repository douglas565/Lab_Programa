#include <stdio.h>

int main() {
    int var;
    int d1;
    int d2;
    int d3;

    d1 = getchar() - '0';  // Convertendo o caractere em um dígito numérico
    d2 = getchar() - '0';
    d3 = getchar() - '0';

    var = d1 * 100 + d2 * 10 + d3;  // Reconstruindo o número a partir dos dígitos

    if (var < 0) {
        putchar('-');
        var = -var;
    }

    d1 = var / 100;
    d2 = (var % 100) / 10;
    d3 = (var % 10);

    putchar(d1 + '0');
    putchar(d2 + '0');
    putchar(d3 + '0');

    return 0;
}
