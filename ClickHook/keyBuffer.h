#ifndef __KEY_BUFFER_H
#define __KEY_BUFFER_H

#define BUFFER_SIZE 50

class CKeyBuffer{
public:
	int	keys;
	int myBack;
	unsigned char KeyBuffer[BUFFER_SIZE];
	int	CaseBuffer[BUFFER_SIZE];         
	WORD UnicodeBuffer[BUFFER_SIZE]; 
	unsigned char AnsiBuffer[BUFFER_SIZE];
	unsigned char prevChar;
public:
	CKeyBuffer(){
			keys=1;
			KeyBuffer[0]='k';
	}
	void processChar(unsigned char);

	void processDoubleMark(unsigned char );
	void processBreveMark(unsigned char );
	void processToneMark(unsigned char );
	void TelexShortKey(unsigned char );
	void PostChar(int,unsigned  char,int returnK);//returnK thiet lap truong hop nhan lai cung phim dau

};//end KeyBuffer

#endif