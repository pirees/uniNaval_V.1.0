#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_PLAYERS 100

struct jogador {
    char nome[100];
    int pontuacao;
    int nivelRanking;
};

int nivel;

void salvarDadosUsuario(char[100], int pontuacao, int nivel);
void ranking();
void menuInicial();
void inserirUsername(int nivel);
void lerArquivoTxt();


/*MONTA A TABELA DE ACORDO COM A DIFICULDADE DO JOGO*/
void montarTabela(int tabuleiro[][nivel]){   
    int linha, coluna;

    for(linha=0 ; linha < nivel ; linha++ )
        for(coluna=0 ; coluna < nivel ; coluna++ )
            tabuleiro[linha][coluna]=-1;
}

/*MOSTRA A TABELA PARA O USUÁRIO COM AS CASAS QUE FORAM OU NÃO JOGADAS*/
void mostrarTabuleiro(int tabuleiro[][nivel], int pontos, char nomeJogador[100]){
    int linha, coluna;
    printf("                                                           ------------------------------------------------------------------\n");
    printf("                                                           |                    UniNaval - Sua emoção é aqui                |\n");
    printf("                                                           ------------------------------------------------------------------\n");
    printf("                                                           ------------------------------------------------------------------\n");
    printf("                                                           |      Digite 123 na linha para sair | Salvamento automático     |\n");
    printf("                                                           ------------------------------------------------------------------\n");
    printf("\n");
    printf("                                                                                    Jogador: %s \n", nomeJogador                );
    printf("                                                                                     Pontos: %i \n", pontos                     );
    printf("\n");
    
    printf("\n");
    for(coluna=0; coluna < nivel; coluna++){
            printf("\t| %d |", coluna + 1);
    }
    printf("\n");
    for(linha=0; linha < nivel; linha++ ){
        if(nivel == 5){
            printf("\t--------------------------------------\n");
        } else if( nivel == 7){
            printf("\t-----------------------------------------------------\n");
        } else{
            printf("\t---------------------------------------------------------------------\n");
        }
        printf("%d",linha+1);
        for(coluna=0; coluna < nivel; coluna++ ){
            if(tabuleiro[linha][coluna]==-1){
                printf("\t| ~ |");
            }else if(tabuleiro[linha][coluna]==0){
                printf("\t| A |");
            }else if(tabuleiro[linha][coluna]==1){
                printf("\t| N |");
            }
        }
            printf("\n");
    }
    
    salvarDadosUsuario(nomeJogador, pontos, nivel);
}

/*MONTA OS NÁVIOS DE MISTURADA*/    
void montarNavios(int navios[][2]){
    srand(time(NULL));
    int navio, ultima;

    for(navio=0 ; navio < nivel; navio++){
        navios[navio][0]= rand()%nivel;
        navios[navio][1]= rand()%nivel;
    }
}

/*MONTA A JOGADA COM O USUÁRIO*/
void jogadaUsuario(int tiro[2]){
    int opcao; 

    printf("\n");
    printf("Linha: ");
    scanf("%d",&tiro[0]);
    if(tiro[0] == 123){
        menuInicial();
    }
    tiro[0]--;
    
    printf("Coluna: ");
    scanf("%d",&tiro[1]);
    tiro[1]--;
}

/*VERIFICA SE A JOGADA ACERTOU NAVIO*/
int acertouNavio(int tiro[2], int navios[][2]){
    int navio;

    for(navio=0 ; navio < nivel ; navio++){
        if( tiro[0]==navios[navio][0] && tiro[1]==navios[navio][1]){
            printf("Você acertou em um navio com o tiro (%d,%d)\n",tiro[0]+1,tiro[1]+1);
            return 1;
        }
    }
    return 0;
}

/*ATUALIZA O TABULEIRA COM O ACERTO DO USUARIO E COM O ERRO*/
void atualizaTabuleiro(int tiro[2], int navios[][2], int tabuleiro[][nivel]){ 
    if(acertouNavio(tiro,navios))
        tabuleiro[tiro[0]][tiro[1]]=1;
    else
        tabuleiro[tiro[0]][tiro[1]]=0;
}

/*DICAS PARA O USUÁRIO*/
/*SERÁ REMOVIDO NO FUTURO*/
void dicas(int tiro[2], int navios[][2], int attempt){
        
    int linha=0, coluna=0,row;

    //contar quantos navios existem na linha/coluna
    for(row=0 ; row < 3 ; row++){
        if(navios[row][0]==tiro[0])
            linha++;
           if(navios[row][1]==tiro[1])
              coluna++;
    }

    printf("\nDica %d: \nLinha %d -> %d navios\nColuna %d -> %d navios\n",attempt,tiro[0]+1,linha,tiro[1]+1,coluna);
}

/*O JOGO RODA TODO AQUI*/
void rodarMenu(char nomeJogador[100]){
    int tabuleiro[nivel][nivel];
    int navios[nivel][2];
    int tiro[2];
    int tentativas=0, atingiu=0, pontos=0;
    char opcao;

    montarTabela(tabuleiro);
    montarNavios(navios);
    
    printf("\n");
    
    do{     
        mostrarTabuleiro(tabuleiro, pontos, nomeJogador);
        jogadaUsuario(tiro);
        tentativas++;
        if(tabuleiro[tiro[0]][tiro[1]] != -1){
            printf("Jogada já realizada");
            system("cls");
        }
        else if(acertouNavio(tiro, navios)){
            dicas(tiro,navios,tentativas);
            atingiu++;
            pontos++;
            system("cls");
        }
        else{
            system("cls");
            dicas(tiro,navios,tentativas);
        }
        
        atualizaTabuleiro(tiro,navios,tabuleiro);
    }
    
    while(atingiu!=nivel);

        printf("\n\n\nVocê fechou o jogo com %d tentativas \n", tentativas);
        printf("\n");
        mostrarTabuleiro(tabuleiro, pontos, nomeJogador);
        printf("\n");
        system("pause");
        menuInicial();
            
}

/*SALVA OS DADOS DO USUARIO EM UM ARQUIVO TXT*/
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

/*ORDERNA A PONTUACAO DE ACORDO COM OS DADOS DO TXT*/
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

/*LEITURA DE ARQUIVO*/
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

/*TELA PARA ESCOLHA DA DIFICULDADE*/
int escolherDificuldade(){
    int escolha;
    printf ("\n");
    printf ("                                                          ---------------------------------------------------\n");
    printf ("                                                          -      Escolha a dificuldade para o jogo          -\n");
    printf ("                                                          ---------------------------------------------------\n");
    printf ("\n");
    printf ("                                                          ---------------------------------------------------\n");
    printf ("                                                          -     1 - Fácil - Tabuleiro 5x5 (5 navios)        -\n");
    printf ("                                                          -     2 - Médio - Tabuleiro 7x7 (7 navios)        -\n");
    printf ("                                                          -     3 - Difícil - Tabuleiro 9x9 (9 navios)      -\n");
    printf ("                                                          ---------------------------------------------------\n");
    printf ("\n");
    printf ("                                                          Escolha o nível:  "                                   );
    scanf("%i", &escolha);

    if(escolha == 1){
        nivel = 5;   
    } else if (escolha == 2) {
       nivel = 7;
    } else {
       nivel = 9; 
    }
    
    system("cls");
    inserirUsername(nivel);

    return nivel;
}

/*TELA PARA INFORMA O NOME DO JOGADOR*/
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
    rodarMenu(nomeJogador);
}

/*MENU INICIAL*/
void menuInicial(){
    system("cls");
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
                escolherDificuldade();
                break;
            case 2:
                system("cls");
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

/*RANKING*/
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
        }
    }
}