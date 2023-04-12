#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "rv_disasm.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    // Check if the file name is parsed through command line
    if (argc < 2) {
        cout << "Please provide a filename as an argument." << endl;
        return 1;
    }
    // Open the file
    ifstream hexfile(argv[1]);
    // Check if file can be open
    if (!hexfile.is_open()) {
        cout << "Failed to open file " << argv[1] << endl;
        return 1;
    }

    string instruction_s;
    vector <uint32_t> instruction;

    while(getline(hexfile, instruction_s)){
        stringstream ss (instruction_s);
        uint32_t ibuf;
        ss >> hex >> ibuf;
        instruction.push_back(ibuf);
    }

    hexfile.close();

    cout << "Disassembling RV32I INSTRUCTIONS!!" << endl;
    Disassembler disasm;
    disasm.disassembler(instruction);

    return 0;
}

