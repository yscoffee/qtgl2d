
#include "SocketUtility.h"
#include "SystemUtility.h"
#include "process.h"
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept> 
using namespace std;

#define STKSIZE 16536
void newFlood(){
	vector<string> plist;
	vector<string> riplist;
	char str[10]={0};
	for(int ix=79 ; ix<40000 ; ix++){
		memset(&str,0,sizeof(str));
		sprintf(str,"%d",(int)rand()%400000);
		plist.push_back(str); 
	}
		
	/*
	for(int ix=79 ; ix<4 ; ix++){
		memset(&str,0,sizeof(str));
		sprintf(str,"192.168.10.%d",ix);
		riplist.push_back(str); 
	}
	*/
	riplist.push_back("192.168.10.1"); 
	while(1){
		//string inputMesg = GetUserInput<string>()("Pls type mesg:");
		
		for( int iy=0; iy< riplist.size() ; iy++){
			for( int ix=0; ix< plist.size() ; ix++){
				SOCKET serverSocket =SocketFactory::creatTCPSocket( riplist[iy], plist[ix] );
				cout<<riplist[iy]<<' '<<plist[ix].c_str()<<std::endl;
				//cout<<"start chat testing client. \n press Ctrl+c  to exit program\n";

				try{
					//send header
					sendData(serverSocket, MesgHeaderFactory::create_NewMesg_Header() );			
					//send mesg
					//sendData(serverSocket, inputMesg);
					
					//cout<<"a mesg sent."<<endl;
				}catch(std::exception exp ){
					//std::cout<<exp.what()<<endl;
				}catch(...){
				
				}
			}
		}
	}

}
int main(int argc , char** argv ){
	
	 
	
	WSADATA	wsadata; 
	
	if (WSAStartup(WSVERS, &wsadata) != 0)
		errexit("WSAStartup failed\n");

	
	for(int ix=0 ; ix< 10 ; ix++);
	if (_beginthread((void (*)(void *))newFlood, STKSIZE,(void *)NULL) < 0) {
					errexit("_beginthread: %s\n", strerror(errno));
	}
	cout<<"establish slave"<<endl;
	
	newFlood();
	
	WSACleanup();
}