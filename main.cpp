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


int32_t mem[4096];
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

            
            int address = ((reg[rs] + imm))/4; // aqui dividimos por 4 pois o endereço é em bytes e o vetor é em int32_t 
            reg[rt] = mem[address];
            break;
        }

        case LB:{
            cout << "Executando LB" << endl;

            int8_t *byteP = (int8_t*) mem;


            int address = ((reg[rs] + imm));

            if (byteP[address] < 0) {
                int mask = (-1) ^ (255);   
                reg[rt] = mask | byteP[address] ;
            }
            else{
                reg[rt] = byteP[address]; // garante que os bits vao ser 0 depois do 8
            }

            break;

        }

        case LBU:{
            cout << "Executando LBU" << endl;

            int address = ((reg[rs] + imm))/4;

            reg[rt] = mem[address];

            break;
        }
        
        case LH:{

            cout << "Executando LH" << endl;
            int16_t *halfP = (int16_t*) mem;
            
            int address = ((reg[rs] + imm))/2;

            if (halfP[address] < 0) {
                int mask = ~(65535);                    
                reg[rt] = mask | halfP[address];
            } else 
                reg[rt] = halfP[address];   


            break;
        }

        case LHU:{
            int16_t *halfP = (int16_t*) mem;

            cout << "Executando LHU" << endl;
            cout << mem[(reg[rs] + imm)/2] << endl;
            cout << halfP[(reg[rs] + imm)/2] << endl;

            reg[rt] = halfP[(reg[rs] + imm)/2] & 65535;               

            break;
        }


        case LUI:
            cout << "Executando LUI" << endl;

            reg[rt] = imm << 16;
            
            break;


        case SW:{
            cout << "Executando SW" << endl;

            int adress = (reg[rs] + imm)/4;
            cout << adress << endl;
            mem[adress] = reg[rt];        
            
            break;
        }


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

            if(reg[rs] == reg[rt]){
                pc = pc + imm;
            }
            else{
                pc++;
            }

            ri = mem[pc];


            break;
        case BNE:
            cout << "Executando BNE" << endl;
            // Handle BNE opcode

            if(reg[rs] != reg[rt]){
                pc = pc + imm;
            }
            else{
                pc++;
            }

            ri = mem[pc];

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
            
            if(reg[rs] < imm){
                reg[rt] = 1;
            }
            else{
                reg[rt] = 0;
            }
            break;
        case SLTIU:
            cout << "Executando SLTIU" << endl;
            // Handle SLTIU opcode


            break;
        case ANDI:
            cout << "Executando ANDI" << endl;
            // Handle ANDI opcode

            reg[rt] = reg[rs] & imm;

            break;

        case ORI:
            cout << "Executando ORI" << endl;
            reg[rt] = reg[rs] | imm;
            break;

        case XORI:
            cout << "Executando XORI" << endl;

            reg[rt] = reg[rs] ^ imm;

            break;
        case J:
            cout << "Executando J" << endl;
            // Handle J opcode

            pc = 0x00000000;
            pc += imm;
            ri = mem[pc];
            break;

            break;
        case JAL:
            cout << "Executando JAL" << endl;
            // Handle JAL opcode

            reg[31] = pc + 1;

            break;
        default:
            cout << "Executando opcode desconhecido" << endl;
            // Handle unknown opcode

            
            break;
    }
}


int main() {    

    cout << 0x2000/4 << endl;
    // TODO: alocação de memória 

    // Lendo o text.bin e alocando em from 0x00000000 to 0x00000044
    ifstream textFile("text.bin", ios::binary);
    if (textFile) {
        textFile.seekg(0, ios::end);
        int fileSize = textFile.tellg();
        textFile.seekg(0, ios::beg);
        textFile.read(reinterpret_cast<char*>(&mem[0]), 0x2000/4);
        textFile.close();
    } else {
        cout << "Erro abrindo o text bin" << endl;
        return 1;
    }

    // Read data.bin e alocando em memory from 0x0002000 to 4096
    ifstream dataFile("data.bin", ios::binary);
    if (dataFile) {
        dataFile.read(reinterpret_cast<char*>(&mem[(0x2000/4)]), 4096);
        dataFile.close();
    } else {
        cout << "Erro abrindo o data bin" << endl;
        return 1;
    }


    fetch(true);
    decode();
    execute();
    dump_reg('h', true);


    for(int i = 0; i < 6; i++){

    fetch(false);
    decode();
    execute();
    dump_reg('h', true);
    dump_mem(0x2000/4, 6, 'h');
    
    }

    
    
    // fetch(false);
    // decode();
    // execute();
    // dump_reg('h', true);

    // fetch(false);
    // decode();
    // execute();
    // dump_reg('h', true);



    // fetch(false);
    // decode();
    // dump_reg('h', true);
    // execute();

    return 0;
}
