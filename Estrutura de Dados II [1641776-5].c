# include <stdio.h>
# include <locale.h>
# include <stdlib.h>
# include <string.h>

//assinatura das funções
struct NO* addno(char* dado[]);

void soma();
void subtracao();
void multiplicacao();

int charToInt(char dado[1]);

//Estrutua do Nó
struct NO {
    char Dado[1];
    struct NO *Direira;
    struct NO *Esquerda;
};

//Váriaveis gloabais utilizadas para realizar os cálculos
struct NO* NoIni = NULL;
int LadoEsquerdo, LadoDireito, Total;

//cria e devole um novo nó
struct NO* addno(char* dado[]){
    struct NO* newNo = (struct NO *) malloc(sizeof( struct NO));
    strcpy(newNo->Dado, &dado);
    newNo->Esquerda = NULL;
    newNo->Direira = NULL;

    return newNo;
}

void inicializarVariaveis(){
    LadoEsquerdo = NULL;
    LadoDireito  = NULL;
    Total = NULL;

    NoIni = addno('+');
    NoIni->Esquerda = addno('*');
    NoIni->Direira  = addno('5');

    NoIni->Esquerda->Esquerda = addno('-');
    NoIni->Esquerda->Esquerda->Esquerda = addno('6');
    NoIni->Esquerda->Esquerda->Direira  = addno('3');

    NoIni->Esquerda->Direira = addno('+');
    NoIni->Esquerda->Direira->Esquerda = addno('4');
    NoIni->Esquerda->Direira->Direira  = addno('1');
}

void calcular(struct NO* ptr){
    if((ptr->Esquerda != NULL) || (ptr->Direira != NULL)) {
        calcular(ptr->Esquerda);
        calcular(ptr->Direira);

        if (*ptr->Dado == '+'){
            soma();
        }
        else if(*ptr->Dado == '-'){
            subtracao();
        }
        else if(*ptr->Dado == '*'){
            multiplicacao();
        }
    }
    else{
        //Se ambos os lados são nulos é porque chegou ao fim do nó, então pega o valor e
        //coloca nas variaveis do cálculo

        if (LadoEsquerdo == NULL) {
            LadoEsquerdo = charToInt(ptr->Dado);
        } else {
            LadoDireito = charToInt(ptr->Dado);
        }
    }
}

int charToInt(char dado[1]) {
    switch (*dado){
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
    }

}

void soma(){
    if(Total == NULL){
        Total = LadoEsquerdo + LadoDireito;
        LadoEsquerdo = NULL;
        LadoDireito = NULL;
    }
    else{
        if(LadoDireito != NULL && LadoEsquerdo != NULL) {
            LadoDireito = LadoDireito + LadoEsquerdo;
            LadoEsquerdo = Total;
            Total = NULL;
        }
        else{
            if(LadoEsquerdo == NULL) LadoEsquerdo = Total;
            else LadoDireito = Total;
            Total = NULL;
            soma();
        }
    }
}

void subtracao(){
    if(Total == NULL){
        Total = LadoEsquerdo - LadoDireito;
        LadoEsquerdo = NULL;
        LadoDireito = NULL;
    }
    else{
        if(LadoDireito != NULL && LadoEsquerdo != NULL) {
            LadoDireito = LadoDireito - LadoEsquerdo;
            LadoEsquerdo = Total;
            Total = NULL;
        }
        else{
            if(LadoEsquerdo == NULL) LadoEsquerdo = Total;
            else LadoDireito = Total;
            Total = NULL;
            soma();
        }
    }
}

void multiplicacao(){
    if(Total == NULL){
        Total = LadoEsquerdo * LadoDireito;
        LadoEsquerdo = NULL;
        LadoDireito = NULL;
    }
    else{
        if(LadoDireito != NULL && LadoEsquerdo != NULL) {
            LadoDireito = LadoDireito * LadoEsquerdo;
            LadoEsquerdo = Total;
            Total = NULL;
        }
        else{
            if(LadoEsquerdo == NULL) LadoEsquerdo = Total;
            else LadoDireito = Total;
            Total = NULL;
            soma();
        }
    }
}


int main(){
    setlocale(LC_ALL, "Portuguese");
    printf("##################################\n");
    printf("#    Calculos em arvore binaria  #\n");
    printf("#    Aluno Valdeir de Melo       #\n");
    printf("#    R.A. 1641776-5              #\n");
    printf("#    Estruta de Dados II         #\n");
    printf("##################################\n");

    //Resposável por criar a árvore binária
    inicializarVariaveis();
    //Responsável pelo Cálculo
    calcular(NoIni);

    printf("O Total é : %d", Total);
    return 0;
}