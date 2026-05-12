#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <utility>
#include <cstdint>
#include <cstring>
#include "helper.h"
#include "listnode.h"
#pragma once

using namespace std;

//deserializes
class Deserializer{
	public:
	Deserializer();
	Deserializer(ifstream);
	ListNode* deserialize();

	private:
	ifstream ifile;
	pair<string, int64_t> deserialize_string(string);
	vector<string> into_lines();
};

Deserializer::Deserializer(){
	ifile = ifstream("inlet.in");
}

Deserializer::Deserializer(ifstream ifile_new){
	ifile = move(ifile_new);
}

//turns a single string into a pair of ListNode and rand index
pair<string, int64_t> Deserializer::deserialize_string(string data){
	//read from end until first semicolon, locate it in space
	//memcpy the string before the semicolon
	//cast the rest to int
	uint64_t seperator_idx = data.rfind(";", data.size());
	string data_string(seperator_idx + 1, 0);
	memcpy(data_string.data(), data.data(), seperator_idx);
	string idx_string(data.size() - seperator_idx, 0);
	memcpy(idx_string.data(), data.data()+seperator_idx+1, data.size() - seperator_idx);
	int64_t idx;
	stringstream(idx_string) >> idx;
	return pair<string, int64_t>(data_string, idx);
}

vector<string> Deserializer::into_lines(){
	vector<string> lines;
	string read;
	getline(ifile, read);
	while (read != "") {
		lines.push_back(read);
		getline(ifile, read);
	}
	if (lines.size() < 1) {
		exit_with_error("file is empty");
	}
	return lines;
}

//takes the ifile and deserialzes it, turning text into data
ListNode* Deserializer::deserialize() {
	vector<string> lines = into_lines();
	vector<int64_t> rands;
	vector<ListNode*> collection;
	pair<string, int64_t> pair = deserialize_string(lines[0]);
	ListNode* head = new ListNode{
		nullptr,
		nullptr,
		nullptr,
		move(pair.first),
	};
	ListNode* first_held = head;
	collection.push_back(first_held);
	rands.push_back(pair.second);
	for(int i = 1; i < lines.size(); ++i){
		pair = deserialize_string(lines[i]);
		ListNode* second_held = new ListNode{
			first_held,
			nullptr,
			nullptr,
			move(pair.first),
		};
		first_held->next = second_held;
		first_held = second_held;
		collection.push_back(first_held);
		rands.push_back(pair.second);
	}
	for(int i = 0; i < collection.size(); i++){
		ListNode* target;
		if(rands[i] >= 0){
			target = collection[rands[i]];
		} else {
			target = nullptr;
		}
		collection[i]->rand = target;
	}
	return head;
}
