#include "configparser.h"
#include <iostream>
#include <sstream>

// **** Private Helper Functions ****
// ==================================
//            Serializers
// ==================================

// Convert a vector to a string
// {1,3,4,2,6,7} ==> "1,3,4,2,6,7,"
string ConfigParser::to_str(vector<int> v) {
    // Use a string stream
    stringstream ss;

    // Iterate through the vector
    for (auto i = v.begin(); i != v.end();++i) {
        ss << *i << ",";
    }
    return ss.str();
}

// Convert a string vector to a string
string ConfigParser::to_str(vector<string> v) {
    // Use a string stream
    stringstream ss;

    // Iterate through the vector
    for (auto i = v.begin(); i != v.end();++i) {
        ss << *i << ",";
    }
    return ss.str();
}

// Convert a int to a string
// 54 ==> "54"
string ConfigParser::to_str(int i) {
    stringstream ss;
    ss << i;
    return ss.str();
}



// ==================================
//              Parsers
// ==================================
// Parse an vector of int
vector<int> ConfigParser::to_v(string s) {
    stringstream ss(s);

    // Discard some initial characters
    ss >> skipws;

    // Initialize some variables
    char delim;
    int i;
    vector<int> result;

    // Read the numbers, ignore white space
    while (ss >> skipws >> i >> skipws >> delim) {
        result.push_back(i);
    }
    return result;
}

// Parse a vector of string
vector<string> ConfigParser::to_v_str(string s) {
    stringstream ss(s);

    // Discard some initial characters
    ss >> skipws;

    // Initialize some variables
    string i;
    vector<string> result;

    // Read the numbers, ignore white space
    while (getline(ss, i, ',')) {
        result.push_back(i);
    }
    return result;
}

// Parse an int
int ConfigParser::to_i(string s) {
    stringstream ss(s);
    int i = 0;
    ss >> i;
    return i;
}


// *** Public Functions ***
// ==================================
//          File Loaders
// ==================================
// Load from file
void ConfigParser::load() {
    ifstream ifs(file);
    // Just ignore empty file
    if (!ifs.is_open()) {
        return;
    }

    string key, value;
    while(getline(ifs, key, '=')) {
        getline(ifs, value);
        config[key] = value;
    }
    ifs.close();
}

// Write to file
void ConfigParser::write() {
    ofstream ofs(file);
    for (auto it = config.begin(); it != config.end(); ++it) {
        ofs << it->first << "=" << it->second << endl;
    }
    ofs.close();
}


// ==================================
//              Getters
// ==================================
// Get a configuration key
string ConfigParser::get(string key) {
    try {
        return config.at(key);
    } catch (out_of_range e) {
        return default_config.at(key);
    }
}
int ConfigParser::get_int(string key) {
    return to_i(get(key));
}
vector<string> ConfigParser::get_v_str(string key) {
    return to_v_str(get(key));
}
vector<int> ConfigParser::get_v(string key) {
    return to_v(get(key));
}

// ==================================
//              Setters
// ==================================
// Set a configuration key
void ConfigParser::set(string key, string value, bool default_conf) {
    if (default_conf) {
        default_config[key] = value;
    } else {
        config[key] = value;
    }
}
void ConfigParser::set(string key, int value, bool default_conf) {
    set(key, to_str(value), default_conf);
}
void ConfigParser::set(string key, vector<string> value, bool default_conf) {
    set(key, to_str(value), default_conf);
}
void ConfigParser::set(string key, vector<int> value, bool default_conf) {
    set(key, to_str(value), default_conf);
}




// Change the file to read and write
void ConfigParser::set_file(string fname) {
    file = fname;
}
