/**************************************************
CONSULTA CPF E ARMAZENA (Aula de C++, UDESC)

Autor: Artur Machado.

Propósito: Armazena um vetor de 5 pessoas, cada pessoa composta por NOME, CPF válido e IDADE.

Uso: Preencher conforme solicitado na tela.
     Exemplo de CPF para teste ### 529.982.247-25 ###
**************************************************/

#include <stdio.h>
#include <string.h>

void verificador (unsigned long *);      //função verificadora de CPF
const int S = 5;        //tamanho da agenda

struct pessoa {         //struct com informações de cada pessoa
  char nome[100];       //nome da pessoa
  unsigned long cpf;    //CPF da pessoa
  unsigned short idade; //idade da pessoa
} agenda[S];            //vetor AGENDA, com espaço para armazenar 5 pessoas

char line[100];         //vetor de captura de texto
short int i;            //índice loop

int main () {
  printf ("Informe os dados a seguir\n");

  for (i = 0; i < S; ++i){              //loop do tamanho da agenda
    printf ("NOME: ");
    fgets (line, sizeof(line), stdin);  //recebe o nome em LINE
    line[strlen(line)-1] = '\0';        //troca o '\n' por '\0'
    strcpy (agenda[i].nome, line);      //copia LINE para NOME
    strcpy (line, "\0");                //esvazia LINE

    while (agenda[i].cpf == 0){                 //loop enquanto o CPF não for válido
        printf ("CPF: ");
        fgets (line, sizeof(line), stdin);      //recebe o cpf em LINE
        sscanf (line, "%lu", &agenda[i].cpf);   //input de CPF através de LINE
        strcpy (line, "\0");                    //esvazia LINE
        verificador(&agenda[i].cpf);            //chama função verificadora de CPF, se inválido, repete o loop
    }

    printf ("Idade: ");
    fgets (line, sizeof(line), stdin);       //recebe a idade em LINE
    sscanf (line, "%hu", &agenda[i].idade);  //input de IDADE através de LINE
    strcpy (line, "\0");                     //esvazia LINE

    printf ("\n");                      //"\n", para clareza
  }

  return (0);
}

/* função verificadora de CPF */
void verificador (unsigned long *cpf_ptr){
    /*
    Explicação do "isolamento":
    supondo que quero o '3' de 12345

    A) maior elemento... 12345 % 1000 = 345
    B) menor elemento... 12345 %  100 =  45
    C) diferença...        345 -   45 = 300
    D) isolamento final... 300 /  100 =   3    -> fim */

    unsigned long x;                    //elemento maior
    unsigned long y;                    //elemento menor (para isolar o dígito em questão)
    unsigned long multiplicador = 100;  //usado para isolar o dígito do CPF, inicia em 100
    short int i;                        //índice loop
    int soma;                           //somatório para validação do CPF
    int verificador_1;                  //penúltimo dígito de acordo com a verificação
    int verificador_2;                  //último dígito de acordo com a verificação
    int penultimo = ((*cpf_ptr % 100) - (*cpf_ptr % 10))/10;    //penúltimo dígito do CPF já isolado
    int ultimo = *cpf_ptr % 10;                                 //último dígito do CPF já isolado

    /* verificador_1 - penúltimo dígito */
    for (i = 2; i < 11; ++i){                   //loop dos 9 primeiros dígitos
        x = *cpf_ptr % (multiplicador*10);      //cpf % 1000
        y = *cpf_ptr % multiplicador;           //cpf % 100
        soma += ((x - y)/multiplicador) * i;    //(cpf%1000 - cpf%100)/ 100 * 2 -> "isolamento", descrito acima
        multiplicador *=10;                     //ao final, cresce para pegar o dígito à esquerda
    }
    verificador_1 = (soma * 10) % 11;   //RESTO da divisão por 11
    if (verificador_1 == 10)            //se 10, considerar '0'
        verificador_1 = 0;

    /* verificador_2 - último dígito */
    multiplicador = 10;             //reinicia para reuso
    soma = 0;                       //reinicia para reuso
    for (i = 2; i <= 11; ++i){                  //loop dos 10 primeiros dígitos
        x = *cpf_ptr % (multiplicador*10);      //mesmo esquema do "isolamento", descrito acima
        y = *cpf_ptr % multiplicador;
        soma += ((x - y)/multiplicador) * i;
        multiplicador *=10;
    }
    verificador_2 = (soma * 10) % 11;   //RESTO da divisão por 11
    if (verificador_2 == 10)            //se 10, considerar '0'
        verificador_2 = 0;

    /* comparação dos verificadores com os últimos dígitos do CPF */
    if ((verificador_1 != penultimo) || (verificador_2 != ultimo)){ //se diferentes, CPF inválido
        *cpf_ptr = 0;
        printf ("!!CPF inválido!! Digite novamente...\n");
    }
    return;
}
