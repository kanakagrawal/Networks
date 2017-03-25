#include <iostream>
#include <string>
#include <map>
#include <bitset>
using namespace std;

bitset<32> addEntrytoTable(int &sig,string a, string b = "255.255.255.255");	//return a 32 bit number after anding a and b. also set sig to number of 1's in b(netmask).