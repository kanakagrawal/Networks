#include "trie.h"
#include "utils.h"

int main(){
	string s;
	getline(cin,s);
	getline(cin,s);
	int x = s.find(" ");
	string a,b;
	map<int,string> ForwardingTableString;
	int index = 1;
	ForwardingTableString[0] = "default";
	Trie forwardingtable;
	while(x!=-1){
		a = s.substr(0,x);
		b = s.substr(x+1);
		ForwardingTableString[index] = s;
		int sig;
		bitset<32> tete = addEntrytoTable(sig,a,b);
		forwardingtable.insert(tete,31,index,sig);
		getline(cin,s);
		x = s.find(" ");
		index++;
	}
	int n;
	cin>>n;
	getline(cin,s);
	while(getline(cin,s)){
		int sig;
		bitset<32> tete = addEntrytoTable(sig,s);
		int temp = forwardingtable.search(tete,31,0);
		cout<<s<<" "<<ForwardingTableString[temp]<<endl;
	}
}