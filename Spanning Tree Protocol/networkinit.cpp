#include "bridge.h"

map<int,int> bridgeidtoindex;
map<char,Lan> l;
map<int,char> hosttolan;

void func(int h1, int h2, char alan, char blan, Bridge* b,int ignorebridgeid = -1){
	Lan x = l[alan];
	set<int> :: iterator it;
	for(it = x.b.begin();it != x.b.end() ;it++){
		if(b[bridgeidtoindex[*it]].Lans[alan]!='N'){
			if(ignorebridgeid == -1 || ignorebridgeid != *it){
				b[bridgeidtoindex[*it]].Forwarding_table[h1] = alan;
				if(b[bridgeidtoindex[*it]].Forwarding_table.find(h2) == b[bridgeidtoindex[*it]].Forwarding_table.end()){
					map<char,char> :: iterator itt;
					for(itt = b[bridgeidtoindex[*it]].Lans.begin(); itt != b[bridgeidtoindex[*it]].Lans.end(); itt++){
						if(itt->first != alan && itt->second != 'N'){
							func(h1,h2,itt->first,blan,b,*it);
						}
					}
				}
				else{
					if(b[bridgeidtoindex[*it]].Forwarding_table[h2]!=alan)
						func(h1,h2,b[bridgeidtoindex[*it]].Forwarding_table[h2],blan,b,*it);
				}
			}
		}
	}
}


int main(){
	bool trace;
	cin>>trace;
	int n;
	cin>>n;
	Bridge b[n];
	string s;
	getline(cin,s);				
	for(int i = 0;i<n;i++){
		getline(cin,s);
		int num = stoi(s.substr(1,s.find(':') - 1));
		s = s.substr(s.find(" ")+1);
		bridgeidtoindex[num] = i;
		int noOflans = (s.length()+1)/2;
		b[i].init(num);
		for(int j = 0;j<noOflans;j++){
			b[i].addLan(s[0]);
			map<char,Lan> :: iterator it;
			it = l.find(s[0]);
			if(it == l.end()){
				Lan a;
				a.name = s[0];
				a.b.insert(num);
				l[s[0]] = a;
			}
			else{
				l[s[0]].b.insert(num);
			}
			s = s.substr(s.find(" ")+1);
		}
	}

	int time = 1;
	bool check = true;
	while(check){
		check = false;
		if(trace==1){
			for(int i = 0;i<n;i++){
				Message m = b[i].generate_message();
				map<char,char>:: iterator it;
				for(it = b[i].Lans.begin(); it != b[i].Lans.end(); it++){
					m.lan = it->first;
					Lan x = l[it->first];
					set<int> :: iterator itt;
					for(itt = x.b.begin();itt != x.b.end() ;itt++){
						if(bridgeidtoindex[*itt]!=i){
							cout<<time<<" B"<<*itt<<" s (B"<<m.root<<", "<<m.d<<", B"<<m.source<<")"<<endl;
							if(b[bridgeidtoindex[*itt]].acceptmessage(m))	check = true;
						}
					}
				}
			}
		}
		time++;
		for(int i = 0;i<n;i++){
			Message m = b[i].generate_message();
			map<char,char>:: iterator it;
			for(it = b[i].Lans.begin(); it != b[i].Lans.end(); it++){
				m.lan = it->first;
				Lan x = l[it->first];
				set<int> :: iterator itt;
				for(itt = x.b.begin();itt != x.b.end() ;itt++){
					if(bridgeidtoindex[*itt]!=i){
						if(trace==1)	cout<<time<<" B"<<*itt<<" s (B"<<m.root<<", "<<m.d<<", B"<<m.source<<")"<<endl;
						if(b[bridgeidtoindex[*itt]].acceptmessage(m))	check = true;
					}
				}
			}
		}
	}

	map<char,Lan> :: iterator it;
	for(it = l.begin(); it != l.end(); it++){
		Lan x = it->second;
		set<int> :: iterator itt,temp;
		for(itt = x.b.begin();itt != x.b.end() ;itt++){
			if(b[bridgeidtoindex[*itt]].Lans[it->first]=='D'){
				temp = itt;
				itt++;
				break;
			}
		}
		for(itt = itt; itt != x.b.end() ;itt++){
			if(b[bridgeidtoindex[*itt]].Lans[it->first]=='D'){
				Message m1 = b[bridgeidtoindex[*itt]].generate_message();
				Message m2 = b[bridgeidtoindex[*temp]].generate_message();
				if(m1.d < m2.d){
					b[bridgeidtoindex[*temp]].Lans[it->first]='N';
					temp = itt;
				}
				else if(m2.d < m1.d){
					b[bridgeidtoindex[*itt]].Lans[it->first]='N';
				}
				else if(m1.source < m2.source){
					b[bridgeidtoindex[*temp]].Lans[it->first]='N';
					temp = itt;	
				}
				else if(m2.source < m1.source){
					b[bridgeidtoindex[*itt]].Lans[it->first]='N';
				}
			}
		}
	}

	for(int i = 0;i<n;i++)	b[i].print();

	// cout<<"AS"<<endl;
	for(int i = 0;i< l.size(); i++){
		getline(cin,s);
		char x = s[0];
		s = s.substr(3);
		while(s.size()>0 && s[0]=='H'){
			if(s.find(" ")!= -1){
				l[x].hosts.insert(stoi(s.substr(1,s.find(" "))));
				hosttolan[stoi(s.substr(1,s.find(" ")))] = x;
				s = s.substr(s.find(" ")+1);
			}
			else{
				s = s.substr(1);
				l[x].hosts.insert(stoi(s));
				hosttolan[stoi(s)] = x;
			}
		}
	}
	// cout<<"AS"<<endl;
	int k;
	cin>>k;
	getline(cin,s);
	int order[k];
	for(int i = 0;i<k;i++){
		getline(cin,s);
		int h1,h2;
		h1 = stoi(s.substr(1,s.find(" ")-1));
		h2 = stoi(s.substr(s.find(" ")+2));
		order[i] = h1;
		char alan,blan;
		alan = hosttolan[h1];
		blan = hosttolan[h2];
		func(h1,h2,alan,blan,b);
		for(int j = 0;j<n;j++)	b[j].print1(order,i+1);
		cout<<endl;
	}
}