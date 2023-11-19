#include <iostream>
using namespace std;


#include <iostream>
#include <fstream>
#include <cstdint>

#include <iostream>
#include <fstream>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <cstdint>

using namespace std;


enum OPCODES {
    // R-Type Instructions
    EXT = 0x00,
    
    // Load Instructions
    LW = 0x23,
    LB = 0x20,
    LBU = 0x24,
    LH = 0x21,
    LHU = 0x25,
    LUI = 0x0F,
    
    // Store Instructions
    SW = 0x2B,
    SB = 0x28,
    SH = 0x29,
    
    // Branch Instructions
    BEQ = 0x04,
    BNE = 0x05,
    BLEZ = 0x06,
    BGTZ = 0x07,
    
    // Immediate Instructions
    ADDI = 0x08,
    SLTI = 0x0A,
    SLTIU = 0x0B,
    ANDI = 0x0C,
    ORI = 0x0D,
    XORI = 0x0E,
    
    // Jump Instructions
    J = 0x02,
    JAL = 0x03
};

enum FUNCT {
    ADD = 0x20,
    SUB = 0x22,
    MULT = 0x18,
    DIV = 0x1A,
    AND = 0x24,
    OR = 0x25,
    XOR = 0x26,
    NOR = 0x27,
    SLT = 0x2A,
    JR = 0x08,
    SLL = 0x00,
    SRL = 0x02,
    SRA = 0x03,
    SYSCALL = 0x0C,
    MFHI = 0x10,
    MFLO = 0x12
};


int32_t mem[0x000204c];
int32_t reg[32];
uint32_t pc = 0x00000000;
uint32_t ri = 0x00000000;
uint32_t opcode = 0x00000000;
uint32_t rs = 0x00000000;
uint32_t rt = 0x00000000;
uint32_t rd = 0x00000000;
uint32_t shamt = 0x00000000;
uint32_t funct = 0x00000000;
uint32_t imm = 0x00000000;

void dump_mem(int start, int end, char format) {
    int indice = start;
    for (int i = start; i < start + end; i++) {
        cout << "Address 0x" << hex << indice << ": ";
        if (format == 'h') {
            cout << hex << mem[i] << std::endl;
        } else {
            cout << dec << mem[i] << std::endl;
        }
        indice += 4;
    }
}

void dump_reg(char format, bool showRegs) {

    cout << "--------  Registradores:   --------" << endl;

    cout << "opcode: " << opcode << endl;
    cout << "ri: " << dec << ri << endl;
    cout << "rs: " << rs << endl;
    cout << "rt: " << rt << endl;
    cout << "rd: " << rd << endl;
    cout << "shamt: " << shamt << endl;
    cout << "funct: " << funct << endl;
    cout << "imm: " << imm << endl;
    cout << "PC: 0x" << hex << pc << endl;

    if(showRegs){
        cout << "Banco de registradores:" << endl;
        for (int i = 0; i < 32; i++) {
            cout << "Register $" << dec << i << ": ";
            if (format == 'h') {
                cout << hex << reg[i] << endl;
            } else {
                cout << dec << reg[i] << endl;
            }
        }
    }

    cout << "-------------- Fim  --------------" << endl;
}

void fetch(bool first) {
    if(first) {
        pc = 0x00000000;
    }
    else {
        pc += 1;
    }
    ri = mem[pc];
}

void decode() {
    opcode = (ri & 0xFC000000) >> 26;
    rs = (ri & 0x03E00000) >> 21;
    rt = (ri & 0x001F0000) >> 16;
    rd = (ri & 0x0000F800) >> 11;
    shamt = (ri & 0x000007C0) >> 6;
    funct = (ri & 0x0000003F);
    imm = (ri & 0x0000FFFF);
}


void execute(){
    switch (opcode) {
        case EXT:
            // Handle EXT opcode
            break;
        case LW:{

            cout << "Executando LW" << endl;
            int address = ((reg[rs] + imm) - 0x2000)/4;
            reg[rt] = mem[8192 + address];
            break;
        }

        case LB:
            cout << "Executando LB" << endl;

            reg[rt] = mem[rs + imm];

            break;

        case LBU:
            cout << "Executando LBU" << endl;
            // Handle LBU opcode
            break;
        case LH:
            cout << "Executando LH" << endl;
            // Handle LH opcode
            break;
        case LHU:
            cout << "Executando LHU" << endl;
            // Handle LHU opcode
            break;
        case LUI:
            cout << "Executando LUI" << endl;
            reg[rt] = imm << 16;
            break;
        case SW:
            cout << "Executando SW" << endl;
            // Handle SW opcode
            break;
        case SB:
            cout << "Executando SB" << endl;
            // Handle SB opcode
            break;
        case SH:
            cout << "Executando SH" << endl;
            // Handle SH opcode
            break;
        case BEQ:
            cout << "Executando BEQ" << endl;
            // Handle BEQ opcode
            break;
        case BNE:
            cout << "Executando BNE" << endl;
            // Handle BNE opcode
            break;
        case BLEZ:
            cout << "Executando BLEZ" << endl;
            // Handle BLEZ opcode
            break;
        case BGTZ:
            cout << "Executando BGTZ" << endl;
            // Handle BGTZ opcode
            break;
        case ADDI:
            cout << "Executando ADDI" << endl;

            reg[rt] = reg[rs] + imm;

            break;
        case SLTI:
            cout << "Executando SLTI" << endl;
            // Handle SLTI opcode
            break;
        case SLTIU:
            cout << "Executando SLTIU" << endl;
            // Handle SLTIU opcode
            break;
        case ANDI:
            cout << "Executando ANDI" << endl;
            // Handle ANDI opcode
            break;

        case ORI:
            cout << "Executando ORI" << endl;
            reg[rt] = reg[rs] | imm;
            break;

        case XORI:
            cout << "Executando XORI" << endl;
            // Handle XORI opcode
            break;
        case J:
            cout << "Executando J" << endl;
            // Handle J opcode
            break;
        case JAL:
            cout << "Executando JAL" << endl;
            // Handle JAL opcode
            break;
        default:
            cout << "Executando opcode desconhecido" << endl;
            // Handle unknown opcode
            break;
    }
}


int main() {    


    // TODO: alocação de memória 

    // Lendo o text.bin e alocando em from 0x00000000 to 0x00000044
    ifstream textFile("text.bin", ios::binary);
    if (textFile) {
        textFile.seekg(0, ios::end);
        int fileSize = textFile.tellg();
        textFile.seekg(0, ios::beg);
        textFile.read(reinterpret_cast<char*>(&mem[0]), fileSize);
        textFile.close();
    } else {
        cout << "Erro abrindo o text bin" << endl;
        return 1;
    }

    // Read data.bin e alocando em memory from 0x0000200 to 0x0000204c
    ifstream dataFile("data.bin", ios::binary);
    if (dataFile) {
        dataFile.read(reinterpret_cast<char*>(&mem[0x2000]), 0x4d);
        dataFile.close();
    } else {
        cout << "Erro abrindo o data bin" << endl;
        return 1;
    }


    fetch(true);
    decode();
    execute();
    dump_reg('h', true);

    fetch(false);
    decode();
    execute();
    dump_reg('h', true);
    
    
    fetch(false);
    decode();
    execute();
    dump_reg('h', true);

    fetch(false);
    decode();
    dump_reg('h', true);
    execute();

    // fetch(false);
    // decode();
    // dump_reg('h', true);
    // execute();

    return 0;
}
