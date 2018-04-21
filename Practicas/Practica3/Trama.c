/*########################	TRAMA ANALIZER	#######################
* @author Laura Andrea Morales
* @version 0.1
* @team CompilandoConocimiento
* @date 4/04/2018
* @compile "gcc -std=c11 Trama.c -o Trama"
* @run "./Trama "
*/

#include <stdlib.h>
#include <stdio.h>
#include<stdbool.h>
typedef unsigned int uint;
typedef unsigned char byte;
typedef unsigned short int Twobytes;
typedef unsigned long long int lint;

uint Crc=0;
uint Suma=0;
bool flag=true;
Twobytes Auxiliar=0;
void binprintf(int IP)											//==============PRINT AS BINARY================
{
    unsigned int aux=1<<((sizeof(int)<<3)-1);					//Change the pointer
    while(aux) {												//While aux is true
        printf("%d", (IP&aux ? 1 : 0));							//Print it
        aux >>= 1;												//Move it baby
    }
}
//Usa 4 chars para crear un int metelo en un for del size of the trama
byte CountBits(byte Num){
	byte aux=128;
	byte Number=0;
	for(byte j=0;j<8;j++){
		
			if (Num&(aux>>j))
						Number++;
}
	
	return Number;
}


Twobytes Checksum(byte uno, byte dos){
	Auxiliar=dos|(uno<<8);
	Suma+=Auxiliar;
}

uint  crc8 (byte data[], int size)
{
   int i=1,j=0;
   byte unbyte, temp=0;
   byte crc = data[0];
   byte poly=0x07;
   unbyte=data[0];
   while (i<size)
   {
   		if(unbyte&128){
   			//printf("Es uno: \n");
   			if(j<8){

   				unbyte<<=1;
	   			if(data[i]&128){
		   					unbyte|=1;
		   				}
		   				else{
		   					unbyte|=0;
		   				}
		   				//printf("CRC %#02x\n",unbyte);

	   			data[i]<<=1;
	   			j++;
	   			unbyte=unbyte^=poly;
	   			//printf("1XOR %#02x\n",unbyte);

	   			
   			}
   			else{															//Siguiente bloque de datos
   						
		   				i++;												//Actualizame el dato
   						j=0;												//Resetea
   						if(!(i==size)){										//Si ya no hay datos

		   							unbyte<<=1;
		   							//printf("CRC %#02x\n",unbyte);

				   						if(data[i]&128){
						   					unbyte|=1;
						   					data[i]<<=1;
								   			j++;
								   			unbyte=unbyte^=poly;
				   						}
				   						else if(!(data[i]&128)){
						   					unbyte|=0;
						   					data[i]<<=1;
								   			j++;
						   					unbyte=unbyte^=poly;
						   		}
						   			//printf("XOR %#02x\n",unbyte);

						   	}
						   	

   			}
   		}
   		else {
   			//printf("Es un cero\n");
		   		if(j<8){
		   				unbyte<<=1;
		   				//printf("CRC %#02x\n",unbyte);

		   				if(data[i]&128){
		   					unbyte|=1;
		   				}
		   				else{
		   					unbyte|=0;
		   				}
			   			data[i]<<=1;
			   			j++;
		   				//printf("crc %#02x\n",unbyte);

			   		}
			   	else{
		   				i++;
   						j=0;
   						if(!(i==size)){									//Si ya no hay datos
   							unbyte<<=1;
		   				//printf("CRC %#02x\n",unbyte);
				   				if(data[i]&128){
				   					/*
						   					unbyte|=1;
						   					data[i]<<=1;
								   			j++;
								   			unbyte=unbyte^=poly;
						   				}
						   		else if(!(data[i]&128)){
						   					unbyte|=0;
						   					data[i]<<=1;
								   			j++;
								   			unbyte=unbyte^=poly;
						   				}
		   				printf("xor %#02x\n",unbyte);*/
				   					unbyte|=1;
		   				}
		   				else{
		   					unbyte|=0;
		   				}
			   			data[i]<<=1;
			   			j++;
		   				//printf(" %#02x\n",unbyte);

				   		}
			   		}
   }  
}
   return (uint)unbyte;
}

int main(int argc, char const *argv[])

{	//Checksum 
	//byte T[]={0x83,0x22, 0x45,0x48,0x65,0x6C,0x6C,0x6F,0x21,0xB8,0x48,0x00};
	//Bit pariodad par correcta
	//byte T[]={0x83,0x22, 0x45,0x48,0x65,0x6C,0x6C,0x6F,0x21,0xB1,0x48,0x00};
	//Bit pariodad impar correcta
	//byte T[]={0x83,0x22, 0x45,0x48,0x65,0x6C,0x6C,0x6F,0x21,0xB3,0x48,0x00};
	// Trama de tarea
	//byte T[]={0x03,0x4B, 0x1F,0x4A,0x65,0x73,0x75,0x69,0x20,0xB1,0xA1,0x40};
	//CRC 8
	byte T[]={0x83,0x22, 0x45,0x48,0x65,0x6C,0x6C,0x6F,0x21,0xB4,0x47,0x48,0x00};
	byte Tc[]={0x83,0x22,0x45,0x48,0x65,0x6C,0x6C,0x6F,0x21,0xB4,0x87,0x48,0x00};

	

	byte Languaje[4][4]={"Fre","Ger","Eng","Spa"};
	byte Grupo[3][5]={"2CM8","3CM5","4CV7"};
	byte size=(T[0]&63)*2;
	byte Enrutamiento[4][8]={"Estatic","","Din Dij","Din Bel"};
	byte ControlF[4][4]={"PyE","","ReN","RSe"};

	byte Medio[8][8]={"","WiFi","Infrarr","Bluetoo","Coaxial","ParTren","FibraOp","Telefon"};
	byte Aux=0;
	
	

	//********************	Some Info we wantto know ***************************************
	printf("Languaje: %s\n",Languaje[T[0]>>6] );			//Languaje is in the 2 msb
	printf("Size: %hhu\n",size );						//Size is give by the 6 lsb in 2 bytes 

	printf("\n 			Emisor: \n");
	printf("Grupo: %s\n", Grupo[T[1]>>6]);

	printf("Usuario: %d\n", (T[1]&63));

	printf("\n 			Receptor: \n");
	printf("Grupo: %s\n", Grupo[T[2]>>6]);

	printf("Usuario: %d\n\n", (T[2]&63));

	printf("Mensaje\n");

	for (byte i = 3; i <= 2+size; ++i)
	{
		printf("%c",T[i] );
	}
	printf("Fin Mensaje\n");

	printf("Enrutamiento: %s\n",Enrutamiento[T[size+3]>>6] );
	
	printf("Control de flujo: %s\n",ControlF[(T[size+3]>>4)&0b00000011] );

	//printf("Control de error: %s\n", ControlE[(T[size+3]>>1)&0b00000111] );

	if(((T[size+3]>>1)&0b00000111)==1){
		
		printf("Bit paridad impar\n");

		for (byte i = 0; i <= size+3; ++i)
			Aux=Aux+CountBits(T[i]);
		
		printf("Numero de unos: %d\n\n",Aux );

		if (Aux&1)
			printf("Bien: el número de bits es impar\n");

		else	
			printf("Trama Dañada: el número de bits es par\n");
		
	}
	else if (((T[size+3]>>1)&0b00000111)==0)
	{
		

		printf("\nBit paridad Par\n");
		for (byte i = 0; i <= size+3; ++i)
		{
			Aux=Aux+CountBits(T[i]);
		}
		printf("Numero de unos: %d\n",Aux );
		if (Aux&1)
			printf("Trama Dañada: el número de bits es Impar\n");
		else
			printf("Bien: el número de bits es par\n");

		
	}
	else if(((T[size+3]>>1)&0b00000111)==4){
		printf("Checksum\n");
		for (byte i = 0; i < (size+4); i+=2)
			{
				if ((size+4)<(i+1))
				{
					Checksum(0,T[i]);
				}
				else
				{
					Checksum(T[i],T[i+1]);
				}
			}

		Auxiliar=Suma>>16;
		Suma=Suma&0xFFFF;
		Suma+=Auxiliar;
		printf("%#010x\n\n",(~Suma)&0xFFFF );

	}
	else if(((T[size+3]>>1)&0b00000111)==2){
		printf("CRC 8\n");

		Auxiliar=crc8(&Tc[0],size+4);

		printf("CRC 8 %#02x\n",Auxiliar);
		if(T[size+4]==Auxiliar){
			printf("Trama correcta\n");
			printf("CRC 8 %#02x\n",Auxiliar);
		}
		else
			printf("Trama corrupta\n");

	}
	




	
	return 0;
}
