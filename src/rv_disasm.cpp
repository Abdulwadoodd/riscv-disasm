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
            illegal_op(instruction[i]);
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

        case(instr_typedef::I_ld):
            I_ld_type_handler (instruction[i]);
            break;

        case(instr_typedef::S):
            S_type_handler (instruction[i]);
            break;

        case(instr_typedef::J):
            J_type_handler (instruction[i]);
            break;

        case(instr_typedef::B):
            B_type_handler(instruction[i]);
            break;

        case(instr_typedef::I_jalr):
            I_jalr_type_handler (instruction[i]);
            break;
//
//        case(instr_typedef::U):
//            U_type_handler (instruction[i]);
//            break;

        default:
            //cout << "Illegal Instruction\n";
            illegal_op(instruction[i]);
        }
    }
}

uint8_t Disassembler::get_opcode(const uint32_t instruction)
{
    return instruction & 0x0000007F;
}

void Disassembler::illegal_op(const uint32_t instruction)
{
    cout << "Illegal instruction : 0x"
         << setfill('0') << setw(8)
         << hex << instruction << endl;
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

    cout << R_type_table.at(mnemonic)       << "\t"
         << gp_regs_name_table[rd].second   << ","
         << gp_regs_name_table[rs1].second  << ","
         << gp_regs_name_table[rs2].second  << endl;
}

void Disassembler::I_gp_type_handler(const uint32_t instruction)
{
    uint8_t mnemonic, rd, rs1;
    uint16_t imm;
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

    cout << I_gp_type_table.at(mnemonic)    << "\t"
         << gp_regs_name_table[rd].second   << ","
         << gp_regs_name_table[rs1].second  << ","
         << dec << imm << endl;
}

void Disassembler::I_ld_type_handler(const uint32_t instruction)
{
    uint8_t mnemonic, rd, rs1;
    uint16_t imm;
    mnemonic = (instruction >> 12) & func3_mask;
    rd  = (instruction>> 7) & reg_mask;
    rs1 = (instruction>>15) & reg_mask;
    imm = (instruction>>20) & 0xFFF;

    cout << I_ld_type_table.at(mnemonic)    << "\t"
         << gp_regs_name_table[rd].second   << ","
         << dec << imm << "("
         << gp_regs_name_table[rs1].second  << ")"
         << endl;
}

void Disassembler::S_type_handler(const uint32_t instruction)
{
    uint8_t mnemonic, rs1, rs2;
    uint16_t imm;

    mnemonic = (instruction >> 12) & func3_mask;
    rs1 = (instruction>>15) & reg_mask;
    rs2 = (instruction>>20) & reg_mask;
    imm = (instruction>> 7) & 0x1F;
    imm|= ((instruction>>25) & 0x7F)<<5;

    cout << S_type_table.at(mnemonic)       << "\t"
         << gp_regs_name_table[rs2].second  << ","
         << dec << imm << "("
         << gp_regs_name_table[rs1].second  << ")"
         << endl;
}

void Disassembler::B_type_handler(const uint32_t instruction)
{
    uint8_t mnemonic, rs1, rs2;
    uint16_t imm;

    mnemonic = (instruction >> 12) & func3_mask;
    rs1  = (instruction>>15) & reg_mask;
    rs2  = (instruction>>20) & reg_mask;
    imm  = (instruction>>8) & 0xF;
    imm |= ((instruction>>25) & 0x3F)<<4;
    imm |= ((instruction>>7) & 0x1)<<10;
    imm |= ((instruction>>31) & 0x1)<<11;
    imm  = imm<<1;

    cout << B_type_table.at(mnemonic)       << "\t"
         << gp_regs_name_table[rs1].second  << ","
         << gp_regs_name_table[rs2].second  << ", PC + 0x"
         << hex << int(imm) << endl;
}

void Disassembler::J_type_handler(const uint32_t instruction)
{
    uint8_t rd;
    int imm;

    rd   = (instruction>> 7) & reg_mask;
    imm  = (instruction>>21) & 0x3FF;
    imm |= ((instruction>>20) & 0x1)<<10;
    imm |= ((instruction>>12) & 0xFF)<<11;
    imm |= ((instruction>>31) & 0x1)<<20;
    imm = imm<<1;

    cout << "jal\t" << gp_regs_name_table[rd].second << ", PC + 0x"
         << hex << int(imm) << endl;
}

void Disassembler::I_jalr_type_handler(const uint32_t instruction)
{
    uint8_t rd, rs1;
    uint16_t imm;

    rd   = (instruction>> 7) & reg_mask;
    rs1  = (instruction>>15) & reg_mask;
    imm = (instruction>>20) & 0xFFF;

    cout << "jalr\t" << gp_regs_name_table[rd].second << ","
         << dec << imm << "("
         << gp_regs_name_table[rs1].second << ")"
         << endl;

}