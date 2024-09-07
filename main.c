#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TECLA_ESC 27       // o c�digo da tecla ESC � 27
#define OCULTAR 0
#define REVELAR 1
#define PERDEU 0
#define GANHOU 2
#define DIMENSAO 5
#define INDICE_FINAL 24    // �ndice final do vetor
#define TOTAL_ELEMENTOS 25 // total de elementos

/* Tabuleiro � de 5 x 5, ent�o temos 25 c�lulas
   30% das c�lulas devem conter minas, ent�o 30% de 25 � 7,5 arredondando temos 8 minas. */
#define TOTAL_MINAS 8

/* Vetor com 25 elementos representando tabuleiro, �ndice de 0 a 24
   Guarda se a posi��o possui ou n�o minas.
   Onde:
   0 - n�o existe mina
   1 - sim, existe uma mina nesta posi��o
*/
int tabuleiroMina[TOTAL_ELEMENTOS];

/* Vetor com 25 elementos representando tabuleiro, �ndice de 0 a 24
   Guarda se o usu�rio j� jogou em determinada posi��o.
   Onde:
   0 - n�o jogou
   1 - sim, j� jogou nesta posi��o do tabuleiro
*/
int tabuleiroJogada[TOTAL_ELEMENTOS];

/* PROT�TIPO DAS FUN��ES */
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

    /* Vari�vel para pegar a tecla digitada */
    int tecla;

    /* Vari�vel para pegar a posi��o que o usu�rio quer jogar*/
    char posicao[4];

    /* Retorno do processamento da jogada */
    int resposta;

    //A fun��o srand inicializa a fun��o que ir� retornar um n�mero aleat�rio.
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

        /* obt�m c�digo da tecla digitada */
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

            //TESTE - REMOVA O COMENT�RIO ABAIXO E VEJA A RESPOSTA DO JOGO, �TIL PARA TESTAR QUANDO GANHA
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

        /* Enquanto n�o perder o jogo ou ganhar, continua */
        } while ( (resposta != PERDEU) && (resposta != GANHOU) );

    /* S� sai quando o comando exit(0) for executado */
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
        //n�mero aleat�rio de 0 a 4
        pos = rand() % TOTAL_ELEMENTOS;

        //Se n�o existe mina ainda
        if (tabuleiroMina[pos] == 0){

            //marca que agora tem uma mina nesta posi��o
            tabuleiroMina[pos] = 1;

            //mais uma mina foi adicionada
            totalMinas++;
        }

    //enquanto n�o tiver 8 minas continua
    } while(totalMinas != TOTAL_MINAS);
}

/* O jogo normalmente s� deve mostrar as posi��es j� jogadas
   Onde
     0 - n�o revelar o jogo
     1 - revelar o jogo
*/
void desenharTabuleiro(int revelar){
    int a;
    int contador = 0;
    int minasRedor;

    char letras[] = "ABCDE";
    int letra = 0;

    /* S� DEVE MOSTRAR POSI��ES J� JOGADAS */

    printf("\n  01234 \n");

    for (a = 0; a <= INDICE_FINAL; a++){

        if (contador == 0){
            printf("%c ", letras[letra]);

            //pr�xima letra da linha
            letra++;
        }

        contador++;

        //Se n�o � para revelar o jogo
        if (revelar == 0){

            //Se posi��o n�o foi escolhida
            if (tabuleiroJogada[a] == 0){

                //oculta
                printf("?");
            }else{
                //verifica e mostra quantas minas tem ao redor da posi��o
                minasRedor = contarMinas(a);
                printf("%d", minasRedor);
            }

        }else{ // Se � para revelar o jogo

            //Se tem mina
            if (tabuleiroMina[a] == 1){
                printf("*");
            }else{
                //mostra quantas minas tem ao redor da posi��o
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


/* conta quantas minas tem ao redor de uma posi��o */
int contarMinas(int posicao){

    int contador = 0;
    int peca = 0;

    //Se a pe�a n�o estiver na borda direita
    if ( !bordaDireita(posicao) ){

        //obt�m a posicao da pe�a a sua direita
        peca = pecaDireita(posicao);

        //se for uma mina
        if ( tabuleiroMina[peca] == 1){
            contador++;
        }
    }

    //Se a pe�a n�o estiver na borda esquerda
    if ( !bordaEsquerda(posicao) ){

        //obt�m a posicao da pe�a a sua esquerda
        peca = pecaEsquerda(posicao);

        //se for uma mina
        if ( tabuleiroMina[peca] == 1){
            contador++;
        }
    }

    //Se a pe�a n�o estiver na borda superior
    if ( !bordaSuperior(posicao) ){

        //obt�m a posicao da pe�a superior
        peca = pecaSuperior(posicao);

        //se for uma mina
        if ( tabuleiroMina[peca] == 1){
            contador++;
        }
    }

    //Se a pe�a n�o estiver na borda inferior
    if ( !bordaInferior(posicao) ){

        //obt�m a posicao da pe�a inferior
        peca = pecaInferior(posicao);

        //se for uma mina
        if ( tabuleiroMina[peca] == 1){
            contador++;
        }
    }

    /* DIAGONAIS */

    //Se a pe�a n�o estiver na borda superior ou na borda esquerda
    if ( !bordaSuperior(posicao) && !bordaEsquerda(posicao) ){

        //obt�m a posicao da pe�a superior esquerda
        peca = pecaSuperiorEsquerda(posicao);

        //se for uma mina
        if ( tabuleiroMina[peca] == 1){
            contador++;
        }
    }

    //Se a pe�a n�o estiver na borda superior ou na borda direita
    if ( !bordaSuperior(posicao) && !bordaDireita(posicao) ){

        //obt�m a posicao da pe�a superior direita
        peca = pecaSuperiorDireita(posicao);

        //se for uma mina
        if ( tabuleiroMina[peca] == 1){
            contador++;
        }
    }

    //Se a pe�a n�o estiver na borda inferior esquerda
    if ( !bordaInferior(posicao) && !bordaEsquerda(posicao) ){

        //obt�m a posicao da pe�a inferior esquerda
        peca = pecaInferiorEsquerda(posicao);

        //se for uma mina
        if ( tabuleiroMina[peca] == 1){
            contador++;
        }
    }

    //Se a pe�a n�o estiver na borda inferior direita
    if ( !bordaInferior(posicao) && !bordaDireita(posicao) ){

        //obt�m a posicao da pe�a inferior direita
        peca = pecaInferiorDireita(posicao);

        //se for uma mina
        if ( tabuleiroMina[peca] == 1){
            contador++;
        }
    }

    return contador;
}


/* Converte caractere (char) para posi��o v�lida na matriz, ou seja, um n�mero de 0 a 4
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

    //converte para mai�sculo
    pos[0] = toupper(pos[0]);

    //converte letra para n�mero
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

    //converte posi��o de matriz, para posi��o sequencial
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

    /* converte posi��o de matriz, para posi��o sequencial
       exemplo [2][0] (linha 3, coluna 3) para 10
       lembrando que o �ndice come�a em zero
    */
    return (pos1 * DIMENSAO) + (DIMENSAO - pos2);
}


/* Retorno:
    0 - jogada marcada, uma mina e fim de jogo
    1 - jogada marcada, sem mina e jogo continua
    2 - jogada marcada, descobriu todas as minas
*/
int jogar(char *pos){

    /* converte as coordenadas (Ex: A1) para uma posi��o v�lida (Ex: 0) */
    int posicao = converte(pos);

    /* Marca onde o usu�rio jogou */
    tabuleiroJogada[posicao] = 1;

    /* Se tem uma mina */
    if (tabuleiroMina[posicao] == 1){
        /* fim do jogo */
        return 0;
    }

    /* Se n�o ganhou */
    if ( ganhou() == 0 ){
        //continua
        return 1;
    }else{
        //parab�ns
        return 2;
    }
}


/* Verifica se o usu�rio ganhou o jogo
    0 - n�o ganhou
    1 - sim, ganhou o jogo
*/
int ganhou(){
    int a;
    int contador = 0;

    /* jogo tem 25 posi��es e 8 minas, ent�o deve fazer 17 jogadas para vencer */
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


/* Retorna a posi��o da pe�a que est� a direita */
int pecaDireita(int posicao){
    return posicao + 1;
}

/* Verifica se o n�mero pertence a borda direita
   Onde:
   0 - n�o
   1 - sim, essa posi��o pertence a borda direita
*/
int bordaDireita(int posicao){
    if ( inteiro(posicao + 1, DIMENSAO) ){
        return 1;
    } else {
        return 0;
    }
}


/* Retorna a posi��o da pe�a que est� a esquerda */
int pecaEsquerda(int posicao){
    return posicao - 1;
}

/* Verifica se o n�mero pertence a borda esquerda
   Onde:
   0 - n�o
   1 - sim, essa posi��o pertence a borda esquerda
*/
int bordaEsquerda(int posicao){
    if ( inteiro(posicao, DIMENSAO) ){
        return 1;
    } else {
        return 0;
    }
}


/* Retorna a posi��o da pe�a que est� a cima */
int pecaSuperior(int posicao){
    return posicao - DIMENSAO;
}

/* Verifica se o n�mero pertence a borda superior
   Onde:
   0 - n�o
   1 - sim, essa posi��o pertence a borda superior
*/
int bordaSuperior(int posicao){
    if ( posicao < DIMENSAO ){
        return 1;
    } else {
        return 0;
    }
}


/* Retorna a posi��o da pe�a que est� a baixo */
int pecaInferior(int posicao){
    return posicao + DIMENSAO;
}

/* Verifica se o n�mero pertence a borda inferior
   Onde:
   0 - n�o
   1 - sim, essa posi��o pertence a borda inferior
*/
int bordaInferior(int posicao){

    //ultima pe�a da borda inferior
    int ultima = (DIMENSAO * DIMENSAO) - 1;

    //primeira pe�a da borda inferior
    int primeira = (DIMENSAO * DIMENSAO) - DIMENSAO;

    if ( (posicao >= primeira) && (posicao <= ultima) ){
        return 1;
    } else {
        return 0;
    }
}


/* Retorna a posi��o da pe�a que est� na parte superior esquerda */
int pecaSuperiorEsquerda(int posicao){
    return posicao - DIMENSAO - 1;
}

/* Retorna a posi��o da pe�a que est� na parte superior direita */
int pecaSuperiorDireita(int posicao){
    return posicao - DIMENSAO + 1;
}

/* Retorna a posi��o da pe�a que est� na parte inferior esquerda */
int pecaInferiorEsquerda(int posicao){
    return posicao + DIMENSAO - 1;
}

/* Retorna a posi��o da pe�a que est� na parte inferior direita */
int pecaInferiorDireita(int posicao){
    return posicao + DIMENSAO + 1;
}

/* Verifica se um n�mero � inteiro
   Onde retorna:
   0 - n�o
   1 - sim, este n�mero � inteiro
*/
int inteiro(float numerador, float denominador){
    //fmod - retorna a parte fracion�ria, ou seja, se a parte fracion�ria � zero, ent�o � um inteiro
    if ( fmod(numerador, denominador) == 0 ){
         return 1;
    } else {
         return 0;
    }
}
