#ifndef _CODE_TABLE_H
#define _CODE_TABLE_H

unsigned char _8bitWovel[][12][6];
unsigned char _8bitDouble[][8];
unsigned char _8bitBreve[][6];
WORD L_16bitWovel[][72];
WORD H_16bitWovel[][72];
WORD _16bitdd[];
WORD _16bitDD[];


class CCodeTable{
public:
	void buildCodeTable(int typing,int index);

};

#endif