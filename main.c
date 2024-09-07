#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TECLA_ESC 27       // o código da tecla ESC é 27
#define OCULTAR 0
#define REVELAR 1
#define PERDEU 0
#define GANHOU 2
#define DIMENSAO 5
#define INDICE_FINAL 24    // índice final do vetor
#define TOTAL_ELEMENTOS 25 // total de elementos

/* Tabuleiro é de 5 x 5, então temos 25 células
   30% das células devem conter minas, então 30% de 25 é 7,5 arredondando temos 8 minas. */
#define TOTAL_MINAS 8

/* Vetor com 25 elementos representando tabuleiro, índice de 0 a 24
   Guarda se a posição possui ou não minas.
   Onde:
   0 - não existe mina
   1 - sim, existe uma mina nesta posição
*/
int tabuleiroMina[TOTAL_ELEMENTOS];

/* Vetor com 25 elementos representando tabuleiro, índice de 0 a 24
   Guarda se o usuário já jogou em determinada posição.
   Onde:
   0 - não jogou
   1 - sim, já jogou nesta posição do tabuleiro
*/
int tabuleiroJogada[TOTAL_ELEMENTOS];

/* PROTÓTIPO DAS FUNÇÕES */
void limparTabuleiro();
void espalharMinas();
void desenharTabuleiro();
int contarMinas(int posicao);
int converte(char *pos);
int jogar(char *pos);
int ganhou();
int pecaDireita(int posicao);
int bordaDireita(int posicao);
int pecaEsquerda(int posicao);
int bordaEsquerda(int posicao);
int pecaSuperior(int posicao);
int bordaSuperior(int posicao);
int pecaInferior(int posicao);
int bordaInferior(int posicao);
int pecaSuperiorEsquerda(int posicao);
int pecaSuperiorDireita(int posicao);
int pecaInferiorEsquerda(int posicao);
int pecaInferiorDireita(int posicao);
int inteiro(float numerador, float denominador);


int main(int argc, char *argv[])
{

    /* Variável para pegar a tecla digitada */
    int tecla;

    /* Variável para pegar a posição que o usuário quer jogar*/
    char posicao[4];

    /* Retorno do processamento da jogada */
    int resposta;

    //A função srand inicializa a função que irá retornar um número aleatório.
    srand ( time(NULL) );

    do{
        /* Limpa a tela */
        system("cls");

        printf("****************************************************\n");
        printf("****************************************************\n");
        printf("***          ISLWYNDEN                           ***\n");
        printf("*** Jorge Bezerra dos Santos                     ***\n");
        printf("***                                              ***\n");
        printf("****************************************************\n");
        printf("****************************************************\n");
        printf("\n \n \n \n");
        printf("Pressione qualquer tecla para iniciar o jogo\n");
        printf("Pressione ESC para terminar\n");

        /* obtém código da tecla digitada */
        tecla = getch();

        /* Se apertou ESC */
        if (tecla == TECLA_ESC){
            /* Sai do programa */
            exit(0);
        }

        limparTabuleiro();

        espalharMinas();

        do{
            /* Limpa a tela */
            system("cls");

            //desenha o tabuleiro sem revelar as minas
            desenharTabuleiro(OCULTAR);

            //TESTE - REMOVA O COMENTÁRIO ABAIXO E VEJA A RESPOSTA DO JOGO, ÚTIL PARA TESTAR QUANDO GANHA
            //desenharTabuleiro(REVELAR);

            printf("\nDigite 'sair' para desistir e encerrar o jogo.");
            printf("\nOu escolha a linha e a coluna: ");
            scanf("%s", posicao);

            /* Se digitou "sair" */
            if (strcmp(posicao, "sair") == 0){
                /* Sai do programa */
                exit(0);
            }

            resposta = jogar(posicao);

            switch (resposta){

                case PERDEU:
                    //desenha o tabuleiro revelando as minas
                    desenharTabuleiro(1);

                    printf("\nGAME OVER\n");
                    system("PAUSE");

                    break;

                case GANHOU:
                    //desenha o tabuleiro revelando as minas
                    desenharTabuleiro(1);

                    printf("\nPARABENS, VOCE COMPLETOU O JOGO\n");
                    system("PAUSE");

                    break;
            }

        /* Enquanto não perder o jogo ou ganhar, continua */
        } while ( (resposta != PERDEU) && (resposta != GANHOU) );

    /* Só sai quando o comando exit(0) for executado */
    } while (1);

    return 0;
}


void limparTabuleiro(){
    int a;
    for (a = 0; a <= INDICE_FINAL; a++){
        tabuleiroMina[a] = 0;
        tabuleiroJogada[a] = 0;
    }
}


void espalharMinas(){
    int pos;
    int totalMinas = 0;

    do {
        //número aleatório de 0 a 4
        pos = rand() % TOTAL_ELEMENTOS;

        //Se não existe mina ainda
        if (tabuleiroMina[pos] == 0){

            //marca que agora tem uma mina nesta posição
            tabuleiroMina[pos] = 1;

            //mais uma mina foi adicionada
            totalMinas++;
        }

    //enquanto não tiver 8 minas continua
    } while(totalMinas != TOTAL_MINAS);
}

/* O jogo normalmente só deve mostrar as posições já jogadas
   Onde
     0 - não revelar o jogo
     1 - revelar o jogo
*/
void desenharTabuleiro(int revelar){
    int a;
    int contador = 0;
    int minasRedor;

    char letras[] = "ABCDE";
    int letra = 0;

    /* SÓ DEVE MOSTRAR POSIÇÕES JÁ JOGADAS */

    printf("\n  01234 \n");

    for (a = 0; a <= INDICE_FINAL; a++){

        if (contador == 0){
            printf("%c ", letras[letra]);

            //próxima letra da linha
            letra++;
        }

        contador++;

        //Se não é para revelar o jogo
        if (revelar == 0){

            //Se posição não foi escolhida
            if (tabuleiroJogada[a] == 0){

                //oculta
                printf("?");
            }else{
                //verifica e mostra quantas minas tem ao redor da posição
                minasRedor = contarMinas(a);
                printf("%d", minasRedor);
            }

        }else{ // Se é para revelar o jogo

            //Se tem mina
            if (tabuleiroMina[a] == 1){
                printf("*");
            }else{
                //mostra quantas minas tem ao redor da posição
                minasRedor = contarMinas(a);
                printf("%d", minasRedor);
            }

        } // end if

        //quebra linha a cada cinco
        if (contador == DIMENSAO){
             printf("\n");

             //reinicia contador
             contador = 0;
        }

    } //end for

    printf("\n");
}


/* conta quantas minas tem ao redor de uma posição */
int contarMinas(int posicao){

    int contador = 0;
    int peca = 0;

    //Se a peça não estiver na borda direita
    if ( !bordaDireita(posicao) ){

        //obtém a posicao da peça a sua direita
        peca = pecaDireita(posicao);

        //se for uma mina
        if ( tabuleiroMina[peca] == 1){
            contador++;
        }
    }

    //Se a peça não estiver na borda esquerda
    if ( !bordaEsquerda(posicao) ){

        //obtém a posicao da peça a sua esquerda
        peca = pecaEsquerda(posicao);

        //se for uma mina
        if ( tabuleiroMina[peca] == 1){
            contador++;
        }
    }

    //Se a peça não estiver na borda superior
    if ( !bordaSuperior(posicao) ){

        //obtém a posicao da peça superior
        peca = pecaSuperior(posicao);

        //se for uma mina
        if ( tabuleiroMina[peca] == 1){
            contador++;
        }
    }

    //Se a peça não estiver na borda inferior
    if ( !bordaInferior(posicao) ){

        //obtém a posicao da peça inferior
        peca = pecaInferior(posicao);

        //se for uma mina
        if ( tabuleiroMina[peca] == 1){
            contador++;
        }
    }

    /* DIAGONAIS */

    //Se a peça não estiver na borda superior ou na borda esquerda
    if ( !bordaSuperior(posicao) && !bordaEsquerda(posicao) ){

        //obtém a posicao da peça superior esquerda
        peca = pecaSuperiorEsquerda(posicao);

        //se for uma mina
        if ( tabuleiroMina[peca] == 1){
            contador++;
        }
    }

    //Se a peça não estiver na borda superior ou na borda direita
    if ( !bordaSuperior(posicao) && !bordaDireita(posicao) ){

        //obtém a posicao da peça superior direita
        peca = pecaSuperiorDireita(posicao);

        //se for uma mina
        if ( tabuleiroMina[peca] == 1){
            contador++;
        }
    }

    //Se a peça não estiver na borda inferior esquerda
    if ( !bordaInferior(posicao) && !bordaEsquerda(posicao) ){

        //obtém a posicao da peça inferior esquerda
        peca = pecaInferiorEsquerda(posicao);

        //se for uma mina
        if ( tabuleiroMina[peca] == 1){
            contador++;
        }
    }

    //Se a peça não estiver na borda inferior direita
    if ( !bordaInferior(posicao) && !bordaDireita(posicao) ){

        //obtém a posicao da peça inferior direita
        peca = pecaInferiorDireita(posicao);

        //se for uma mina
        if ( tabuleiroMina[peca] == 1){
            contador++;
        }
    }

    return contador;
}


/* Converte caractere (char) para posição válida na matriz, ou seja, um número de 0 a 4
Onde:
  A = 0
  B = 1
  C = 2
  D = 3
  E = 4
*/
int converte(char *pos){

    int pos1;
    int pos2;

    //converte para maiúsculo
    pos[0] = toupper(pos[0]);

    //converte letra para número
    if (pos[0] == 'A'){
        pos1 = 0;

    }else if (pos[0] == 'B'){
        pos1 = 1;

    }else if (pos[0] == 'C'){
        pos1 = 2;

    }else if (pos[0] == 'D'){
        pos1 = 3;

    }else if (pos[0] == 'E'){
        pos1 = 4;
    }

    //converte posição de matriz, para posição sequencial
    if (pos[1] == '0'){
        pos2 = 5;

    }else if (pos[1] == '1'){
        pos2 = 4;

    }else if (pos[1] == '2'){
        pos2 = 3;

    }else if (pos[1] == '3'){
        pos2 = 2;

    }else if (pos[1] == '4'){
        pos2 = 1;
    }

    /* converte posição de matriz, para posição sequencial
       exemplo [2][0] (linha 3, coluna 3) para 10
       lembrando que o índice começa em zero
    */
    return (pos1 * DIMENSAO) + (DIMENSAO - pos2);
}


/* Retorno:
    0 - jogada marcada, uma mina e fim de jogo
    1 - jogada marcada, sem mina e jogo continua
    2 - jogada marcada, descobriu todas as minas
*/
int jogar(char *pos){

    /* converte as coordenadas (Ex: A1) para uma posição válida (Ex: 0) */
    int posicao = converte(pos);

    /* Marca onde o usuário jogou */
    tabuleiroJogada[posicao] = 1;

    /* Se tem uma mina */
    if (tabuleiroMina[posicao] == 1){
        /* fim do jogo */
        return 0;
    }

    /* Se não ganhou */
    if ( ganhou() == 0 ){
        //continua
        return 1;
    }else{
        //parabéns
        return 2;
    }
}


/* Verifica se o usuário ganhou o jogo
    0 - não ganhou
    1 - sim, ganhou o jogo
*/
int ganhou(){
    int a;
    int contador = 0;

    /* jogo tem 25 posições e 8 minas, então deve fazer 17 jogadas para vencer */
    int jogadasVencer = TOTAL_ELEMENTOS - TOTAL_MINAS;

    for (a = 0; a <= INDICE_FINAL; a++){
        if (tabuleiroJogada[a] == 1){
            contador++;
        }
    }

    if (contador == jogadasVencer){
        return 1;
    }else{
        return 0;
    }
}


/* Retorna a posição da peça que está a direita */
int pecaDireita(int posicao){
    return posicao + 1;
}

/* Verifica se o número pertence a borda direita
   Onde:
   0 - não
   1 - sim, essa posição pertence a borda direita
*/
int bordaDireita(int posicao){
    if ( inteiro(posicao + 1, DIMENSAO) ){
        return 1;
    } else {
        return 0;
    }
}


/* Retorna a posição da peça que está a esquerda */
int pecaEsquerda(int posicao){
    return posicao - 1;
}

/* Verifica se o número pertence a borda esquerda
   Onde:
   0 - não
   1 - sim, essa posição pertence a borda esquerda
*/
int bordaEsquerda(int posicao){
    if ( inteiro(posicao, DIMENSAO) ){
        return 1;
    } else {
        return 0;
    }
}


/* Retorna a posição da peça que está a cima */
int pecaSuperior(int posicao){
    return posicao - DIMENSAO;
}

/* Verifica se o número pertence a borda superior
   Onde:
   0 - não
   1 - sim, essa posição pertence a borda superior
*/
int bordaSuperior(int posicao){
    if ( posicao < DIMENSAO ){
        return 1;
    } else {
        return 0;
    }
}


/* Retorna a posição da peça que está a baixo */
int pecaInferior(int posicao){
    return posicao + DIMENSAO;
}

/* Verifica se o número pertence a borda inferior
   Onde:
   0 - não
   1 - sim, essa posição pertence a borda inferior
*/
int bordaInferior(int posicao){

    //ultima peça da borda inferior
    int ultima = (DIMENSAO * DIMENSAO) - 1;

    //primeira peça da borda inferior
    int primeira = (DIMENSAO * DIMENSAO) - DIMENSAO;

    if ( (posicao >= primeira) && (posicao <= ultima) ){
        return 1;
    } else {
        return 0;
    }
}


/* Retorna a posição da peça que está na parte superior esquerda */
int pecaSuperiorEsquerda(int posicao){
    return posicao - DIMENSAO - 1;
}

/* Retorna a posição da peça que está na parte superior direita */
int pecaSuperiorDireita(int posicao){
    return posicao - DIMENSAO + 1;
}

/* Retorna a posição da peça que está na parte inferior esquerda */
int pecaInferiorEsquerda(int posicao){
    return posicao + DIMENSAO - 1;
}

/* Retorna a posição da peça que está na parte inferior direita */
int pecaInferiorDireita(int posicao){
    return posicao + DIMENSAO + 1;
}

/* Verifica se um número é inteiro
   Onde retorna:
   0 - não
   1 - sim, este número é inteiro
*/
int inteiro(float numerador, float denominador){
    //fmod - retorna a parte fracionária, ou seja, se a parte fracionária é zero, então é um inteiro
    if ( fmod(numerador, denominador) == 0 ){
         return 1;
    } else {
         return 0;
    }
}
