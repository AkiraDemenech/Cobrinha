#include<windows.h> 
#include<stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h> 
#define neck 177
#define head 1
#define size 5
int tamanho;
char vidro[4];
char mostra (int casa);
void carrega (int *tela, int t);
void exibir (int *tela, int t);
int decidir (int *dx, int *dy, int *cob, int cer);
int ir (int *a, int *b, int *c, int t, int *da, int *db);
void gotoxy (int x, int y);
int *matrix (int *m, int l, int i, int j);

int main()
{
	srand(time(0)); 
	tamanho = (rand()%size) + size;
	vidro[3] = '|';
	vidro[2] = '/';
	vidro[1] = '\\';
	int cerca = 6*size;
	int cercado[cerca][cerca];
	carrega(cercado,cerca*cerca);
/*	for(int c=0; c<cerca; c++) {
		printf("\n");
		for(int b=0; b<cerca; b++)
			printf("%c",mostra(cercado[c][b]));
	} 
	printf("%d",tamanho); */
//	printf("%d\t%c\n%d\t%c\n%d\t%c\n",176,176,177,177,178,178);
//	for(int c=10; c>-10; c--)
//		printf("\n%c\t%d\t%d%d",mostra(c),mostra(c),c,tamanho);
	gotoxy(0,0);
	int t, dy=0,dx=0,x = (rand()%(cerca-size))+size, y = (rand()%(cerca-size))+size;
	while(ir(&x,&y,cercado,cerca,&dx,&dy) == 0) {	} // se a cobrinha pôde ir a a algum lugar, significa que ela está em algum lugar onde poderia estar.
	do { 
		t	= time(0);
		while(time(0)-t<1 && kbhit() == 0) 	// essa espera de até 1 segundo pode ser interrompida pelo teclado, 
		{ 	//	if(kbhit()!=0)return 0; 	// assim, caso seja interrompido o programa durante a espera, 
		} 									// ele será terminado (quase) imediatamente
		if(ir(&x,&y,cercado,cerca,&dx,&dy) == 1) {
			gotoxy(0,0);
			cercado[y][x] = head;
			exibir(cercado, cerca);
		}
	} while (kbhit() == 0);
	return 0;
}


int ir (int *a, int *b, int *c, int t, int *da, int *db) {
	int r = decidir(da,db,matrix(c,t,*a,*b),t);
	if(r == 0 || (da == 0 && db == 0))
		return 0;
	(*a) += *da;
	(*b) += *db;
	return 1;
}
int decidir (int *dx, int *dy, int *cob, int cer) {
	for(int c = 0; c < tamanho; c++) {
		if((0 != (*dx) || 0 != (*dy)) && (*matrix(cob,cer,*dx,*dy))%(2*size)!=0)
			return 1;
		(*dx) = (rand()%3) - 1;
		(*dy) = (rand()%3) - 1;
	}
	return 0;
}

char mostra (int casa) {
	if(casa>tamanho)
		return vidro[casa/(size+size)]; //casa/10
	if(casa+tamanho>head)
		return (char)(neck+((casa==head)?(head):(casa%2)));
	return ' ';//32
}
void carrega (int *tela, int t) {
	gotoxy(0,0);
	FILE *obs = fopen("obstaculos.txt","r");
	char f;
	while (t>0) {
		do {
			f = getc(obs);
			printf("%c",f);
		} while (f!='0' && f!='1'); /*
*(tela+(--t)) = (f=='0')?(-tamanho):(size*2*(1+(rand()%3)));
	*/	*tela = (f=='0')?(-tamanho):(size*2*(1+(rand()%3)));
		tela++;
		t--;
	}
}
void exibir (int *tela, int t) {
	for(int c,l=0; l<t; l++) {
		for(c=0; c<t; c++) {
			printf("%c",mostra(*tela));
			if ((*tela)<=head && (*tela)>-tamanho)
				(*tela)--;
			tela++;
		}
		printf("\n");
	}
}
void gotoxy (int x, int y) {
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){x, y});
}
int *matrix (int *m, int l, int i, int j) {
	return m + l*i + j;
}

/*
Faça um programa para controlar um objeto denominado “cobrinha”,
sua função é realizar movimentos em qualquer direção 
(a frente, a cima, a baixo e nas diagonais, nunca retornando), 
sendo que a decisão de direção é tomada pela cabeça da cobrinha 
(de forma aleatória) e o restante do corpo deve passar pelos mesmos pontos.

Para compor o corpo da cobrinha use caracteres da tabela ASCII 178, 177 e 176; a cobrinha 
não deve deixar rastro (ou seja, o último caractere deve ser “branco”),
considere o corpo da cobrinha com comprimente entre 5 e 10 caracteres (defina o tamanho).

A cobrinha deve estar aprisionada em um "cercado" de 30 linhas e 30 colunas,
considere as laterais (extremidades do cercado) como sendo um vidro, ou seja,
estando frente a extremidade a cobrinha deve escolher uma outra rota, pois não pode atravessar o vidro.

Inserir atraso entre cada passo da cobrinha.

Existem obstáculos no interior do cercado que serão fornecidos através de um arquivo texto (veja arquivo exemplo).
A cobrinha não pode passar através dos obstáculos.
Como exemplo de obstáculo: uma barra, um quadrado, uma coluna, etc.

** os elementos presentes no cercado (obstáculos) serão inseridos em um arquivo texto (matriz 30x30) com "0" representando espaço livre e "1" representando obstáculo.

O programa deve ser encerrado ao ser teclado qualquer tecla.
*/