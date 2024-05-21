#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void inicio(){
    printf("---------------\n");
    printf(" Jogo de Forca \n");
    printf("---------------\n\n");
}

void chute(char chutes[26],int* tentativas){ 
    char palpite;
    scanf(" %c", &palpite);
       
    chutes[*tentativas] = palpite;
    (*tentativas)++;
}

int ja_chutou(char letra, char chutes[26], int tentativas){
    int achou = 0;
           
    for(int j=0;j<tentativas;j++){
       if(chutes[j] == letra){
          achou = 1;
          break;
       }
    }
    
    return achou;
}

int main(){
    inicio();
    
    char palavra_secreta[20];
		
    sprintf(palavra_secreta, "MELANCIA");
		
    int acertou = 0;
    int enforcou = 0;
    
    char chutes[26];
    int tentativas = 0;
    
    do{
       for(int i=0;i<strlen(palavra_secreta); i++){
           int achou = ja_chutou(palavra_secreta[i], chutes, tentativas);
           
           if(achou){
               printf("%c ",palavra_secreta[i]);
           }else{
               printf("_ ");
       	   }
       }
       printf("\n");
       
       chute(chutes, &tentativas);
       
     
    }while(!acertou && !enforcou);
}
