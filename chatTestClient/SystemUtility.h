#ifndef SYSTEMUTILITY
#define SYSTEMUTILITY

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include "SpecializeType.h"


//#define NODEBUG // for assert.h

//#define DEBUG_COUT
#ifdef DEBUG_COUT

#define  DE_PRINT(X); std::cout<<X<<std::endl;
#endif

#ifndef DEBUG_COUT
#define DE_PRINT(X); 
#endif

// template class to handle general input from user
//


template<typename T>
class GetUserInput{
public:	
	T operator() (char* descibeStr=NULL  ){

		// read until success
		while(1){

			if(descibeStr!=NULL)
				std::cout<<descibeStr;
			T tempInput;
			std::cin>>tempInput;

			// simple error handle
			if(std::cin.fail()){
				std::cout<<"Invalid input . "<<std::endl;
				std::cin.clear();
				std::string temp;
				std::getline(std::cin,temp);
			}else{
				return tempInput;
			}

		}
	}	
}; 


template<>
class GetUserInput<string>{
public:	
	string operator() (char* descibeStr=NULL  ){

		// read until success
		while(1){

			if(descibeStr!=NULL)
				std::cout<<descibeStr;

			std::string input;
			std::getline(std::cin,input);
			
			// simple error handle
			if(std::cin.fail()){
				std::cout<<"Invalid input . "<<std::endl;
				std::cin.clear();
				std::string temp;
				std::getline(std::cin,temp);
			}else{
				return input;
			}

		}
	}	
}; 
void sysWait(double SEC){

	_sleep(static_cast<unsigned long>(1000*SEC) );
}
void printNChar(char c , int num){
	std::string ss(num,c);
	std::cout<<ss<<std::endl;
}

void clearSysConsole(){
     
#ifndef DEBUG_COUT
	//std::system("cls");
#endif
}
void pauseSystem(){
	std::system("pause");
}

template <typename T>
std::string toString( T obj){

	std::stringstream sstrm;

	sstrm<<obj;

	return sstrm.str();

}

#endif
