#include<windows.h>
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

struct cobrinha { //	não é exatamente um objeto....
	int y,x, dx,dy;
};

void gotoxy (int x, int y) { // seta a posição do cursor da linha de comando
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){x, y});
//	system("cls");	// printf("%c[%d;%dH",0x1B,y,x);	
}

int *matrix (int *m, int l, int i, int j) {
	return m + l*i + j; // percorrimento da matriz como um vetor em forma de ponteiro
}

int main()
{
	gotoxy(0,0);
	srand(time(0)); 
	tamanho = (rand()%size) + size;
	vidro[3] = '|';
	vidro[2] = '/';
	vidro[1] = '\\';
	vidro[0] = ' ';
	int cerca = 6*size;
	int cercado[cerca][cerca];
	carrega(cercado,cerca*cerca); // abre do arquivo

	int t, d, c, cobras = 1 + (rand()%tamanho);
	struct cobrinha ofidios[cobras];
	for(c=0; c<cobras; c++) {
		ofidios[c].dy = 0;
		ofidios[c].dx = 0;
		do {			
			ofidios[c].x = (rand()%(cerca-size))+size; 
			ofidios[c].y = (rand()%(cerca-size))+size;
		} while (ir(&ofidios[c].x,&ofidios[c].y,cercado,cerca,&ofidios[c].dx,&ofidios[c].dy) == 0);
		for(t=0; t<tamanho; t++) {	// posiciona o corpo da cobrinha no começo
			while(ir(&ofidios[c].x,&ofidios[c].y,cercado,cerca,&ofidios[c].dx,&ofidios[c].dy) == 0) {	} // se a cobrinha pôde ir a a algum lugar, significa que ela está em algum lugar onde poderia estar.
			cercado[ofidios[c].y][ofidios[c].x] = head - tamanho + t; // o tamanho será o mesmo para todas, se fosse diferente, o processamento do "sumiço" do fim do rastro do rabo teria de ser individualizado de alguma forma
		}
	}
	do { 
		t = time(0);
		d = 0;
		for(c=0; c<cobras; c++)
			if(ir(&ofidios[c].x,&ofidios[c].y,cercado,cerca,&ofidios[c].dx,&ofidios[c].dy) == 1) {
		//	d+=ir(&ofidios[c].x,&ofidios[c].y,cercado,cerca,&ofidios[c].dx,&ofidios[c].dy);
				cercado[ofidios[c].y][ofidios[c].x] = head;
				d += 1;
			}				
		if(d > 0) {
			gotoxy(0,0);
			exibir(cercado, cerca);
			if(d > head)
				d = 0;
		} else if (rand()%tamanho == head) d = head; // se empacar, quanto maior a cobra, menor a chance de ficar esperando parada.
		while(time(0)-t<d && kbhit() == 0) 	  			{		} 									
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
	FILE *obs = fopen("obstaculos.txt","r");
	char f;
	while (t>0) {
		do {
			f = getc(obs);
			printf("%c",f);
		} while (f<32 && f!=EOF);/*(f!='0' && f!='1'); 
*(tela+(--t)) = (f=='0')?(-tamanho):(size*2*(1+(rand()%3)));
	*/	*tela = (f%2==0)?(-tamanho):(size*2*(1+(rand()%3)));
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