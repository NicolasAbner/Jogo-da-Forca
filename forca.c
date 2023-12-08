#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "forca.h" //HEADER

// Variaveis globais
char chutes[26];
int chutesDados = 0;
char palavra[TAMANHO_PALAVRA];
int lingua;

//FUNÇÕES

//ESCOLHE IDIOMA
int idioma(){
    
    int idiomaEscolha;
    printf("ESCOLHA O IDIOMA DA FORCA:\n");
    printf("1- PORTUGUES\n");
    printf("2- ENGLISH\n");
    scanf("%d", &idiomaEscolha);

    if (idiomaEscolha == 1){
        lingua = 1;
        
    } else{
        if (idiomaEscolha == 2){
            lingua = 0;
        }else{
            printf("OPCAO INVALIDA! TENTE NOVAMENTE\n");
        
            exit(1);
        }
    }

    return lingua;
    
}
//MENU
void abertura(){

    printf("/******************/\n");
    printf("/* Jogo de Forca */\n");
    printf("/****************/\n\n");

} 
//CHUTE DE LETRA
void chuta(){

    char chute;
    scanf(" %c", &chute);
    chutes[chutesDados] = chute;
    chutesDados++;
    
}
//VERIFICA CHUTE
int jachutou(char letra){
    
    int achou = 0;
    for (int j = 0; j < chutesDados; j++){
        if (chutes[j] == letra){
            achou = 1;
            break;
        }
    }

    return achou;

}
//VERIFICA PALAVRA
void desenhaForca(){

    int erros = chutesErrados();

    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (erros>=1?'(':' '), 
        (erros>=1?'_':' '), (erros>=1?')':' '));
    printf(" |      %c%c%c  \n", (erros>=3?'\\':' '), 
        (erros>=2?'|':' '), (erros>=3?'/': ' '));
    printf(" |       %c     \n", (erros>=2?'|':' '));
    printf(" |      %c %c   \n", (erros>=4?'/':' '), 
        (erros>=5?'\\':' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");


    for (int i = 0; i < strlen(palavra); i++){

        int achou = jachutou(palavra[i]);
        if (achou) {
            printf("%c ", palavra[i]);
        } else {
            printf("_ ");
        }
    }

    printf("\n");

}
//USER INPUT PARA ADICIONAR PALAVRA
void adicionaPalavra(){

    int escolha;
    printf("VOCE DESEJA ADICIONAR UMA NOVA PALAVRA PARA O JOGO?\n");
    printf("1- SIM\n");
    printf("2- NAO\n");
    scanf(" %d", &escolha);

    if (escolha == 1){
        char novaPalavra[TAMANHO_PALAVRA];
        printf("QUAL A NOVA PALAVRA?");
        scanf(" %s", &novaPalavra);

        FILE* f ;

        if (lingua == 1){
            f = fopen("palavras.txt", "r+");
        } else{
            f = fopen("words.txt", "r+");
        }
        
        if (f == 0){
            printf("BANCO DE DADOS INDISPONIVEL, VOLTE MAIS TARDE. \n");
            exit(1);
        }

        int qtd;
        fscanf(f, " %d", &qtd);
        qtd++;

        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", qtd);

        fseek(f, 0, SEEK_END);
        fprintf(f, " \n%s", novaPalavra);
        fclose(f);
        
    }else{
        printf("OBRIGADO POR JOGAR! VOLTE SEMPRE!");
        exit(1);
    }
}
//ESCOLHE PALAVRA MISTERIOSA
void escolhePalavra(){

    FILE* f;

    if (lingua == 1){
        f = fopen("palavras.txt", "r");

    } else{
        f = fopen("words.txt", "r");
    }

    if (f == 0){
        printf("BANCO DE DADOS INDISPONIVEL, VOLTE MAIS TARDE. \n");
        exit(1);
    }

    int qtddepalavras;
    fscanf(f, "%d", &qtddepalavras);


    srand(time(0));
    int randomico = rand () % qtddepalavras; 

    for (int i = 0; i < randomico; i++){
        fscanf(f, "%s", palavra);
    }    

    fclose(f);

}
//VERIFICA PALAVRA FOI CHUTA = GANHOU/NÃO GANHOU
int acertou(){
    for (int i = 0; i < strlen(palavra); i++){
        if (!jachutou(palavra[i])){
            return 0;
        }
    }

    return 1;
}
//CONTA CHUTES ERRADOS - GERAR FORCA
int chutesErrados(){
    int erros = 0;

    for (int i = 0; i < chutesDados; i++){
        int existe = 0;

        for (int j = 0; j < strlen(palavra); j++){
            if(chutes[i] == palavra[j]){
                existe = 1;
                break;
            }
        }
        if (!existe) erros++;
           
    }
    return erros;

}
//VERIFICA TENTATIVAS - PERDEU
int enforcou(){
    return chutesErrados() >= 6;

}
// CÓDIGO MAIN
int main(){

    int idiomaPalavra = idioma();

    escolhePalavra(idiomaPalavra);
    abertura();

    do {
        
        desenhaForca();
        chuta();

    } while (!acertou() && !enforcou());
    if (acertou()){
        
        printf("\nPARABENS, VOCÊ VENCEU!\n\n");
        printf("A PALAVRA ERA: %s\n", palavra);

        printf("       ___________      \n");
        printf("      '._==_==_=_.'     \n");
        printf("      .-\\:      /-.    \n");
        printf("     | (|:.     |) |    \n");
        printf("      '-|:.     |-'     \n");
        printf("        \\::.    /      \n");
        printf("         '::. .'        \n");
        printf("           ) (          \n");
        printf("         _.' '._        \n");
        printf("        '-------'       \n\n");

        adicionaPalavra(lingua);

    }else{

        printf("\nISH, FOSTES ENFORCADO... BOA SORTE NA PROXIMA\n");
        printf("A PALAVRA ERA: %s\n", palavra);
        

        printf("    _______________         \n");
        printf("   /               \\       \n"); 
        printf("  /                 \\      \n");
        printf("//                   \\/\\  \n");
        printf("\\|   XXXX     XXXX   | /   \n");
        printf(" |   XXXX     XXXX   |/     \n");
        printf(" |   XXX       XXX   |      \n");
        printf(" |                   |      \n");
        printf(" \\__      XXX      __/     \n");
        printf("   |\\     XXX     /|       \n");
        printf("   | |           | |        \n");
        printf("   | I I I I I I I |        \n");
        printf("   |  I I I I I I  |        \n");
        printf("   \\_             _/       \n");
        printf("     \\_         _/         \n");
        printf("       \\_______/           \n");

    }
    
}