#include <vector>
#include <array>
#include <unordered_map>

using namespace std;

#pragma once

    #define func3_mask  0x07
    #define func7_mask  0x8
    #define reg_mask    0x1F

    class Disassembler
    {
        uint8_t get_opcode      (const uint32_t instruction);
        //uint8_t get_type        (const uint32_t instruction);
        void parse_instruction  (const uint32_t instruction);
        void R_type_handler     (const uint32_t instruction);
        void I_gp_type_handler  (const uint32_t instruction);
        void I_ld_type_handler  (const uint32_t instruction);
        void S_type_handler     (const uint32_t instruction);
        void J_type_handler     (const uint32_t instruction);
        void I_jalr_type_handler(const uint32_t instruction);
        void U_type_handler     (const uint32_t instruction);
        void I_call_type_handler(const uint32_t instruction);

    public:
        void disassembler(const vector <uint32_t> instruction);
    };

    enum class instr_typedef
    {
        R,
        I_gp,
        I_ld,
        S,
        B,
        J,
        I_jalr,
        U,
        I_call
    };

    enum gp_regs : uint8_t
		{
			x0, x1, x2, x3, x4, x5, x6, x7,
			x8, x9, x10, x11, x12, x13, x14, x15,
			x16, x17, x18, x19, x20, x21, x22, x23,
			x24, x25, x26, x27, x28, x29, x30, x31
		};

    inline array gp_regs_name_table = {
			pair{gp_regs::x0, "zero"},
			pair{gp_regs::x1, "ra"},
			pair{gp_regs::x2, "sp"},
			pair{gp_regs::x3, "gp"},
			pair{gp_regs::x4, "tp"},
			pair{gp_regs::x5, "t0"},
			pair{gp_regs::x6, "t1"},
			pair{gp_regs::x7, "t2"},
			pair{gp_regs::x8, "s0"},
			pair{gp_regs::x9, "s1"},
			pair{gp_regs::x10, "a0"},
			pair{gp_regs::x11, "a1"},
			pair{gp_regs::x12, "a2"},
			pair{gp_regs::x13, "a3"},
			pair{gp_regs::x14, "a4"},
			pair{gp_regs::x15, "a5"},
			pair{gp_regs::x16, "a6"},
			pair{gp_regs::x17, "a7"},
			pair{gp_regs::x18, "s2"},
			pair{gp_regs::x19, "s3"},
			pair{gp_regs::x20, "s4"},
			pair{gp_regs::x21, "s5"},
			pair{gp_regs::x22, "s6"},
			pair{gp_regs::x23, "s7"},
			pair{gp_regs::x24, "s8"},
			pair{gp_regs::x25, "s9"},
			pair{gp_regs::x26, "s10"},
			pair{gp_regs::x27, "s11"},
			pair{gp_regs::x28, "t3"},
			pair{gp_regs::x29, "t4"},
			pair{gp_regs::x30, "t5"},
			pair{gp_regs::x31, "t6"}
		};

    const unordered_map <uint8_t, const instr_typedef> opcode_instr_type
    {
        // RV32I
            {0x37, instr_typedef::U},       // lui
			{0x17, instr_typedef::U},       // auipc
			{0x6F, instr_typedef::J},       // jal
			{0x67, instr_typedef::I_jalr},  // jalr
			{0x63, instr_typedef::B},       // branch (beq, bne, blt, bge, bltu, bgeu)
			{0x23, instr_typedef::S},       // store (sb, sh, sw)
			{0x13, instr_typedef::I_gp},    // I-type (addi, xori, etc.)
			{0x33, instr_typedef::R},       // R-type (add, sub, xor, ect.)
			//{0x0F, instr_typedef::I},     // fence
			{0x73, instr_typedef::I_call},  // ecall, ebreak
			{0x03, instr_typedef::I_ld}     // Load (lw, lh, lb, lbu, lhu)
    };

    const unordered_map <uint8_t, string> R_type_table
    {
     // { {func7[5],func3}, "mnemonic"}
        {0x0, "add"},
        {0x8, "sub"},
        {0x4, "xor"},
        {0x6, "or"},
        {0x7, "and"},
        {0x1, "sll"},
        {0x5, "srl"},
        {0xD, "sra"},
        {0x2, "slt"},
        {0x3, "sltu"}
    };

    const unordered_map <uint8_t, string> I_gp_type_table
    {
     // { {func7[5],func3}, "mnemonic"}
        {0x0, "addi"},
        {0x4, "xori"},
        {0x6, "ori"},
        {0x7, "andi"},
        {0x1, "slli"},
        {0x5, "srli"},
        {0xD, "sra"},
        {0x2, "slti"},
        {0x3, "sltiu"}
    };

    const unordered_map <uint8_t, string> I_ld_type_table
    {
     // {func3 , "mnemonic"}
        {0x0, "lb"},
        {0x1, "lh"},
        {0x2, "lw"},
        {0x4, "lbu"},
        {0x5, "lhu"}
    };

    const unordered_map <uint8_t, string> S_type_table
    {
     // {func3 , "mnemonic"}
        {0x0, "sb"},
        {0x1, "sh"},
        {0x2, "sw"}
    };

    const unordered_map <uint8_t, string> B_type_table
    {
     // {func3 , "mnemonic"}
        {0x0, "beq"},
        {0x1, "bne"},
        {0x4, "blt"},
        {0x5, "bge"},
        {0x6, "bltu"},
        {0x7, "bgeu"}
    };

    const unordered_map <uint8_t, string> I_jalr_type_table
    {
     // {func3 , "mnemonic"}
        {0x0, "jalr"}
    };





