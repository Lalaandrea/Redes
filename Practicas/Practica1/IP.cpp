#include <iostream>       
#include <bitset>         
#include <array>         
#include <stdio.h>         

typedef unsigned int uint;
typedef unsigned char byte;

using namespace std;
//Complie as g++ IP.cpp -std=c++11


//*******************************Only for reserch uses***************************

/*
    do{
    scanf("%hhu.%hhu.%hhu.%hhu", &Data[0], &Data[1], &Data[2], &Data[3]);
    if(Data[0]<=255 && Data[1]<=255 && Data[2]<=255 &&Data[3]<=255) flag=false;
    else printf("Wrong IP, The values are between 0-255 please try again.\n");//Let me know im fool

    }while(flag);
*/



std::array<byte, 4> Data;

bitset<32> CreateIP(byte a, byte b, byte c, byte d) {           // ====== CREATE AN IP ====
    uint IPAdress = 0;                                          //Start by cleaning it all
    IPAdress |= a << (32 - 8);                                  //Let`s put a info in 0-7
    IPAdress |= b << (32 - 16);                                 //Let`s put b info in 8-15
    IPAdress |= c << (32 - 24);                                 //Let`s put c info in 16-31
    IPAdress |= d;                                              //The info in d just fit
    
    return bitset<32>(IPAdress);                                //Go little butterfly
}


uint ToInt(bitset<32> IPint){return (uint)(IPint.to_ulong());}	//======= CONVERTO TO INT =======


bitset<32> CreateIP(array<byte, 4> Data) {                      // ====== CREATE AN IP ====
    return CreateIP(Data[0], Data[1], Data[2], Data[3]);        //Return the cool part
}

char GetClass(bitset<32> IP) {                                  // ===== GET IP CLASS ===
    if (IP[31] == 0) return 'A';                                //If start in 0 return a
    else if (IP[30] == 0) return 'B';                           //If start in 10 return b
    else if (IP[29] == 0) return 'C';                           //If start in 110 return c
    else if (IP[28] == 0) return 'D';                           //If start in 1110 return d
    else return 'E';                                            //Else you are just weird
}

string CreateStringView(bitset<32> IP, bool Decimal = true) {   // ===== CREATE STRING VIEW ===

    string Data;                                                //Return data
    for (byte i = 0; i < 4; ++i) {                               //For each block of 8 bits

        bitset<8> Block;                                        //Create a new one
        for (byte j = 0; j < 8; ++j) Block[j] = IP[(8*i) + j];   //Copy the corresponding bits

        auto Temporal = Decimal?                                //We want decimal notation
            to_string(Block.to_ulong()) :                       //Then show me the string in _10
            Block.to_string();                                  //Else show me the string in _2

        Data.insert(0, (i != 0)? Temporal + "." : Temporal);    //If not end insert + "."
    }

    return Data;                                                //Send the string
}

bitset<32> CreateNetwork(bitset<32>IP, bitset<32>MR){			//========= CLACULATE NETWORK ========
	bitset<32> Network;
	for(byte i=0; i<32;i++) Network[i]=IP[i]&MR[i];								
return Network;
}

bitset<32> CreateBroadcast(bitset<32>IP, bitset<32>MR){
	bitset<32> Broadcast;
	for(byte i=0; i<32;i++){
		Broadcast[i]=IP[i]|~MR[i];		//========= CLACULATE BROADCAST ========
}
return Broadcast;
}

bitset<32> CreateRangeA(bitset<32> Network){					//========= CLACULATE RANGE ========
	return bitset<32>(ToInt(Network)+1);  									//Return as bitset
}
bitset<32> CreateRangeB(bitset<32> Broadcast){					//========= CLACULATE RANGE ========
	return bitset<32>(ToInt(Broadcast)-1);   									//Return as bitset 
}

void Scan(){												//Scan my elements
	bool flag=true;											//We will need this for compare
	uint a,b,c,d;
	printf("IP Calculator v1.0\nPlease give me your IP\n");

	do{
	scanf("%u.%u.%u.%u", &a, &b, &c, &d);					//Scan my adress
	if(a<=255 && b<=255 && c<=255 && d<=255) {				//If youre pretty
		Data[0]=a;										//Push into my bytes
		Data[1]=b;										//Push into my bytes
		Data[2]=c;										//Push into my bytes
		Data[3]=d;										//Push into my bytes
		flag=false;											//Let me out
	}
	else printf("Wrong IP, The values are between 0-255 please try again.\n");//Let me know im fool
}while(flag);												

}

int main () {

	//bool flag=true;
	Scan();

    bitset<32> MNA(0b11111111000000000000000000000000);			//Define my Mask a
    bitset<32> MNB(0b11111111111111110000000000000000);			//Define my Mask b
    bitset<32> MNC(0b11111111111111111111111100000000);			//Define my Mask c

    auto IP = CreateIP(Data);									//Create my Ip from the data
    printf("Class: %c\n", GetClass(IP));						//Show me my class


	if(GetClass(IP)=='A'){										//If youre a A class
		cout << "Network"<<endl;
		cout << CreateStringView(CreateNetwork(IP,MNA))<<endl;
		
		cout << "Broadcast"<<endl;
		cout << CreateStringView(CreateBroadcast(IP,MNA))<<endl;

		cout << "Range" <<endl;
		
		cout << CreateStringView(CreateRangeA(CreateNetwork(IP,MNA)))<<endl;
		cout << "-"<<endl;
		cout << CreateStringView(CreateRangeB(CreateBroadcast(IP,MNA)))<<endl;
		
		
	}
	else if(GetClass(IP)=='B'){
		cout << "Network"<<endl;
		cout << CreateStringView(CreateNetwork(IP,MNB))<<endl;
		
		cout << "Broadcast"<<endl;
		cout << CreateStringView(CreateBroadcast(IP,MNB))<<endl;

		cout << "Range" <<endl;
		
		cout << CreateStringView(CreateRangeA(CreateNetwork(IP,MNB)))<<endl;
		cout << "-"<<endl;
		cout << CreateStringView(CreateRangeB(CreateBroadcast(IP,MNB)))<<endl;
	}
	else if(GetClass(IP)=='C'){

		cout << "Network"<<endl;
		cout << CreateStringView(CreateNetwork(IP,MNC))<<endl;
		
		cout << "Broadcast"<<endl;
		cout << CreateStringView(CreateBroadcast(IP,MNC))<<endl;

		cout << "Range" <<endl;
		
		cout << CreateStringView(CreateRangeA(CreateNetwork(IP,MNC)))<<endl;
		cout << "-"<<endl;
		cout << CreateStringView(CreateRangeB(CreateBroadcast(IP,MNC)))<<endl;
	}
	else if(GetClass(IP)=='D'){
		cout<< ""<<endl;
	}
	else if(GetClass(IP)=='E'){
		cout<< ""<<endl;
	}

	
	

    

  return 0;
}
