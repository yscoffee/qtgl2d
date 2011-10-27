#ifndef SOCKETUTILITY
#define SOCKETUTILITY
#pragma   comment(lib,   "Ws2_32.lib")   
#include<string>
#include<iostream>
#include<sstream>
#include<winsock.h>
#include<stdexcept> 
#include <stdarg.h>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include "SpecializeType.h"


using std::runtime_error;
using std::fstream;
using std::ofstream;
using std::ifstream;
using std::string;
using std::endl;
using std::cin;
using std::cout;
using std::cerr;
using std::pair;
using std::stringstream;
//========= Macros =============================================================
#define	QLEN		100	/* maximum connection queue length	*/
#define	BUFSIZE		4096
#define	LINELEN	    4096
#define	WSVERS		MAKEWORD(2, 0)

#ifndef	INADDR_NONE
#define	INADDR_NONE	0xffffffff
#endif	/* INADDR_NONE */
//==============================================================================
SOCKET passivesock(const char *service, const char *transport, int qlen);
SOCKET connectsock(const char *host, const char *service, const char *transport );


// the Socket factory class 
// this class responsibles for produce socket to an IP, Port
//-----------------------------------------------------------------------------
class SocketFactory{

public:

	static SOCKET creatTCPSocket(const string IP,const string Port){
		return connectsock( IP.c_str(), Port.c_str(), "tcp");
	}

};

// Message Header Factory class 
// this class responsibles for produce message header 
//-----------------------------------------------------------------------------
class MesgHeaderFactory{

public:
	 //static
     enum MesgHeader{ 
		MH_NewMesg=1,
		MH_Ini,
		MH_EXIT
	};
	 static MesgHeader create_NewMesg_Header(){
		return MH_NewMesg;
	}
 
	static MesgHeader create_Ini_Header(){
		return MH_Ini;
	}
	static MesgHeader create_EXIT_Header(){
		return MH_EXIT;
	}
};


std::ostream& operator<< (std::ostream & ostr ,MesgHeaderFactory::MesgHeader &msh ){
	ostr<<static_cast<int>(msh);
	return ostr;
}

std::istream& operator>> (std::istream & istr, MesgHeaderFactory::MesgHeader &msh ){
	int input=0;
	istr>>input;
	msh=static_cast<MesgHeaderFactory::MesgHeader>(input);

	return istr;
}


void errexit(const char *format, ...)
{
	va_list	args;

	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);
	WSACleanup();
	exit(1);
}


//======== template send & receive template function ====================================
/*
 * @ throws SendSockError
 */
template<typename T>
void sendData( SOCKET sockFd, T data )
{
	//transfer T data
	stringstream sstr;
	sstr<<data;

	int result = send(sockFd, sstr.str().c_str() , sstr.str().size()+1 , 0);

	if(   result ==  SOCKET_ERROR ){
		throw runtime_error("sendData ERROR");
	}else
		return;
}
template<typename T>
void sendData( SOCKET sockFd, T* dataPtr )
{
	//transfer T data
	stringstream sstr;
	sstr<<(*dataPtr);

	int result = send(sockFd, sstr.str().c_str() , sstr.str().size()+1 , 0);

	if(   result ==  SOCKET_ERROR ){
		throw runtime_error("sendData ERROR");
	}else
		return;
}
/*
 * @ throws RecvSockError
 */
template<typename T>
void receiveData(SOCKET socket ,T &storage)
{

	char	buf[LINELEN+1]={0};		/* buffer for one line of text	*/
	int	recvCount=0;	/* characters counts		*/

	recvCount = recv(socket, buf, LINELEN, 0);
	if (recvCount == SOCKET_ERROR)
		throw runtime_error("recv fail");

	//	string receiveStr(buf,recvCount);
	string receiveStr(buf);
	stringstream strIn(receiveStr);
	
	strIn>> storage;

	return;
}
//==============================================================================
//		 template specialization 
//FULL specialization for const char*
//---------------------------------------------------------------------------
template<>
void sendData(SOCKET sockFd,const char* c_mesg )
{
	int result = send(sockFd, c_mesg , strlen(c_mesg) , 0);

	if(   result ==  SOCKET_ERROR )
		throw runtime_error("send fail");
	else
		return;
}
//FULL specialization for char*
//---------------------------------------------------------------------------
template<>
void sendData(SOCKET sockFd,char* mesg )
{
	sendData<const char*>(sockFd,mesg);
}
//FULL specialization for string
//---------------------------------------------------------------------------
template<>
void sendData(SOCKET sockFd,string mesg )
{
	int result = send(sockFd, mesg.c_str() , mesg.size()+1 , 0);

	if(   result ==  SOCKET_ERROR )
		throw runtime_error("send fail");
	else
		return;
}

//FULL Specialization for string version
//---------------------------------------------------------------------------
template<>
void receiveData(SOCKET socket ,string &storage)
{

	char	buf[LINELEN+1]={0};		/* buffer for one line of text	*/
	int	recvCount=0;	/* characters counts		*/

	recvCount = recv(socket, buf, LINELEN, 0);
	if (recvCount == SOCKET_ERROR)
		throw runtime_error("recv fail");
	//	string receiveStr(buf,recvCount);
	storage = string(buf);
	return ;
}

SOCKET passivesock(const char *service, const char *transport, int qlen)
{
	struct servent	*pse;	/* pointer to service information entry	*/
	struct protoent *ppe;	/* pointer to protocol information entry*/
	struct sockaddr_in sin;	/* an Internet endpoint address		*/
	SOCKET		s;	/* socket descriptor			*/
	int		type;	/* socket type (SOCK_STREAM, SOCK_DGRAM)*/

	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;

	/* Map service name to port number */
	if ( pse = getservbyname(service, transport) )
		sin.sin_port = htons(ntohs((u_short)pse->s_port)+0);
	else if ( (sin.sin_port = htons((u_short)atoi(service))) == 0 )
		errexit("can't get \"%s\" service entry\n", service);

	/* Map protocol name to protocol number */
	(ppe = getprotobyname(transport)) ;
	if ( ppe == 0)
		errexit("can't get \"%s\" protocol entry\n", transport);

	/* Use protocol to choose a socket type */
	if (strcmp(transport, "udp") == 0)
		type = SOCK_DGRAM;
	else
		type = SOCK_STREAM;

	/* Allocate a socket */
	s = socket(PF_INET, type, ppe->p_proto);
	if (s == INVALID_SOCKET)
		errexit("can't create socket: %d\n", GetLastError());

	/* Bind the socket */
	if (bind(s, (struct sockaddr *)&sin, sizeof(sin)) == SOCKET_ERROR)
		errexit("can't bind to %s port: %d\n", service,
		GetLastError());
	if (type == SOCK_STREAM && listen(s, qlen) == SOCKET_ERROR)
		errexit("can't listen on %s port: %d\n", service,
		GetLastError());
	return s;
}

SOCKET connectsock(const char *host, const char *service, const char *transport )
{
	struct hostent	*phe;	/* pointer to host information entry	*/
	struct servent	*pse;	/* pointer to service information entry	*/
	struct protoent *ppe;	/* pointer to protocol information entry*/
	struct sockaddr_in sin;	/* an Internet endpoint address		*/
	int	s, type;	/* socket descriptor and socket type	*/


	memset(&sin, 0, sizeof(sin));
	sin.sin_family = PF_INET;

	/* Map service name to port number */
	if ( pse = getservbyname(service, transport) )
		sin.sin_port = pse->s_port;
	else if ( (sin.sin_port = htons((u_short)atoi(service))) == 0 )
		errexit("can't get \"%s\" service entry\n", service);

	/* Map host name to IP address, allowing for dotted decimal */
	if ( phe = gethostbyname(host) )
		memcpy(&sin.sin_addr, (const void*)phe->h_addr, phe->h_length);
	else if ( (sin.sin_addr.s_addr = inet_addr(host)) == INADDR_NONE)
		errexit("can't get \"%s\" host entry\n", host);

	/* Map protocol name to protocol number */
	if ( (ppe = getprotobyname(transport)) == 0)
		errexit("can't get \"%s\" protocol entry\n", transport);
	/* Use protocol to choose a socket type */
	if (strcmp(transport, "udp") == 0)
		type = SOCK_DGRAM;
	else
		type = SOCK_STREAM;

	/* Allocate a socket */
	s = socket(PF_INET, type, ppe->p_proto);
	if (s == INVALID_SOCKET)
		errexit("can't create socket: %d\n", GetLastError());

	/* Connect the socket */
	if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) == SOCKET_ERROR)
		errexit("can't connect to %s.%s: %d\n", host, service,
		GetLastError());
	return s;
}


#endif
