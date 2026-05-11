#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <utility>
#include <cstdint>
#pragma once

using namespace std;

//writes deserialized
class DeserializedWriter{
	public: 
	DeserializedWriter(ListNode*);
	DeserializedWriter(ListNode*, ofstream);
	void write_deserialized();

	private:
	ofstream ofile;
	ListNode* head;
	vector<ListNode*> make_vector();
	void node_write(ListNode* node);
};

DeserializedWriter::DeserializedWriter(ListNode* head_new){
	ofile = ofstream("outlet.out");
	head = head_new;
}

DeserializedWriter::DeserializedWriter(ListNode* head_new, ofstream ofile_new){
	ofile = move(ofile_new);
	head = head_new;
}

//decompiles the entire node into bytes and writes to ofile
void DeserializedWriter::node_write(ListNode* node) {
	write_bytes(node->prev, ofile);
	write_bytes(node->next, ofile);
	write_bytes(node->rand, ofile);
	write_bytes(node->data, ofile);
}

vector<ListNode*> DeserializedWriter::make_vector(){
	vector<ListNode*> vec;
	ListNode* node = head;
	while (node != nullptr){
		vec.push_back(node);
		node = node->next;
	}
	return vec;
}

//calls node_write on every node
void DeserializedWriter::write_deserialized() {
	vector<ListNode*> list = make_vector();
	for (ListNode* x: list) {
		node_write(x);
	}
}
