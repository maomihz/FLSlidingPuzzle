#include <unordered_map>
#include <string>
#include <fstream>
#include <vector>


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
// key3=[1,2,3,4,5]
//
// The configurations are not ordered. Default configuration is a mask on top
// of the configuration, and it is not written to the disk. Every time the
// parser is initialized, the default configuration need to be set.

class ConfigParser {
private:
    unordered_map<string, string> default_config;
    unordered_map<string, string> config;
    string file;   // The configuration file to read and write

    // Serializer
    string to_str(vector<int> v);  // Serialize an integer vector to a string
    string to_str(vector<string> v); // Serialize an string vector to a string
    string to_str(int i);          // Serialize an integer to a string

    // Parser
    vector<int> to_v(string s);    // Parse a vector string to a vector
    vector<string> to_v_str(string s); // Parse a vector of string
    int to_i(string s);            // Parse an integer string to an integer

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
    string get(string key);         // Get a configuration
    int get_int(string key);        // Get a conf and convert to int
    vector<string> get_v_str(string key);// Get a conf and convert to vector<string>
    vector<int> get_v(string key);  // Get a conf and convert to vector<int>

    // Set a configuration item
    void set(string key, string value, bool default_conf=false);
    void set(string key, int value, bool default_conf=false);
    void set(string key, vector<string> value, bool default_conf=false);
    void set(string key, vector<int> value, bool default_conf=false);

    // Change the file to read or write
    void set_file(string fname);

};
