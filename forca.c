#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char palavra_secreta[20];
char chutes[26];
int tentativas = 0;

void inicio(){
    printf("---------------\n");
    printf(" Jogo de Forca \n");
    printf("---------------\n\n");
}

void chute(){ 
    char palpite;
    printf("Qual letra? ");
    scanf(" %c", &palpite);
       
    chutes[tentativas] = palpite;
    tentativas++;
}

int ja_chutou(char letra){
    int achou = 0;
           
    for(int j=0;j<tentativas;j++){
       if(chutes[j] == letra){
          achou = 1;
          break;
       }
    }
    
    return achou;
}

void desenha_forca(){
    for(int i=0;i<strlen(palavra_secreta); i++){
        if(ja_chutou(palavra_secreta[i])){
           printf("%c ",palavra_secreta[i]);
        }else{
           printf("_ ");
    	}
    }
    printf("\n");
}

void escolhe_palavra(){
    sprintf(palavra_secreta, "MELANCIA");
}

int main(){
    int acertou = 0;
    int enforcou = 0;
    
    escolhe_palavra();
    inicio();
    
    do{
       desenha_forca();
       chute();

    }while(!acertou && !enforcou);
}
