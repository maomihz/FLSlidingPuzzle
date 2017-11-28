#include <unordered_map>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>

#pragma once

using namespace std;

// *** Configuration Parser class ***
// The config parser parses configuration and have public functions to access
// the values of configuration.
//
// It supports three data types: string, int, vector of int.
// A configuration item consists of a string as the key, and the value.
// When written to the file system, all three data types are serialized to
// a string.
//
// The format of the configuration file looks like this:
// key1=my_value
// key2=14
// key3=1,2,3,4,5,
//
// The configurations are not ordered. Default configuration is a mask on top
// of the configuration, and it is not written to the disk. Every time the
// parser is initialized, the default configuration need to be set.

class ConfigParser {
private:
    unordered_map<string, string> default_config;
    unordered_map<string, string> config;
    string file;   // The configuration file to read and write

public:
    // Constructor
    ConfigParser(string fname)
        : config(),
        file(fname) {}

    void load();  // Load contents from file
    void write(); // Write contents into file

    // Get a configuration item
    // It first checks if the key exist in the ordinary config. If not, then
    // it checks the default config.

    template<class T>
    T get(string key);  // Get a configuration
    template<class T>   // Set a configuration item
    void set(string key, T value, bool default_conf=false);

    // Change the file to read or write
    void set_file(string fname);
};

// Serializer & Parser
template<class T> string to_string(T);
template<class T> T from_string(string s);

// **** Private Helper Functions ****
// ==================================
//            Serializers
// ==================================
// Serialize a vector
template<class T>
ostream& operator<<(ostream& os, const vector<T>& v) {
    for (T e : v) {
        os << e << ",";
    }
    return os;
}

// convert any object to string
template<class T>
string to_string(T obj) {
    ostringstream ss;
    ss << obj;
    return ss.str();
}


// ==================================
//              Parsers
// ==================================
// Parse an vector of int
template<class T>
istream& operator>>(istream& is, vector<T>& v) {
    string item;
    while (getline(is, item, ',')) {
        v.push_back(from_string<T>(item));
    }
    return is;
}

template<class T>
T from_string(string s) {
    istringstream ss(s);
    T result;
    ss >> result;
    return result;
}




// ==================================
//              Getters
// ==================================
// Get a configuration key
template<class T>
T ConfigParser::get(string key) {
    try {
        return from_string<T>(config.at(key));
    } catch (out_of_range e) {
        return from_string<T>(default_config.at(key));
    }
}

// ==================================
//              Setters
// ==================================
// Set a configuration key
template<class T>
void ConfigParser::set(string key, T value, bool default_conf) {
    if (default_conf) {
        default_config[key] = to_string(value);
    } else {
        config[key] = to_string(value);
    }
}
