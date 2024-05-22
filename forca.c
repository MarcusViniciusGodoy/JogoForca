#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "forca.h"

char palavra_secreta[TAMANHO_PALAVRA];
char chutes[26];
int chutes_dados = 0;

void inicio(){
    printf("---------------\n");
    printf(" Jogo de Forca \n");
    printf("---------------\n\n");
}

void chute(){ 
    char palpite;
    printf("Qual letra? ");
    scanf(" %c", &palpite);
       
    chutes[chutes_dados] = palpite;
    chutes_dados++;
}

int ja_chutou(char letra){
    int achou = 0;
           
    for(int j=0;j<chutes_dados;j++){
       if(chutes[j] == letra){
          achou = 1;
          break;
       }
    }
    
    return achou;
}

void desenha_forca(){
    int erros = chutes_errados();

    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (erros>=1?'(':' '), 
         (erros>=1?'_':' '), (erros>=1?')':' '));
    printf(" |      %c%c%c  \n", (erros>=3?'\\':' '), 
         (erros>=2?'|':' '), (erros>=3?'/': ' '));
    printf(" |       %c     \n", (erros>=2?'|':' ')); 
    printf(" |      %c %c   \n", (erros>=4?'/':' '), 
         (erros>=4?'\\':' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");

    for(int i=0;i<strlen(palavra_secreta); i++){
        int achou = ja_chutou(palavra_secreta[i]);
        
        if(achou){
           printf("%c ",palavra_secreta[i]);
        }else{
           printf("_ ");
    	}
    }
    printf("\n");
    
}

void adiciona_palavra(){
    char quer;
    
    printf("Você deseja adicionar uma palavra no jogo? [s/n]\n");
    scanf(" %c", &quer);
    
    if(quer == 's'){
       char nova_palavra[TAMANHO_PALAVRA];
       printf("Qual a nova palavra? \n");
       scanf("%s", nova_palavra);
       
       FILE* f;
       
       f = fopen("palavra.txt", "r+");
       if(f == 0){
           printf("Desculpe banco de dados não disponível!\n\n");
           exit(1);
       }
       
       int qtd;
       fscanf(f, "%d", &qtd);
       qtd++;
       
       fseek(f, 0, SEEK_SET);
       fprintf(f, "%d", qtd);
       
       fseek(f, 0, SEEK_END);
       fprintf(f, "\n%s", nova_palavra);
       fclose(f);
    }
}

void escolhe_palavra(){
    FILE* f;
    
    f = fopen("palavra.txt", "r");
    if(f == 0){
       printf("Desculpe banco de dados não disponível!\n\n");
       exit(1);
    }
    
    int qtdepalavra;
    fscanf(f, "%d", &qtdepalavra);
    
    srand(time(0));
    int randomico = rand() % qtdepalavra;
    
    for(int i=0;i<=randomico;i++){
        fscanf(f, "%s", palavra_secreta);
    } 
    
    fclose(f);
}

int acertou(){
    for(int i=0; i<strlen(palavra_secreta); i++){
        if(!ja_chutou(palavra_secreta[i])){
           return 0;
        }
    }
    return 1;
}

int letraexiste(char letra) {

    for(int j = 0; j < strlen(palavra_secreta); j++) {
        if(letra == palavra_secreta[j]) {
            return 1;
        }
    }

    return 0;
}

int chutes_errados(){
    int erros = 0;
    
    for(int i=0; i<chutes_dados; i++){
        int existe = 0;
        
        for(int j=0;j<strlen(palavra_secreta);j++){
            if(chutes[i] == palavra_secreta[j]){
                existe = 1;
                break;
            }
        }
        if(!existe) erros++;
    }
    return erros;
}

int enforcou(){
    return chutes_errados() >= 5;
}

int main(){
    
    escolhe_palavra();
    inicio();
    
    do{
       desenha_forca();
       chute();

    }while(!acertou() && !enforcou());
   
    if(acertou()){
       printf("\nParabéns, você ganhou!\n\n");
       
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
    }else{
       printf("\nPuxa, você foi enforcado!\n");
       printf("A palavra era **%s**\n\n", palavra_secreta);

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

