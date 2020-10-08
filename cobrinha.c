#include<windows.h>	// necessário para definição da gotoxy
#include<stdlib.h>	
#include <stdio.h>
#include <conio.h>
#include <time.h> 
#define neck 177	//	caractere do pescoço
#define head 1	//	diferença do pescoço para a cabeça
#define size 5	// tamanho mínimo da cobrinha e diferença para o máximo
int tamanho;
char vidro[4];	// caracteres que não são a cobrinha
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
	vidro[0] = ' ';
	int cerca = 6*size;
	int cercado[cerca][cerca];
	carrega(cercado,cerca*cerca); // abre do arquivo
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
	int t, d=1, dy=0,dx=0,x = (rand()%(cerca-size))+size, y = (rand()%(cerca-size))+size;
	while(ir(&x,&y,cercado,cerca,&dx,&dy) == 0) {	} // se a cobrinha pôde ir a a algum lugar, significa que ela está em algum lugar onde poderia estar.
	do { 
		t	= time(0);
		while(time(0)-t<d && kbhit() == 0) 	// essa espera de até 1 segundo pode ser interrompida pelo teclado, 
		{ 	//	if(kbhit()!=0)return 0; 	// assim, caso seja interrompido o programa durante a espera, 
		} 									// ele será terminado (quase) imediatamente
		d = ir(&x,&y,cercado,cerca,&dx,&dy);
		if(d == 1) {
			gotoxy(0,0);
			cercado[y][x] = head;
			exibir(cercado, cerca);
		} else if (rand()%tamanho == head) d = head; // se empacar, quanto maior a cobra, menor a chance de ficar esperando parada.
	} while (kbhit() == 0);
	return 0;
}


int ir (int *a, int *b, int *c, int t, int *da, int *db) {
	if(decidir(da,db,matrix(c,t,*b,*a),t) == 0)
		return 0; 
	(*a) += *da;
	(*b) += *db;
	return 1;
}
int decidir (int *dx, int *dy, int *cob, int cer) {
	for(int c = 0; c < tamanho; c++) { // tenta mais se a cobra for maior
		if(((*dx) != 0 || 0 != (*dy)) && (*matrix(cob,cer,*dy,*dx))<-head && rand()%tamanho>c)
			return 1; // quanto maior a cobra, menos chance há dela mudar de direção sem necessidade
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
	return vidro[0];//32
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