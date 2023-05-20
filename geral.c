#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int nivel;

#define MAX_PLAYERS 50
#define TAMANHO_TABELA nivel
#define NUM_NAVIOS 3 

struct jogador {
    char nome[100];
    int pontuacao;
    int nivelRanking;
};

typedef struct {
    int linha;
    int coluna;
} Coordenada;

typedef struct {
    char simbolo;
    int tamanho;
    Coordenada cord[4];
} Navio;

void salvarDadosUsuario(char[100], int pontuacao, int nivel);
void ranking();
void menuInicial();
void inserirUsername(int nivel);
void lerArquivoTxt();
void rodarMenu(char nomeJogador[100]);

void montarTabela(char tabuleiro[TAMANHO_TABELA][TAMANHO_TABELA]){   
    int linha, coluna;

    for(linha=0 ; linha < nivel ; linha++ )
        for(coluna=0 ; coluna < nivel ; coluna++ )
            tabuleiro[linha][coluna]=-1;
}

void salvarDadosUsuario(char str[100], int pontuacao, int nivel){

   FILE *pont_arq; // cria variável ponteiro para o arquivo
   int found = 0;
   char input[100];
   char line[100];
   long int pos = 0;

   strcpy(input, str);
   
    // Abrir arquivo para leitura e gravação
    pont_arq = fopen("dadosUsuario.txt", "r+");
    if (pont_arq == NULL) {
        printf("Erro ao abrir arquivo\n");
    }

    // Procurar usuário no arquivo
   while (fgets(line, sizeof(line), pont_arq)) {
        if (strstr(line, input) != NULL) {
            found = 1;
            break;
        }
         pos = ftell(pont_arq);
    }

    fseek(pont_arq, pos, SEEK_SET);
   if (!found) {
        fprintf(pont_arq, "%s,%i,%i\n", input, pontuacao, nivel);
    } else {
        fprintf(pont_arq, "%s,%i,%i\n", input, pontuacao, nivel);
    }

    // Fechar arquivo
    fclose(pont_arq);
}


void ordernarPontuacao (struct jogador jogadores[], int n) {
    int i, j;
    struct jogador temp;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (jogadores[j].pontuacao < jogadores[j+1].pontuacao) {
                temp = jogadores[j];
                jogadores[j] = jogadores[j+1];
                jogadores[j+1] = temp;
            }
        }
    }
}

void lerArquivoTxt(){

  FILE *pont_arq;
  char *token;
  struct jogador jogadores[MAX_PLAYERS];
  char linha[100];
  int i, num_jogadores = 0;
  char nivel_str[100];
  
  //abrindo o arquivo_frase em modo "somente leitura"
  pont_arq = fopen("dadosUsuario.txt", "r");

    while (fgets(linha, 100, pont_arq) != NULL) {
        token = strtok(linha, ",");
        strncpy(jogadores[num_jogadores].nome, token, sizeof(jogadores[num_jogadores].nome));
        token = strtok(NULL, ",");
        jogadores[num_jogadores].pontuacao = atoi(token);
        token = strtok(NULL, ",");
        jogadores[num_jogadores].nivelRanking = atoi(token);

        num_jogadores++;
    }
    
    ordernarPontuacao(jogadores, num_jogadores);
    
    for (i = 0; i < num_jogadores; i++) {

        if (jogadores[i].nivelRanking == 5) {
            strcpy(nivel_str, "Fácil");
        } else if (jogadores[i].nivelRanking == 7) {
            strcpy(nivel_str, "Médio");
        } else {
            strcpy(nivel_str, "Difícil");
        } 

        printf("                                                                               %d. %s - %d - %s\n", i+1, jogadores[i].nome, jogadores[i].pontuacao, nivel_str);
    }
  
  //fechando o arquivo
  fclose(pont_arq);    
}

int escolherDificuldade(){
    int escolha;
    printf ("\n");
    printf ("                                                          ---------------------------------------------------\n");
    printf ("                                                          -      Escolha a dificuldade para o jogo          -\n");
    printf ("                                                          ---------------------------------------------------\n");
    printf ("\n");
    printf ("                                                          ---------------------------------------------------\n");
    printf ("                                                          -     1 - Fácil - Tabuleiro 5x5 (3 navios)        -\n");
    printf ("                                                          -     2 - Médio - Tabuleiro 7x7 (3 navios)        -\n");
    printf ("                                                          -     3 - Difícil - Tabuleiro 10x10 (3 navios)    -\n");
    printf ("                                                          ---------------------------------------------------\n");
    printf ("\n");
    printf ("                                                          Escolha o nível:  "                                   );
    scanf("%i", &escolha);

    if(escolha == 1){
        nivel = 5;   
    } else if (escolha == 2) {
       nivel = 7;
    } else {
       nivel = 10; 
    }
    
    system("cls");
    //system("clear");
    inserirUsername(nivel);

    return nivel;
}


void inserirUsername(nivel){
    char nomeJogador[100];
    
    printf ("\n");
    printf ("                                                          ---------------------------------------------------\n");  
    printf ("                                                          -     Informe o seu nome para iniciar o jogo:     -\n");
    printf ("                                                          ---------------------------------------------------\n"); 
    printf ("\n");
    printf ("                                                          Seu apelido: "                                        );
    scanf("%s", nomeJogador);
    system("cls");
    //system("clear");
    rodarMenu(nomeJogador);
}

void menuInicial(){
    system("cls");
    //system("clear");
    int choice;
    while(1){
        printf("\n");
        printf ("                                                                 *********************************************\n");
        printf ("                                                                 *        *Bem-vindo ao UniNaval Game*       *\n");
        printf ("                                                                 *********************************************\n");
        printf("\n");   
        printf ("                                                                 *********************************************\n"); 
        printf ("                                                                 *               1 - Jogar                   *\n");
        printf ("                                                                 *********************************************\n");
        printf ("                                                                 *               2 - Ranking                 *\n");
        printf ("                                                                 *********************************************\n");
        printf ("                                                                 *               3 - Sair                    *\n");
        printf ("                                                                 *********************************************\n");
        printf("\n");
        printf("                                                                 ---------------------------------------------\n");
        printf("                                                                            Escolha uma opção: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                system("cls");
            //system("clear");
                escolherDificuldade();
                break;
            case 2:
                system("cls");
            //system("clear");
                ranking();
                break;
            case 3:
                printf("Obrigado por nos visitar :)\n");
                exit(0);

            default:
                printf("Digite uma opção válida. \n");    
        }
    }
}

void ranking(){
    int choice;

    while(1){
        printf (" \n");
        printf ("                                                                 ---------------------------------------------------\n");
        printf ("                                                                 -        Veja a sua posição até o momento :)      -\n");
        printf ("                                                                 ---------------------------------------------------\n");
        printf (" \n");
        printf("                                                                                      Ranking                        \n");
        printf ("                                                                 ---------------------------------------------------\n");
        printf (" \n");
        lerArquivoTxt();
        printf (" \n");
        printf ("                                                                 ---------------------------------------------------\n");
        printf (" \n");

        printf ("                                                                 [1] - Pressione para voltar                         \n");
        printf ("                                                                 ---------------------------------------------------\n");
        printf (" \n");
        scanf("%d", &choice);

        switch(choice) {
                case 1:
                  menuInicial();
                  break;

                default:
                    printf("Digite uma opção válida. \n");
                    system("cls");                        
                    //system("clear");
        }
    }
}

void mostrarTabuleiro(char tabuleiro[TAMANHO_TABELA][TAMANHO_TABELA], int pontos, char nomeJogador[100]) {
    char navioPosicao = '~';
    printf("                                                           ------------------------------------------------------------------\n");
    printf("                                                           |                    UniNaval - Sua emoção é aqui                |\n");
    printf("                                                           ------------------------------------------------------------------\n");
    printf("                                                           ------------------------------------------------------------------\n");
    printf("                                                           |   Navio com 2 casas |  Navio com 3 casas | Navio com 4 casas   |\n");
    printf("                                                           ------------------------------------------------------------------\n");
    printf("\n");
    printf("                                                           ------------------------------------------------------------------\n");
    printf("                                                           |             A - Água | X - Acertou | ~ - Não jogou             |\n");
    printf("                                                           |                Acerto +3 pontos | Água -1 ponto                |\n");
    printf("                                                           ------------------------------------------------------------------\n");
    printf("\n");
    printf("                                                                                    Jogador: %s \n", nomeJogador                );
    printf("                                                                                     Pontos: %i \n", pontos                     );
    printf("\n");
    printf("                                                           ------------------------------------------------------------------\n");
    printf("                                                           |      Digite 123 na linha para sair | Salvamento automático     |\n");
    printf("                                                           ------------------------------------------------------------------\n");
    printf("\n");
    

    printf("  ");
    int i, j;
    if(nivel == 5){
        printf("\t\t\t\t\t\t\t\t\t");
        for (i = 0; i < TAMANHO_TABELA; i++) {
            printf("    %2d ", i);
        }
        printf("\n");
        for (i = 0; i < TAMANHO_TABELA; i++) {
            printf("\t\t\t\t\t\t\t\t\t");
            printf(" %d|", i);
            for (j = 0; j < TAMANHO_TABELA; j++) {
                if (tabuleiro[i][j] == 'S') {
                    printf("  %-2c  |", navioPosicao);
                } else {
                    printf("  %-2c  |", tabuleiro[i][j]);
                }
            }
            printf("\n");
        }
        salvarDadosUsuario(nomeJogador, pontos, nivel);
    } else if(nivel == 7){
        printf("\t\t\t\t\t\t\t\t");
        for (i = 0; i < TAMANHO_TABELA; i++) {
            printf("    %2d ", i);
        }
        printf("\n");
        for (i = 0; i < TAMANHO_TABELA; i++) {
            printf("\t\t\t\t\t\t\t\t");
            printf(" %d|", i);
            for (j = 0; j < TAMANHO_TABELA; j++) {
                if (tabuleiro[i][j] == 'S') {
                    printf("  %-2c  |", navioPosicao);
                } else {
                    printf("  %-2c  |", tabuleiro[i][j]);
                }
            }
            printf("\n");
        }
        salvarDadosUsuario(nomeJogador, pontos, nivel);
    }  else {
        printf("\t\t\t\t\t\t\t");
        for (i = 0; i < TAMANHO_TABELA; i++) {
            printf("    %2d ", i);
        }
        printf("\n");
        for (i = 0; i < TAMANHO_TABELA; i++) {
            printf("\t\t\t\t\t\t\t");
            printf(" %d|", i);
            for (j = 0; j < TAMANHO_TABELA; j++) {
                if (tabuleiro[i][j] == 'S') {
                    printf("  %-2c  |", navioPosicao);
                } else {
                    printf("  %-2c  |", tabuleiro[i][j]);
                }
            }
            printf("\n");
        }
        salvarDadosUsuario(nomeJogador, pontos, nivel);
    }
} 

int jogadaValidaUsuario(int linha, int coluna) {
    return linha >= 0 && linha < TAMANHO_TABELA && coluna >= 0 && coluna < TAMANHO_TABELA;
}

int navioValido(Navio navio) {
    int i;
    for (i = 0; i < navio.tamanho; i++) {
        if (!jogadaValidaUsuario(navio.cord[i].linha, navio.cord[i].coluna)) {
            return 0;
        }
    }
    return 1;
}

int sobreporNavio(Navio navio, char tabuleiro[TAMANHO_TABELA][TAMANHO_TABELA]) {
    int i, j;
    
    for (i = 0; i < navio.tamanho; i++) {
        int linha = navio.cord[i].linha;
        int coluna = navio.cord[i].coluna;
        //if (tabuleiro[linha][coluna] != '-') {
        if (tabuleiro[linha][coluna] != '~') {    
            return 1;
        }
    }
    return 0;
}

void inserirNavios(char tabuleiro[TAMANHO_TABELA][TAMANHO_TABELA], Navio navios[]) {
    int tamanhos[NUM_NAVIOS] = {2, 3, 4};
    int i, j;
    srand(time(NULL));
    for (i = 0; i < NUM_NAVIOS; i++) {
        Navio navio;
        navio.tamanho = tamanhos[i];
        navio.simbolo = 'S';
        do {
            int start_linha = rand() % TAMANHO_TABELA;
            int start_coluna = rand() % TAMANHO_TABELA;
            int direcao = rand() % 2; // 0 para horizontal, 1 para vertical
            if (direcao == 0) { // horizontal
                for (j = 0; j < navio.tamanho; j++) {
                    navio.cord[j].linha = start_linha;
                    navio.cord[j].coluna = start_coluna + j;
                }
            } else { // vertical
                for (j = 0; j < navio.tamanho; j++) {
                    navio.cord[j].linha = start_linha + j;
                    navio.cord[j].coluna = start_coluna;
                }
            }
        } while (!navioValido(navio) || sobreporNavio(navio, tabuleiro));
        for (j = 0; j < navio.tamanho; j++) {
            int linha = navio.cord[j].linha;
            int coluna = navio.cord[j].coluna;
            tabuleiro[linha][coluna] = 'S';
        }
        navios[i] = navio;
    }
}

int contarNavios(char tabuleiro[TAMANHO_TABELA][TAMANHO_TABELA]) {
    int count = 0;
    int i, j;
    for (i = 0; i < TAMANHO_TABELA; i++) {
        for (j = 0; j < TAMANHO_TABELA; j++) {
            if (tabuleiro[i][j] == 'S') {
                count++;
            }
        }
    }
    return count;
}

void rodarMenu(char nomeJogador[100]){
    int i, j;
    srand(time(NULL));
    char tabuleiro[TAMANHO_TABELA][TAMANHO_TABELA];
    Navio navios[NUM_NAVIOS];
    for (i = 0; i < TAMANHO_TABELA; i++) {
        for (j = 0; j < TAMANHO_TABELA; j++) {
            //tabuleiro[i][j] = '-';
            tabuleiro[i][j] = '~';
        }
    }

    inserirNavios(tabuleiro, navios);
    int numeroNavios = contarNavios(tabuleiro);
    int num_tentativas = 0;
    int pontos = 0;

    while (numeroNavios > 0) {
        mostrarTabuleiro(tabuleiro, pontos, nomeJogador);
        printf("\n");
        //char guess_row;
        int guess_row;
        int guess_col;
        printf("\n");
        printf("Existem %d partes de navio no tabuleiro.\n\n", numeroNavios);

        printf("Linha: ");
        scanf("%d", &guess_row);
        if(guess_row == 123){
            menuInicial();
        }
        printf("Coluna: ");
        scanf("%d", &guess_col);

        int row = guess_row;
        int col = guess_col;

        if (!jogadaValidaUsuario(row, col)) {
            system("CLS");
            //system("clear");
            printf("Jogada inválida.\n\n");
            continue;
            
        }
        if (row == 24 && col == 11) {
            menuInicial();
            continue;
        }
        system("CLS");
        //system("clear");
        //if (tabuleiro[row][col] == '-') {
        if (tabuleiro[row][col] == '~') {    
            printf("Tiro na água!\n\n");
            tabuleiro[row][col] = 'A';
            pontos--;                    
        } else if (tabuleiro[row][col] == 'S') {
            printf("Você acertou uma parte do navio!\n\n");
            tabuleiro[row][col] = 'X';
            num_tentativas++;
            pontos+=3;
            numeroNavios--;
        } else {
            printf("Jogada já foi atingida.\n\n");
        }
    }
    printf("\n");
    mostrarTabuleiro(tabuleiro, pontos, nomeJogador);
    pontos++;
    printf("Parabéns, você ganhou o jogo em %d tentativas!\n", num_tentativas);
    printf("\n");
    system("pause");
    menuInicial();
}