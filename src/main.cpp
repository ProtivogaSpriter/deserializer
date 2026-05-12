//deserializing data
//<data>;<rand_index>

#include "deserializedwriter.h"
#pragma once

using namespace std;

int main() {
	//create a deserializer
	Deserializer ds;

	//deserialize
	ListNode* head = ds.deserialize();
	
	//create a deserializedwriter
	DeserializedWriter dw(head);
	
	//write deserialized
	dw.write_deserialized();
}
