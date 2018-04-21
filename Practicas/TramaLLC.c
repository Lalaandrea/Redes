/*########################	TRAMA ANALIZER	#######################
* @author Laura Andrea Morales
* @version 0.1
* @team CompilandoConocimiento
* @date 4/03/2018
* @compile "gcc -std=c11 IP.c -o IP"
* @run "./IP "
*/
#include <stdlib.h>
#include <stdio.h>
#include<stdbool.h>
#include <string.h>
#define C1 16
#define C2 17
typedef unsigned int uint;
typedef unsigned char byte;
typedef unsigned int sint;

	char Supervision[4][5]={"RR","RNR","REJ","SREJ"};
	char UnumerC[8][7]={"UI","SIM","","SARM","UP","","","SABM"};
	char UnumerR[8][7]={"UI","RIM","","DM","","","",""};


char resultado[100]={};

bool Analizer(byte T[],sint ToT){
	if(ToT<1500){
		printf("%d\n",T[C1]&3 );
		switch(T[C1]&3){
			case 0:
			printf("Entre a caso 0\n");
			sprintf(resultado+strlen(resultado),"T-I N(s):%d,N(r)%d ",T[C1]>>1,T[C2]>>1);
			break;

			case 1:
			printf("Entre a caso Trama de Supervisión\n");
			printf("%d\n",(T[C1]>>2)&3 );

					sprintf(resultado+strlen(resultado),"T-S %s ",Supervision[(T[C1]>>2)&3]);
			break;

			case 2:
			printf("Entre a caso 0\n");
			sprintf(resultado+strlen(resultado),"T-I N(s):%d,N(r)%d ",T[C1]>>1,T[C2]>>1);
			break;

			case 3:
			printf("Entre caso 3 Unnummered\n");
			if ((T[C2]&1))
			{
				printf("Checa Sap\n");
				if (T[15]&1)
				{
					printf("Respuesta\n");
					sprintf(resultado+strlen(resultado),"T-U %s ",UnumerR[((T[C1]>>2)&3)|((T[C1]>>3)&28)]);
				}
				else if (!(T[15]&1))
				{
					printf("Comando\n");
					sprintf(resultado+strlen(resultado),"T-U %s ",UnumerC[((T[C1]>>2)&3)|((T[C1]>>3)&28)]);
				}
				
			}
			
		

			break;



		}
	}
	else return 0;
}

int main(int argc, char const *argv[])
{
	
	byte T[2][19]={{0x00,0x02,0xb3,0x9c,0xae,0xba,0x00,0x02,0xb3,0x9c,0xdf,0x1b,0x00,0x04,0xf0,0xf1,0x01,0x06},{0x00,0x02,0xb3,0x9c,0xae,0xba,0x00,0x02,0xb3,0x9c,0xdf,0x1b,0x00,0x04,0xf0,0xf1,0x01,0x06}};


	for (int i = 0; i < 2; ++i)
	{
		sint ToT=0;

		ToT=(ToT<<8)|T[i][12];
		
		printf("%#02x\n",ToT );
		ToT|=T[i][13];
		printf("%d\n",ToT );

		Analizer(&T[i][0],ToT);

	}

	


	printf("%s\n",resultado);
	
	return 0;
}
