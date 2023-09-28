#include <stdio.h>


void ler_troc(int tam, int vet[tam]){
  
  int vetor2[5];
  int vetor_f[10];
  
  for(int i = 0; i < tam; i++){
    scanf("%d", &vet[i]);
  }
  for(int i = 0; i < tam; i++){
    scanf("%d", &vetor2[i]);
  }

  for(int i = 0; i < 5; i++){
    vetor_f[i] = vet[i];
  }

  for(int i = 5; i < 10; i++){
    for(int j = 0; j < 5; j++){
    vetor_f[i] = vetor2[j];
    }
  }
  
  printf("\n");

  for(int i = 0; i < 10; i++){
    printf("{%d}", vetor_f[i]);
  }
}


int main(){
  int vet[10];

  printf("Digte uma tecla com um numero 10X: \n");
  ler_troc(5 , vet);

  return 0;
}
