#ifndef CLIENT
#define CLIENT

#include "SocketUtility.h"
#include "SystemUtility.h"
#include <stdexcept>
#include <iostream>
#include <sstream>
/*
class Client{

public:
	template<typename T>
	void sendObject(SOCKET sock,const T& object);

	void sendObject(SOCKET sock, MesgHeaderFactory::MesgHeader ss);
};

void Client::sendObject(SOCKET sock, MesgHeaderFactory::MesgHeader ss){
	int retry=1;
	int retryCount=-1;
	while(retry){
		retryCount++;
		try{
			sendData(sock,ss);
			retry=0;
		}catch(std::exception exp ){
			std::cout<<exp.what()<<endl;

			retry=(GetUserInput<int>()("Failed:  Send object again ? \n type 1 to retry other to cancel:") );
			if(retryCount==5)
				cout<<"Sending action failed too many times, EXIT PROGRAM!"<<endl;
		}		
	}
	//Auto get ACK and printout error or success
	string ack;
	try{
		receiveData(sock,ack);

		DE_PRINT("Sending Data Success");

	}catch(std::exception exp){
		DE_PRINT("Sending Data Fail");
	}
}

template<typename T>
void Client::sendObject(SOCKET sock,const T& object)
{

	int retry=1;
	int retryCount=-1;
	while(retry){
		retryCount++;
		try{
			sendData(sock,object);
			retry=0;
		}catch(std::exception exp ){
			std::cout<<exp.what()<<endl;

			cout<<"Send Data again ? \n type again to retry other to cancel:"<<endl<<endl;
			string again;
			cin>>again;
			assert(0);
			if(retryCount==5)
				cout<<"too many fail EXIT PROGRAM!"<<endl;
		}		
	}
	DE_PRINT("Sending Data Wait ACK");
	//Auto get ACK
	string ack;
	try{
		receiveData(sock,ack);

		DE_PRINT("Sending Data Success");
	}catch(std::exception exp){

	}
}
*/

#endif
