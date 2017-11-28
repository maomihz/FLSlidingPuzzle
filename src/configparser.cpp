#include "configparser.h"
// *** Public Functions ***
// ==================================
//          File Loaders
// ==================================
// Load from file
void ConfigParser::load() {
    ifstream ifs(file);
    // Just ignore empty file
    if (ifs.is_open()) {
        string key, value;
        while(getline(ifs, key, '=')) {
            getline(ifs, value);
            config[key] = value;
        }
        ifs.close();
    }
}

// Write to file
void ConfigParser::write() {
    ofstream ofs(file);
    for (auto it = config.begin(); it != config.end(); ++it) {
        ofs << it->first << "=" << it->second << endl;
    }
    ofs.close();
}


// Change the file to read and write
void ConfigParser::set_file(string fname) {
    file = fname;
}
