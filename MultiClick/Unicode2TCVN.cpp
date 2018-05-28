#include "StdAfx.h"
#include "Unicode2TCVN.h"


CHAR _8bitVowelL[][12][6]={
	//TCVN 3
    	//TCVN 3
    {{'¸','µ','¶','·','¹','a'}, // a'  a`  a?  a~  a.   a		
    {'Ê','Ç','È','É','Ë','©'},	// a^' a^` a^? a^~ a^.  a^	
    {'¾','»','¼','½','Æ','¨'},	// a(' a(` a(? a(~ a^.  a(	
    {'Ð','Ì','Î','Ï','Ñ','e'},	// e'  e`  e?  e~  e.   e
    {'Õ','Ò','Ó','Ô','Ö','ª'},	//e^	
    {'Ý','×','Ø','Ü','Þ','i'},	//i	
    {'ã','ß','á','â','ä','o'},	//o	
    {'è','å','æ','ç','é','«'},	//o^	
    {'í','ê','ë','ì','î','¬'},	//o+	
    {'ó','ï','ñ','ò','ô','u'},	//u	
    {'ø','õ','ö','÷','ù','­'},	//u+	 
    {'ý','ú','û','ü','þ','y'}},  //y
	
};//end _8bit


CHAR _8bitDouble[][8] = {
	//dd  DD    ee   EE   aa  AA   oo    OO
	{'®', '§', 'ª', '£', '©', '¢', '«', '¤'},   //TCVN3
	{'¢', '˜', '£', '™', '¡', '—', '¤', 'š'}    //Vietware-F
};

CHAR _8bitBreve[][6] = {
	//a   A     o    O    u    U
	{'¨', '¡', '¬', '¥', '­', '¦'},   //TCVNI3
	{'Ÿ', '–', '¥', '›', '§', 'œ'}    //Vietware-F
};


WORD _16bitVowelL[][12][6]={
	//Unicode
	{0x00e1, 0x00e0, 0x1ea3, 0x00e3, 0x1ea1, 0x0061,
	 0x1ea5, 0x1ea7, 0x1ea9, 0x1eab, 0x1ead, 0x00e2,
	 0x1eaf, 0x1eb1, 0x1eb3, 0x1eb5, 0x1eb7, 0x0103,
	 0x00e9, 0x00e8, 0x1ebb, 0x1ebd, 0x1eb9, 0x0065,
	 0x1ebf, 0x1ec1, 0x1ec3, 0x1ec5, 0x1ec7, 0x00ea,
	 0x00ed, 0x00ec, 0x1ec9, 0x0129, 0x1ecb, 0x0069,
	 0x00f3, 0x00f2, 0x1ecf, 0x00f5, 0x1ecd, 0x006f,
	 0x1ed1, 0x1ed3, 0x1ed5, 0x1ed7, 0x1ed9, 0x00f4,
	 0x1edb, 0x1edd, 0x1edf, 0x1ee1, 0x1ee3, 0x01a1, 
	 0x00fa, 0x00f9, 0x1ee7, 0x0169, 0x1ee5, 0x0075,
	 0x1ee9, 0x1eeb, 0x1eed, 0x1eef, 0x1ef1, 0x01b0, 
	 0x00fd, 0x1ef3, 0x1ef7, 0x1ef9, 0x1ef5, 0x0079},

};//end

WORD _16bitVowelH[][12][6]={
	//Unicode
	{0x00c1, 0x00c0, 0x1ea2, 0x00c3, 0x1ea0, 0x0041,
	 0x1ea4, 0x1ea6, 0x1ea8, 0x1eaa, 0x1eac, 0x00c2,
	 0x1eae, 0x1eb0, 0x1eb2, 0x1eb4, 0x1eb6, 0x0102,
	 0x00c9, 0x00c8, 0x1eba, 0x1ebc, 0x1eb8, 0x0045,
	 0x1ebe, 0x1ec0, 0x1ec2, 0x1ec4, 0x1ec6, 0x00ca,
	 0x00cd, 0x00cc, 0x1ec8, 0x0128, 0x1eca, 0x0049,
	 0x00d3, 0x00d2, 0x1ece, 0x00d5, 0x1ecc, 0x004f,
	 0x1ed0, 0x1ed2, 0x1ed4, 0x1ed6, 0x1ed8, 0x00d4,
	 0x1eda, 0x1edc, 0x1ede, 0x1ee0, 0x1ee2, 0x01a0,
	 0x00da, 0x00d9, 0x1ee6, 0x0168, 0x1ee4, 0x0055,
	 0x1ee8, 0x1eea, 0x1eec, 0x1eee, 0x1ef0, 0x01af,
	 0x00dd, 0x1ef2, 0x1ef6, 0x1ef8, 0x1ef4, 0x0059},

};//end
WORD _16bitDoubleL[]={
					0x0111
					};
WORD _16bitDoubleH[]={
					0x0110
					};




// Character d-
WORD _16bitdd[] = {
					0x00E2,   // VIETWARE X
					0x00f1,   // VNI
					0x0111,   // Unicode
					0x00E0,   // BKHCM2
					0x00BD,	  // BKHCM1
					0x00C7,   // VPS
					0x00F0,   // VISCII
					0x00f0    };  // Windows CP 1258
					


// Character -D
WORD _16bitDD[] = {
					0x00C2,  // VIETWARE X
					0x00d1,  // VNI
					0x0110,  // Unicode
					0x00C0,  // BKHCM2
					0x007D,	 // BKHCM1
					0x00F1,  // VPS
					0x00D0,  // VISCII
					0x00d0  }; // Windows CP 1258
					 





CHAR* convert1(LPCWSTR st){
	CHAR pChar[257];
	int type=1;
	int len=lstrlenW(st);
	int s=0;
	 for(int m=0;m<len;m++){
		 pChar[m]=tolower((CHAR)st[m]);
		for(int i=0;i<12;i++){
			for(int j=0;j<6;j++){
				for(int k=0;k<1;k++){
					if(type==1){
						if(st[m]==_16bitVowelL[k][i][j]&&st[m]!='a'&&st[m]!='e'&&st[m]!='u'&&st[m]!='i'&&st[m]!='o'&&st[m]!='i'&&st[m]!='y'){
							pChar[m]=_8bitVowelL[0][i][j];
							s=m;
							break;
						}
					}else if(type==2){
						if(st[m]==_16bitVowelH[k][i][j]&&st[m]!='a'&&st[m]!='e'&&st[m]!='u'&&st[m]!='i'&&st[m]!='o'&&st[m]!='i'&&st[m]!='y'){
							pChar[m]=_8bitVowelL[0][i][j];
							s=m;
							break;
						}
					}
				}
			}
		}
		
		if(st[m]==0x0111||st[m]==0x0110){
				pChar[m]=_8bitDouble[0][0];
				s=m;
		}
		if(s==m) pChar[m]=tolower(pChar[m]);
	}
    
	pChar[m]=(CHAR)0;
	return pChar;
}


