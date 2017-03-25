#include <iostream>
#include <map>
#include <string>
#include <set>
using namespace std;


struct Message{
	int root;
	int d;
	int source;
	char lan;
};

class Lan{
public:
	set<int> b;	//bridge ids it is connected to 
	set<int> hosts;
	char name;
	bool isHost(int i);
};

class Bridge{
	int id;
	int d;
	int rootID;
	int rootBridge;
	char rootPort;
public:
	map<char,char> Lans;
	map<int,char> Forwarding_table;
	Bridge();
	void init(int i);
	void addLan(char c);
	Message generate_message();
	bool acceptmessage(Message m);
	void print();
	void print1(int* order,int size);
};