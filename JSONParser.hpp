//
// Created by gruno on 2/24/18.
//

#ifndef JSONPARSER_JSONPARSER_HPP
#define JSONPARSER_JSONPARSER_HPP
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "gason.h"

using namespace std;

class JSONParser{
public:
    //Default Constructor
    JSONParser(const string&);
    //Read the data into the buffer
    void readData();
    //Returns a pointer to an unordered_map
    unordered_map<string, vector<string> > parseData();
private:
    string fileName;
    vector<char> buffer;
    JsonAllocator allocator;
    JsonValue value;
    char *endptr;

    //Appends the flight information into the unordered_map
    void append(unordered_map<string, vector<string> > & myMap , const JsonValue& v);

    /* Debugging purpose values */
    int numOfObjects = 0;
    int numOfArrays = 0;
};
#endif //JSONPARSER_JSONPARSER_HPP
