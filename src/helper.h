#include <string>
#include <iostream>
#include <fstream>

using namespace std;

//for all those times when it doesn't make sense
//i was too lazy to implement exceptions/return errors :(
void exit_with_error(string error){
	cout << "exiting with error: " << error << endl;
	exit(1);
}

//writes anything as raw bytes to given ofstream
template<typename T>
void write_bytes(T data, ostream& ofile){
	ofile.write((const char*)(&data), sizeof(data));
}

//concrete overload for string specifically
void write_bytes(string data, ostream& ofile){
	ofile.write((const char*)(&data), sizeof(data));
	//if SSO, the data is already in the structure;
	//otherwise, manually copy.
	if(data.size() > 15){
		ofile.write((const char*)data.data(), data.size());
	}
}
