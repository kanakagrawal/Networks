#include "utils.h"

bitset<32> addEntrytoTable(int &sig, string a, string b){
	int x = a.find(".");
	int A[4],B[4];
	int i = 0;
	while(x!=-1){
		A[i] = stoi(a.substr(0,x));
		i++;
		a = a.substr(x+1);
		x = a.find(".");
	}
	A[i] = stoi(a);
	i = 0;
	x = b.find(".");
	while(x!=-1){
		B[i] = stoi(b.substr(0,x));
		i++;
		b = b.substr(x+1);
		x = b.find(".");
	}
	B[i] = stoi(b);
	int C[4];
	for(i=0;i<4;i++){
		C[i] = A[i] & B[i];
	}
	i = 3;
	while(B[i]==0)	i--;
	sig = (1+i)*8;
	bitset<8> temp(B[i]);
	i = 0;
	while(!temp.test(i) && i<7){
		sig--;
		i++;
	}
	C[0] = C[0] << 24;
	C[1] = C[1] << 16;
	C[2] = C[2] << 8;
	int c = C[0]+C[1]+C[2]+C[3];
	bitset<32> t(c);
	return t;
}