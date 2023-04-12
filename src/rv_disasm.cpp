#include <iostream>
#include <unordered_map>
#include <vector>
#include <iomanip>

#include "rv_disasm.hpp"

using namespace std;

void Disassembler::disassembler(const vector<uint32_t> instruction)
{
    for(int i=0; i < int(instruction.size()); i++ )
    {
        uint8_t opcode = get_opcode(instruction[i]);
        if(opcode_instr_type.find(opcode)==opcode_instr_type.end()){
            cout << "Illegal instruction Opcode: 0x"
                 << setfill('0') << setw(8)
                 << hex << instruction[i] << endl;
            continue;
        }

        instr_typedef type = opcode_instr_type.at(opcode);
        // parse instructions to the respective handler type
        switch (type)
        {
        case(instr_typedef::R):
            R_type_handler (instruction[i]);
            break;

        case(instr_typedef::I_gp):
            I_gp_type_handler (instruction[i]);
            break;
//
//        case(instr_typedef::I_ld):
//            I_ld_type_handler (instruction[i]);
//            break;
//
//        case(instr_typedef::S):
//            S_type_handler (instruction[i]);
//            break;
//
//        case(instr_typedef::J):
//            J_type_handler (instruction[i]);
//            break;
//
//        case(instr_typedef::I_jalr):
//            I_jalr_type_handler (instruction[i]);
//            break;
//
//        case(instr_typedef::U):
//            U_type_handler (instruction[i]);
//            break;

        default:
            cout << "Illegal Instruction\n";
        }
    }
}

uint8_t Disassembler::get_opcode(const uint32_t instruction)
{
    return instruction & 0x0000007F;
}

void Disassembler::R_type_handler(const uint32_t instruction)
{
    uint8_t mnemonic, rd, rs1, rs2;
    // Extract func3 and func7[5]
    // {fun7[5], func3}
    mnemonic =  ((instruction >> 12) & func3_mask);
    mnemonic |= ((instruction >> 27) & func7_mask);
    // extract destination and source registers.
    rd  = (instruction>> 7) & reg_mask;
    rs1 = (instruction>>15) & reg_mask;
    rs2 = (instruction>>20) & reg_mask;

    cout << R_type_table.at(mnemonic)     << "\t";
    cout << gp_regs_name_table[rd].second   << ", ";
    cout << gp_regs_name_table[rs1].second  << ", ";
    cout << gp_regs_name_table[rs2].second  << endl;
}

void Disassembler::I_gp_type_handler(const uint32_t instruction)
{
    uint8_t mnemonic, rd, rs1, imm;
    mnemonic =  ((instruction >> 12) & func3_mask);
    rd  = (instruction>> 7) & reg_mask;
    rs1 = (instruction>>15) & reg_mask;

    switch(mnemonic)
    {
    case (0x1): // srli, srai
    case (0x5): // slli
        mnemonic |= ((instruction >> 27) & func7_mask);
        imm = (instruction>>20) & 0x1F;
        break;
    default:
        imm = (instruction>>20) & 0xFFF;
    }

    cout << I_gp_type_table.at(mnemonic)    << "\t";
    cout << gp_regs_name_table[rd].second   << ", ";
    cout << gp_regs_name_table[rs1].second  << ", 0x";
    cout << hex << int(imm) << endl;
}

