#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    std::string note0;
    std::string note1;
    std::string note2;
    std::string note3;


    ifstream inFile("input.txt");
    if (!inFile) {
        cout << "open input error" << std::endl;
        return 1;
    }

    ofstream outFile("output.txt");
    if (!outFile) {
        cout << "open output error" << std::endl;
        return 1;
    }

    //string str_line;
    getline(inFile, note0);
    getline(inFile, note1);
    getline(inFile, note2);
    getline(inFile, note3);

    string new_string = "";
    for (int i=0; i<note0.length(); i++) {
        new_string += "B";
        if (note0[i] == '-')
            new_string += "00";
        else
            new_string += "11";
        if (note1[i] == '-')
            new_string += "00";
        else
            new_string += "11";
        if (note2[i] == '-')
            new_string += "00";
        else
            new_string += "11";
        if (note3[i] == '-')
            new_string += "00";
        else
            new_string += "11";

        new_string += ", ";
    }
    

    inFile.close();

    outFile << new_string;

    outFile.close();

    return 0;
}
