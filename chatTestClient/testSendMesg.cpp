
#include "SocketUtility.h"
#include "SystemUtility.h"
#include "process.h"
#include <iostream>
#include <string>

using namespace std;
int main(int argc , char** argv ){
	
	if( argc == 3 )
		cout<<argv[1]<<' '<<argv[2]<<endl;
	else{
		cerr<<"arg1= ip , arg2=port\n";
		exit(1);
	}
	
	WSADATA	wsadata; 
	
	if (WSAStartup(WSVERS, &wsadata) != 0)
		errexit("WSAStartup failed\n");

	
	SOCKET serverSocket =SocketFactory::creatTCPSocket( argv[1], argv[2]);
	cout<<"start chat testing client. \n press Ctrl+c  to exit program\n";

 
	
	while(1){
		string inputMesg = GetUserInput<string>()("Pls type mesg:");
	
		try{
			//send header
			sendData(serverSocket, MesgHeaderFactory::create_NewMesg_Header() );			
			//send mesg
			sendData(serverSocket, inputMesg);
			
			cout<<"a mesg sent."<<endl;
		}catch(std::exception exp ){
			std::cout<<exp.what()<<endl;
		}		
	}
		WSACleanup();
}