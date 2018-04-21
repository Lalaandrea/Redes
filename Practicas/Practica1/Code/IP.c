#include <stdlib.h>
#include <stdio.h>
#include<stdbool.h>
typedef unsigned int uint;
typedef unsigned char byte;

	byte ArrayIP[4]={0,0,0,0};

/*//*******************************Only for reserch uses****************************************
void binprintf(int IP)											//==============PRINT AS BINARY================
{
    unsigned int aux=1<<((sizeof(int)<<3)-1);					//Change the pointer
    while(aux) {												//While aux is true
        printf("%d", (IP&aux ? 1 : 0));							//Print it
        aux >>= 1;												//Move it baby
    }
}*/
	/*//*******************************Only for reserch uses****************************************
//===============HELLO DARKNESS MY OLD FRIEND=========================================
	//scanf("%hhu.%hhu.%hhu.%hhu", &ArrayIP[0], &ArrayIP[1], &ArrayIP[2], &ArrayIP[3]);	//What is your IP?
	printf("IP\n");												
	ToIPPrint(IP);
	printf("\n");
*///*******************************Only for reserch uses****************************************

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

	printf("IP Calculator v1.0\nPlease give me your IP\n");

	do{
	scanf("%hu.%hu.%hu.%hu", &a, &b, &c, &d);					//Scan my adress
	if(a<=255 && b<=255 && c<=255 && d<=255) {				//If youre pretty
		ArrayIP[0]=a;										//Push into my bytes
		ArrayIP[1]=b;										//Push into my bytes
		ArrayIP[2]=c;										//Push into my bytes
		ArrayIP[3]=d;										//Push into my bytes
		flag=false;											//Let me out
	}
	else printf("Wrong IP, The values are between 0-255 please try again.\n");//Let me know im fool
}while(flag);												

}
void ToIPPrint(uint IP)									//===========Let's print it pretty===============
{
    printf("%d.%d.%d.%d\n", ((IP >> 24) & 0xFF), ((IP >> 16) & 0xFF), ((IP >> 8) & 0xFF), (IP & 0xFF));//Print it        
}


int main(int argc, char **argv)
{

	uint MNC= 0b11111111111111111111111100000000;		//Initialize the mask Class A
	uint MNB= 0b11111111111111110000000000000000;		//Initialize the mask Class B
	uint MNA= 0b11111111000000000000000000000000;		//Initialize the mask Class C

	Scan();												//Scan my IP
	uint IP=CreateIP(ArrayIP);							//Give me my IP

//===========================If youre a Class A=======================================
	if(((IP>>31)&1)==0){
		printf("\nClass A\n");									//Print your class
		printf("Mask\n");										// and your mask
		ToIPPrint(MNA);												


		printf("\nBroadcast: \n");								//Print your boradcast
		ToIPPrint(IP|~(MNA));	

		printf("Network\n");									//Print you Network
		ToIPPrint(IP&MNA);

		printf("Range:\n");										//Print your Range
		ToIPPrint((IP&MNA)+1);
		printf("-\n");
		ToIPPrint((IP|~(MNA))-1);


		printf("\n");
		if (IP==(IP&MNA))printf("Its an IP Network\n");
		else if(IP==(IP|~(MNA))) printf("Its an IP Broadcast\n");
		else printf("Its an IP Host\n");

	}
	else if(((IP>>30) & 1) == 0){
		printf("\nClass B\n");									//Print your class
		printf("Mask\n");										// and your mask
		ToIPPrint(MNB);

		printf("\nBroadcast: \n");								//Print your boradcast
		ToIPPrint((IP|~(MNB)));

		printf("Network\n");									//Print you Network
		ToIPPrint(IP&MNB);

		printf("Range:\n");										//Print your Range
		ToIPPrint((IP&MNB)+1);
		printf("-\n");
		ToIPPrint((IP|~(MNB))-1);


		printf("\n");
		if (IP==(IP&MNB))printf("Its an IP Network\n");
		else if(IP==(IP|~(MNB))) printf("Its an IP Broadcast\n");
		else printf("Its an IP Host\n");

	}
	else if(((IP>>29) & 1) == 0){
		printf("\nClass C\n");									//Print your class
		printf("Mask\n");										// and your mask
		ToIPPrint(MNC);


		printf("\nBroadcast: \n");								//Print your boradcast
		ToIPPrint(IP|~(MNC));

		printf("Network\n");									//Print you Network
		ToIPPrint(IP&MNC);

		printf("Range:\n");										//Print your Range
		ToIPPrint((IP&MNC)+1);
		printf("\n-\n");
		ToIPPrint((IP|~(MNC))-1);


		printf("\n");
		if (IP==(IP&MNC))printf("Its an IP Network\n");
		else if(IP==(IP|~(MNC))) printf("Its an IP Broadcast\n");
		else printf("Is a IP Host\n");

	}
	else if(((IP>>28) & 1) == 0){								//Print your class
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
