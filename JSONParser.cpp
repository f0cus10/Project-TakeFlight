//
// Created by gruno on 2/24/18.
//
#include <iostream>
#include "JSONParser.hpp"

using namespace std;

JSONParser::JSONParser(const string & fl): fileName{fl} {}

void JSONParser::readData() {
    //Take the filename and setup a c-style pointer
    FILE *filePointer = fopen(fileName.c_str(), "rb");

    /* Error Checking */
    if (!filePointer){
        perror(fileName.c_str());
        exit(EXIT_FAILURE);
    }

    fseek(filePointer, 0, SEEK_END);
    size_t size = ftell(filePointer);
    fseek(filePointer, 0, SEEK_SET);

    vector<char> buffer;
    buffer.resize(size+1);

    fread(buffer.data(), 1, size, filePointer);
    fclose(filePointer);

    jsonParse(buffer.data(), &endptr, &value, allocator);
}

unordered_map<string, vector<string> > JSONParser::parseData(){
    //Value now contains all the values of the JSON
    unordered_map<string, vector<string> > tmp;
    //Value has a hierarchy
    //Time and states are the 2 JSON_OBJECT data types
    return tmp;
}

void JSONParser::append(unordered_map<string, vector<string> > & myMap , const JsonValue& v){
    return;
}

