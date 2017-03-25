#include <iostream>
#include <string>
#include <map>
#include <bitset>

using namespace std;


class Trie{
	Trie* left,*right;
	bool isValid;
	int ind;
public:
	Trie();
	~Trie();
	void insert(bitset<32> &b,int i,int index,int sig);			//i is used for which index of bitset are we at presently
																//sig stores the number of sig bits or the depth of tree from here onwards
																//index stores a value corresponding to the current insert line in forwarding table(used to access back from map in main file)
	int search(bitset<32> &b,int i,int index);					//similar variable meaning as in insert

};