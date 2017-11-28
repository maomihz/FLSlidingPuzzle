#include <iostream>
#include <string>

// *** Here are some tests ***
#include "configparser.h"

int main() {
    vector<int> v = {1,6,3,2,7,9,5,3,1,4};
    vector<string> vstr;
    vstr.push_back("animal");
    vstr.push_back("cat");
    vstr.push_back("dog");
    vstr.push_back("pig");
    vstr.push_back("monkey");
    vstr.push_back("dragonfruit");


    ConfigParser parser("test.txt");
    parser.load();
    parser.set("test1", 15, true);
    parser.set("test2", "str", true);
    parser.set("test3", v, true);
    parser.set("test4", vstr, true);

    cout << "test1: " << parser.get<int>("test1") << endl;
    cout << "test2: " << parser.get<string>("test2") << endl;

    vector<int> conf_v = parser.get<vector<int>>("test3");
    cout << "test3: ";
    for (int i : conf_v)
        cout << i << " ";
    cout << conf_v.size();
    cout << endl;

    vector<string> conf_vstr = parser.get<vector<string>>("test4");
    cout << "test4: ";
    for (string i : conf_vstr)
        cout << i << " ";
    cout << endl;

    // Do some assignments
    v[3] = 12;
    v[6] = 19;
    vstr[1] = "kitten";
    vstr[2] = "doggy";

    parser.set("test1", 19);
    parser.set("test2", "strstr");
    parser.set("test3", v);
    parser.set("test4", vstr);
    parser.write();


    // We are going to test some edge cases
    cout << "\n===Edge Cases===\n";
    parser.set("edge1", "Cat=Dog");
    parser.set("edge=2", "Cat!=Dog");
    parser.write();
    parser.load();


    cout << "Value contains \"=\": " << endl;
    cout << "edge1: ";
    cout << parser.get<string>("edge1") << endl;

    cout << "Key contains \"=\": " << endl;
    cout << "edge=2: ";
    cout << parser.get<string>("edge=2") << endl;
    try {
        cout << "edge: ";
        cout << parser.get<string>("edge") << endl;
    } catch (out_of_range e) {
        cout << "Not Exist." << endl;
    }

}
