#include "trie.h"

Trie :: Trie(){
	ind = -1;
	isValid = false;
	left = NULL;
	right = NULL;
}

Trie :: ~Trie(){

}

void Trie :: insert(bitset<32> &b,int i,int index,int sig){
	if(sig==0){
		isValid = true;
		ind = index;
		return;
	}
	if(b.test(i)){
		if(right==NULL){
			right = new Trie;
		}
		right->insert(b,i-1,index,sig-1);
	}
	else{
		if(left==NULL){
			left = new Trie;
		}
		left->insert(b,i-1,index,sig-1);	
	}
}

int Trie :: search(bitset<32> &b,int i,int index){
	if(ind!=-1)	index = ind;
	if(i<0)	return index;
	if(b.test(i)){
		if(right==NULL)	return index;
		return right->search(b,i-1,index);
	}
	else{
		if(left==NULL)	return index;
		return left->search(b,i-1,index);	
	}
}