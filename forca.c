#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "forca.h"

char palavra_secreta[20];
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

int acertou(){
    for(int i=0; i<strlen(palavra_secreta); i++){
        if(!ja_chutou(palavra_secreta[i])){
           return 0;
        }
    }
    return 1;
}

int enforcou(){
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
    return erros >= 5;
}

int main(){
    
    escolhe_palavra();
    inicio();
    
    do{
       desenha_forca();
       chute();

    }while(!acertou() && !enforcou());
}
