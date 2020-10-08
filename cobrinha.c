
#include<stdlib.h>
#include <stdio.h>
#include <time.h> 
#define neck 177
#define head 1
#define size 5
int tamanho;
char vidro[4];
char mostra (int casa);
void carrega (int *tela, int t);

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