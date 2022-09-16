// Disciplina: Análise e projeto de algorítimos- Linguagem C
// Autor(a): Julia Rampani TIA- 42119529
// Autor(a) Natalia Teixeira TIA- 42129397
 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//A função abaixo vai ter as declarações das variáveis que serão utilizadas durante o programa.
enum Move { cima = 0, baixo = 1, esquerda = 2, direita = 3 };
#define linhas    4
#define colunas 4
int f_linha;
int f_coluna;
int m[linhas][colunas];
const int nShuffles = 100;

/* A função abaixo é responsável pela atualização das posições da peça movida e o espaço vazio. */
int atualiza(enum Move move){
    const int dx[] = {  0,  0, -1, +1 };
    const int dy[] = { -1, +1,  0,  0 };
    int i = f_linha     + dy[move];
    int j = f_coluna + dx[move];
    if ( i >= 0 && i < linhas && j >= 0 && j < colunas ){
        m[f_linha][f_coluna] = m[i][j];
        m[i][j] = 0; f_linha = i; f_coluna = j;
        return 1;
    }
    return 0;
}

/*A função abaixo irá gerar um título na tela, lerá o arquivo da matriz e imprimirá o conteúdo do arquivo na tela.
A matriz que está no arquivo ladrilho.txt será o tabuleiro do jogo. */
void Game_setup(void) {
    int i, j;
    int linha;
    int coluna;

printf("\n\n");
  printf("                                                                                                                                                                                             \n");
  printf("                   8 8888                  .8.          8 888888888o.      8 888888888o.    8 8888 b.             8 8 8888        8     ,o888888o.     \n");
  printf("                   8 8888                 .888.         8 8888    `^888.   8 8888    `88.   8 8888 888o.          8 8 8888        8  . 8888     `88.   \n");
  printf("                   8 8888                :88888.        8 8888        `88. 8 8888     `88   8 8888 Y88888o.       8 8 8888        8 ,8 8888       `8b  \n");
  printf("                   8 8888               . `88888.       8 8888         `88 8 8888     ,88   8 8888 .`Y888888o.    8 8 8888        8 88 8888        `8b \n");
   printf("                  8 8888              .8. `88888.      8 8888          88 8 8888.   ,88'   8 8888 8o. `Y888888o. 8 8 8888        8 88 8888         88 \n");
   printf("                  8 8888             .8`8. `88888.     8 8888          88 8 888888888P'    8 8888 8`Y8o. `Y88888o8 8 8888        8 88 8888         88 \n");
   printf("                  8 8888            .8' `8. `88888.    8 8888         ,88 8 8888`8b        8 8888 8   `Y8o. `Y8888 8 8888888888888 88 8888        ,8P \n");
   printf("                  8 8888           .8'   `8. `88888.   8 8888        ,88' 8 8888 `8b.      8 8888 8      `Y8o. `Y8 8 8888        8 `8 8888       ,8P  \n");
   printf("                  8 8888          .888888888. `88888.  8 8888    ,o88P'   8 8888   `8b.    8 8888 8         `Y8o.` 8 8888        8  ` 8888     ,88'   \n");
   printf("                  8 888888888888 .8'       `8. `88888. 8 888888888P'      8 8888     `88.  8 8888 8            `Yo 8 8888        8     `8888888P'     \n");
printf("\n\n");


	FILE *ladrilho_matriz;
	ladrilho_matriz = fopen("ladrilho.txt", "r");

    fscanf(ladrilho_matriz, "%d %d", &linha, &coluna);
    for ( i = 0; i < linha; i++ )
        for ( j = 0; j < coluna; j++ )
            fscanf(ladrilho_matriz, "%d", &m[i][j]);
            printf("%3d", m[i][j]);
            m[i-1][j-1] = 0;
            f_linha = linhas - 1;
            f_coluna = colunas - 1;
    printf("\n");
    fclose(ladrilho_matriz);
    return 0;
}

/* A função abaixo verifica quando o espaço vazio chega na posição final.*/
int fim(void){
    int i,j; int k = 1;
    for ( i = 0; i < linhas; i++ )
        for ( j = 0; j < colunas; j++ )
            if ( (k < linhas*colunas) && (m[i][j] != k++ ) )
                return 0;
    return 1;
}

/* A função abaixo mostra a nova posição do tabuleiro, depois do movimento.*/
void painel(){
    int i,j;
    putchar('\n');
    for ( i = 0; i < linhas; i++ )
        for ( j = 0; j < colunas; j++ ){
            if ( m[i][j] )
                printf(j != colunas-1 ? " %2d " : " %2d \n", m[i][j]);
            else
                printf(j != colunas-1 ? " %2s " : " %2s \n", "");
        }
    putchar('\n');
}

/* A função abaixo mostra a mensagem de texto, quando o jogo é finalizado.*/
void mensagem(char* text){
    printf("\n%s\n", text);
}

/* A função abaixo pergunta qual direção o jogador deseja ir e irá trocar a peça com o espaço vazio.
 Exemplo: o espaço branco está acima do número 1, aperte c = cima, a peça vai para a posição do espaço vazio. */
enum Move Controller_getMove(void){
    int c;
    for(;;){
        printf("%s", "Selecione o tipo de movimento: b = baixo/c= cima/d= direita/e= esquerda : ");
        c = getchar();
        while( getchar() != '\n' )
            ;
        switch ( c ){
            case 27: exit(EXIT_SUCCESS);
            case 'c' : return cima;
            case 'b' : return baixo;
            case 'e' : return esquerda;
            case 'd' : return direita;
        }
    }
}

/* A função abaixo faz uma pausa após o final do jogo, até que se pressione qualquer tecla. */
void Controller_pause(void){
    getchar();
}

/* A função main fará a chamada de todas as funções anteriores para que ocorra a execução do programa. */
int main(void){

    srand((unsigned)time(NULL));

    do Game_setup(); while ( fim() );

    painel();
    while( !fim() ){
        atualiza( Controller_getMove() );
        painel();
    }

    mensagem("Parábens, você ganhou!");
    Controller_pause();

    return EXIT_SUCCESS;
}
