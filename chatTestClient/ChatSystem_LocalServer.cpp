
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <stdexcept>
#include "process.h"

#include "Client.h"
#include "SystemUtility.h"

using namespace std;
#define STKSIZE 16536
//reply a self-defined ACK string( const char *)
//it's used to let application check the content of pkt
//it's NOT the ack pkt of tcp/ip layer, it is a self-defined string( const char* ).
void replayACK( SOCKET cliSocket ) 
{
	//reply ACK
	try{
		sendData(cliSocket,"data received :ACK");
	}catch(std::exception exp ){
		std::cout<<exp.what()<<endl;
	}		
}

//auto call replyAck function after successful received pkt.
// Note that receiveData may throw exceptions When it encounters errors.
template<typename T>
void RecvDataAndReACK( SOCKET cliSocket, T & stroge ) 
{
	receiveData(cliSocket,stroge);
	replayACK(cliSocket);
}

//just recv and print new mesg to the console.
void getAndPrintNewMesg( SOCKET cliSocket ){

	string  newMesg;
	
	RecvDataAndReACK(cliSocket,newMesg);

	static int mesgCount=0;
	mesgCount++;
	cout<<mesgCount<<"-th "
			<<"recved new mesg:\n\t  "<<newMesg<<endl;
}

// IF RECEIVED A SOCKET CONNECTION
void newConnectHandle( SOCKET cliSocket )
{
	while(1){
	
		try{
			// receiving Data Header
			MesgHeaderFactory::MesgHeader newInputHeader=MesgHeaderFactory::MH_Ini;

			//auto reply ack
			RecvDataAndReACK(cliSocket, newInputHeader);

			switch(newInputHeader){

				case MesgHeaderFactory::MH_NewMesg:

					//auto reply ack

					getAndPrintNewMesg(cliSocket);
					break;
				case MesgHeaderFactory::MH_Ini :
					break;

				case MesgHeaderFactory::MH_EXIT :
					break;
				default:
					cerr<<"ERROR undefined header type. ";
					assert(0);
					break;
			};
		
		}catch(...){
			break;
		}
		
	}//while
	cout<<"A client socket has disconnected."<<endl;
	closesocket(cliSocket);
}

int TCPechod(SOCKET);
void errexit(const char *, ...);

void StartListenServer(string port)
{
	WSADATA	wsadata;
	if (WSAStartup(WSVERS, &wsadata) != 0)
		errexit("WSAStartup failed\n");

	std::cout<<" Chat Server start at port:"<<port<<std::endl;

	SOCKET	msock, ssock;
	msock = passivesock(port.c_str(),"tcp", QLEN);
	struct	sockaddr_in fsin;
	//--------------------------------------------------------------------------
	// accept socket infinite loops
	//--------------------------------------------------------------------------
	while (true){
		int alen = sizeof(fsin);
		ssock = accept(msock, (struct sockaddr *)&fsin, &alen);

		if (ssock == INVALID_SOCKET)
			errexit("accept: error SOCKET number\n", GetLastError());

		try{
			//Iterative Server
			//newConnectHandle(ssock);
			
			if (_beginthread((void (*)(void *))newConnectHandle, STKSIZE,(void *)ssock) < 0) {
					errexit("_beginthread: %s\n", strerror(errno));
			}
			cout<<"establish slave server. continue to listen "<<endl;
			
		}catch(std::domain_error soExc){
			cerr<<soExc.what()<<" error code:"<<GetLastError()<<endl;
		}catch(std::runtime_error rvExc){
			cerr<<rvExc.what()<<" error code:"<<GetLastError()<<endl;		
			errexit("socket recv failed: %d\n",GetLastError());
		}catch(...){
			//cerr<<exc<<endl;
		}
	}

	DE_PRINT("Server TERMINATE!!!!!!!");
	WSACleanup();
}

int main(void){

	
	StartListenServer("3333");
	
	
}