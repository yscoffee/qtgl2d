/*
*  Just contain some def. of  data type
*
*/


#ifndef SPECIALIZETYPE
#define SPECIALIZETYPE

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cassert>
 


template<typename T1,typename T2> 
class KeyValPair{
private:
	KeyValPair(){}
	std::pair<T1,T2> keyAndValue;
public:
	KeyValPair(T1 key ,T2 val):keyAndValue(key,val){}

	T1 getKey(){return keyAndValue.first;}
	T2 getVal(){return keyAndValue.second;}
};
 

template<typename T>
class PrintOut{
public:
	void operator() (T element){
			std::cout<<element;
		}
};

template<typename T1,typename T2>
class PairPrintOut{
public:

	void operator() ( std::pair<T1,T2> element){
		std::cout<<element.first<<" "<<element.second<<std::endl;
	}
};




#endif
