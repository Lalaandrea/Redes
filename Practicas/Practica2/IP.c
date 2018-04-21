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
typedef unsigned int uint;
typedef unsigned char byte;

	byte ArrayIP[4]={0,0,0,0};
	byte ArrayMask[4]={0,0,0,0};



//******************************Only for reserch uses****************************************
void binprintf(int IP)											//==============PRINT AS BINARY================
{
    unsigned int aux=1<<((sizeof(int)<<3)-1);					//Change the pointer
    while(aux) {												//While aux is true
        printf("%d", (IP&aux ? 1 : 0));							//Print it
        aux >>= 1;												//Move it baby
    }
}
	/*//*******************************Only for reserch uses****************************************
//===============HELLO DARKNESS MY OLD FRIEND=========================================
	//scanf("%hhu.%hhu.%hhu.%hhu", &ArrayIP[0], &ArrayIP[1], &ArrayIP[2], &ArrayIP[3]);	//What is your IP?
	printf("IP\n");												
	ToIPPrint(IP);
	printf("\n");
*///*******************************Only for reserch uses****************************************

 int POW( byte Exp)					//=========		POWER BASE 2	==========
{
    int Pow = 1;											//Initialize
    for(byte i = 0; i < Exp; i++)							//For the number of the exponent
    {
        Pow *= 2;											//Power
        printf("Pow %d\n",Pow );
        binprintf(Pow);
    }
    return Pow;
}


uint CreateIP(byte ArrayIP[4]) {           	// ====== CREATE AN IP ====							
    uint IPAdress = 0;                                          //Start by cleaning it all**********
    IPAdress |= ArrayIP[0] << (32 - 8);                        //Let`s put a info in 0-7
    IPAdress |= ArrayIP[1] << (32 - 16);                       //Let`s put b info in 8-15
    IPAdress |= ArrayIP[2] << (32 - 24);                       //Let`s put c info in 16-31
    IPAdress |= ArrayIP[3];                                     //The info in d just fit
    
    return IPAdress;                               //Go little butterfly
}

void Scan(){												//Scan my elements
	bool flag=true;											//We will need this
	unsigned short int a = 0 ,b=0,c=0,d=0;

	printf("IP Calculator v1.0\n");

	do{
		printf("Please give me your IP\n\n");
	scanf("%hu.%hu.%hu.%hu", &a, &b, &c, &d);					//Scan my adress
	if(a<=255 && b<=255 && c<=255 && d<=255) {				//If youre pretty
		ArrayIP[0]=a;										//Push into my bytes
		ArrayIP[1]=b;										//Push into my bytes
		ArrayIP[2]=c;										//Push into my bytes
		ArrayIP[3]=d;										//Push into my bytes										//Let me out
	}
	else printf("Wrong IP, The values are between 0-255 please try again.\n");//Let me know im fool
	a=0;
	b=0;
	c=0;
	d=0;
	printf("Please give me your Mask\n");
	scanf("%hu.%hu.%hu.%hu", &a, &b, &c, &d);					//Scan my adress
	//printf("%hu.%hu.%hu.%hu\n",a,b,c,d);
	if(a<=255 && b<=255 && c<=255 && d<=252) {				//If youre pretty
		ArrayMask[0]=a;										//Push into my bytes
		ArrayMask[1]=b;										//Push into my bytes
		ArrayMask[2]=c;										//Push into my bytes
		ArrayMask[3]=d;										//Push into my bytes
		flag=false;											//Let me out
	}
	else printf("Wrong Mask, The values are between 0-255 please try again.\n");//Let me know im fool
	
}while(flag);												

}
void ToIPPrint(uint IP)									//===========Let's print it pretty===============
{
    printf("%d.%d.%d.%d\n", ((IP >> 24) & 0xFF), ((IP >> 16) & 0xFF), ((IP >> 8) & 0xFF), (IP & 0xFF));//Print it        
}

byte CountBits(uint Address){
	bool flag= true;
	uint aux=2147483648;
	byte Number=0;
	byte NumberOfOnes=0;
	
	for(byte j=0;j<32;j++){
		if(flag){
				if (Address&(aux>>j))
				{
						Number++;
					}
					else{
						flag=false;
						NumberOfOnes=Number;
					}}
		else{
			if (Address&(aux>>j))
			{	
				Number++;
			}
		}

}
	if (Number==NumberOfOnes)
	{
		return Number;
		
	}
	else return 0;
}


int main(int argc, char **argv)
{
	Scan();															//Scan my IP									

	uint Mask=CreateIP(ArrayMask);									//Give me my mask
	while(!CountBits(Mask)){										//The mask is OK?
		printf("Mask wrong: Please try again.\n");					//If not the Scan again till OK
		Scan();
		Mask=CreateIP(ArrayMask);
	}
	
												
	uint IP=CreateIP(ArrayIP);										//Give me my IP					

//===========================If youre a Class A=======================================
	if(!(IP&2147483648)){
		printf("\nClass A\n");									//Print your class	

		if(CountBits(Mask)<8){
			printf("Wrong Mask for class A\n");

		}
		else{											

			printf("\nBroadcast: \n");								//Print your boradcast
			ToIPPrint(IP|~(Mask));

			printf("Network\n");									//Print you Network
			ToIPPrint(IP&Mask);

			printf("Range:\n");										//Print your Range
			ToIPPrint((IP&Mask)+1);
			printf("-\n");
			ToIPPrint((IP|~(Mask))-1);

			//**************************SOME INFO WE NEED TO KNOW*****************************
			printf("Sub Network Bits (Borrow bits): %hhu\n",(CountBits(Mask)-8) );	

			printf("Network Bits: 8\n");

			
			printf("Host Bits: %hhu\n",(32-CountBits(Mask)) );

			
			printf("Number of SubNetworks: %d\n",(POW((CountBits(Mask)-8))));

			printf("Number of Host by SubNetwork :%d\n",(POW((32-CountBits(Mask)))-2) );

			printf("\n");
			//**************************TIPE OF IP********************************************
			if (IP==(IP&Mask))printf("Its an IP Network\n");
			else if(IP==(IP|~(Mask))) printf("Its an IP Broadcast\n");
			else printf("Its an IP Host\n");
		}
	}
	else if(!(IP&1073741824)){
		printf("\nClass B\n");									//Print your class
		printf("Mask\n");										// and your mask
		ToIPPrint(Mask);

		if(CountBits(Mask)<16){
			printf("Wrong Mask for class B\n");

		}
		else{											


			printf("\nBroadcast: \n");								//Print your boradcast
			ToIPPrint(IP|~(Mask));	

			printf("Network\n");									//Print you Network
			ToIPPrint(IP&Mask);

			printf("Range:\n");										//Print your Range
			ToIPPrint((IP&Mask)+1);
			printf("-\n");
			ToIPPrint((IP|~(Mask))-1);

			
			printf("Sub Network Bits (Borrow bits): %hhu\n",(CountBits(Mask)-16) );

			printf("Network Bits: 16\n");


			printf("Host Bits: %hhu\n",(32-CountBits(Mask)) );

			printf("Number of SubNetworks: %d\n",(POW((CountBits(Mask)-16))));

			printf("Number of Host by SubNetwork :%d\n",(POW((32-CountBits(Mask)))-2));

			printf("\n");
			if (IP==(IP&Mask))printf("Its an IP Network\n");
			else if(IP==(IP|~(Mask))) printf("Its an IP Broadcast\n");
			else printf("Its an IP Host\n");
		}

	}
	else if(!(IP&536870912)){
		printf("\nClass C\n");									//Print your class
		printf("Mask\n");										// and your mask
		ToIPPrint(Mask);



		if(CountBits(Mask)<24){
			printf("Wrong Mask for class C\n");

		}
		else{											


			printf("\nBroadcast: \n");								//Print your broadcast
			ToIPPrint(IP|~(Mask));	

			printf("Network\n");									//Print you Network
			ToIPPrint(IP&Mask);

			printf("Range:\n");										//Print your Range
			ToIPPrint((IP&Mask)+1);
			printf("-\n");
			ToIPPrint((IP|~(Mask))-1);

			
			printf("Sub Network Bits (Borrow bits): %hhu\n",(CountBits(Mask)-24) );

			printf("Network Bits: 24\n");


			printf("Host Bits: %hhu\n",(32-CountBits(Mask)) );

			printf("Number of SubNetworks: %d\n",(POW((CountBits(Mask)-24))));

			printf("Number of Host by SubNetwork :%d\n",(POW((32-CountBits(Mask)))-2) );



			printf("\n");
			if (IP==(IP&Mask))printf("Its an IP Network\n");
			else if(IP==(IP|~(Mask))) printf("Its an IP Broadcast\n");
			else printf("Its an IP Host\n");
		}
	}
	else if(!(IP&268435456)){								//Print your class
		printf("Class D\n");
		printf("Multicast\n");									//Tell me about it
		printf("The range its from 224.0.0.0 to 239.255.255.255 \n it is reservated for multicast.\n");


	}
	else{
		printf("Class E\n");									//Print your class
		printf("Reserch and development\n");					//Tel me about it
		printf("This IP class is reservated for experimentation\nonly for R&D or study. The IP adress for this class\nits from 240.0.0.0 to 255.255.255.254\n");


	}
	
	
}
