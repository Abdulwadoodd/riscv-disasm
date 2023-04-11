#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "rv_disasm.hpp"

using namespace std;

int main()
{
    cout << "Dis-assemblying RV32I INSTRUCTIONS!!" << endl;
    string instruction_s;
    vector <uint32_t> instruction;
    ifstream myfile("instr.hex");

    while(getline(myfile, instruction_s)){
        stringstream ss (instruction_s);
        uint32_t ibuf;
        ss >> hex >> ibuf;
        instruction.push_back(ibuf);
    }

    Disassembler disasm;
    disasm.disassembler(instruction);

    return 0;
}
