#include "bridge.h"

Bridge :: Bridge(){
	d = 0;
}

void Bridge :: init(int i){
	id = i;
	rootID = i;
	rootBridge = i;
}

void Bridge :: addLan(char c){
	Lans[c] = 'D';					// D for Designated port
}

Message Bridge :: generate_message(){
	Message m;
	m.root = rootID;
	m.d = d;
	m.source = id;
	return m;
}

bool Bridge :: acceptmessage(Message m){
	if((m.root < rootID) || ((m.root == rootID) && (m.d + 1 < d)) || ((m.root == rootID) && (m.d+1==d) && (m.source < rootBridge))){
		rootID = m.root;
		d = m.d + 1;
		map<char,char> :: iterator it;
		it = Lans.find(rootPort);
		if(it!=Lans.end() && Lans[rootPort] != 'N'){
			Lans[rootPort] = 'D';
		}
		rootPort = m.lan;
		rootBridge = m.source;
		Lans[rootPort] = 'R';
		return true;
	}
	// else{
	// 	cout<<m.lan<<endl;
	// 	map<char,char> :: iterator it;
	// 	it = Lans.find(m.lan);
	// 	if(it!=Lans.end()){
	// 		Lans[m.lan] = 'N';
	// 	}
	// }
	return false;		
}


void Bridge :: print(){
	cout<<"B"<<id<<":";
	map<char,char> ::iterator it;
	for(it = Lans.begin();it!=Lans.end();it++){
		cout<<" "<<it->first<<"-"<<it->second<<"P";
	}
	cout<<endl;
}

void Bridge :: print1(int* order,int size){
	cout<<"B"<<id<<":"<<endl;
	cout<<"HOST ID | FORWARDING PORT"<<endl;
	set<int> temp;
	// cout<<size<<endl;
	for(int i = 0;i<size;i++){
		// cout<<order[i]<<endl;
		if(temp.find(order[i])==temp.end()){
			temp.insert(order[i]);
			if(Forwarding_table.find(order[i])!= Forwarding_table.end()){
			cout<<"H"<<order[i]<<" | "<<Forwarding_table[order[i]]<<endl;
			}
		}
	}
	// map<int,char> ::iterator it;
	// for(it = Forwarding_table.begin();it!=Forwarding_table.end();it++){
	// 	cout<<"H"<<it->first<<" | "<<it->second<<endl;
	// }
}


bool Lan :: isHost(int i){
	if(hosts.find(i)==hosts.end())	return false;
	else	return true;
}



