#include<stdio.h>
#include <time.h> 

#define MAX_LIN 12
#define MAX_COL 48
#define GOTA_R 'H'
#define GOTA 'G'

void limpador (char *vidro, char limpo, int area);
void ler (char *superficie, FILE *chuva,int largura);
void ver (char *superficie, int altura, int largura);
int conta(char *superficie, int altura, int largura);

int main () {
	char janela[MAX_LIN][MAX_COL];
	limpador(janela,' ', MAX_COL*MAX_LIN);
	ler(janela, fopen("gotas.txt", "r"), MAX_COL);
	int t = 0, s;
	do {
		s = time(NULL);
		printf("\nPasso T=%d\n",t++);
		ver(janela, MAX_LIN,MAX_COL);
		while(time(NULL) - s < 1) {}
	} while(conta(janela,MAX_LIN,MAX_COL)>0);
	return 0;
}

int conta(char *superficie, int altura, int largura) {
	int c,l, i,	g = 0;
	for(c=0; c<largura; c++)
		for(l=altura-1; l>0; l--) 
			if(*(superficie + c + l*largura) == GOTA_R || *(superficie + c + l*largura) == GOTA) {
				g++;
				i = 1;
				if(*(superficie + c + l*largura) == GOTA_R) i++;
				if(l+i < altura)
					*(superficie + c + (l+i)*largura) = *(superficie + c + l*largura);
				*(superficie + c + l*largura) = ' ';
			}
	return g;
}

void limpador (char *vidro, char limpo, int area) {
	while(area-- > 0)
		*(area + vidro) = limpo;
}

void ler (char *superficie, FILE *chuva, int largura) {
	int c,l;
	do {
		fscanf(chuva,"%d %d",&c,&l);
		if(c>=0 && c<MAX_COL && l<MAX_LIN && l>0)
			*(superficie + c + l*largura) = ((l==1)?(GOTA_R):(GOTA));
		else printf("%d %d ",c,l);
	} while (c!=0 || l!=0);
	fclose(chuva);
}

void ver (char *superficie, int altura, int largura) {
	int i,j;
	for(i=0; i<altura; i++) {
		for(j=0; j<largura; j++) 
			if(*(superficie + j + i*largura) == GOTA_R)
				printf("%c",GOTA);
			else if(*(superficie + j + i*largura) != ' ' || (i>0 && i<altura-1 && j>0 && j<largura-1))
				printf("%c",*(superficie + j + i*largura));
			else if(i == 0)
				printf("-");
			else if(i+1 == altura)
				printf("+");
			else printf("|");//if(j+1 == largura || j == 0)
		printf("\n");
	}
}