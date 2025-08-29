#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <map>
using namespace std;

//00 LDA 80 01 SUB 10 02 STA 80 03 BRZ 05 04 BRA 00 05 HLT 10 DAT 10 80 DAT 5000 LDA 80

//=== CPU simulation ===//
struct CPU {
    int PC = 0;   // Program Counter: 00, 01, 02, 80 ...
    int ACC = 0;  // Accumulator: 5000, 4990, ... 
    bool halted = false;
};

struct Instruction {
    string opcode;
    int operand;
};

//=== RAM and helper functions ===//
map<int, Instruction> RAM; // Instruction memory
map<int, int> DATA;        // Data memory

void loadProgram() {
    // Program memory
    RAM[0] = { "LDA", 80 };
    RAM[1] = { "SUB", 10 };
    RAM[2] = { "STA", 80 };
    RAM[3] = { "BRZ", 5 };
    RAM[4] = { "BRA", 0 };
    RAM[5] = { "HLT", 0 };

    // Data memory
    DATA[10] = 10;
    DATA[80] = 50; //5000
}

void printState(const CPU& cpu) {
    cout << "PC=" << setw(2) << cpu.PC
        << " ACC=" << setw(6) << cpu.ACC
        << endl;
}

void execute(CPU& cpu) {
    while (!cpu.halted) {
        if (RAM.find(cpu.PC) == RAM.end()) {
            // Example: cpu.PC == 6;
            cerr << "Invalid instruction at " << cpu.PC << endl;
            break;
        }

        Instruction instr = RAM[cpu.PC];
        cout << "Executing " << instr.opcode << " " << instr.operand << " ... ";

        if (instr.opcode == "LDA") {
            cpu.ACC = DATA[instr.operand];
            cpu.PC++;
        }
        else if (instr.opcode == "SUB") {
            cpu.ACC -= DATA[instr.operand];
            cpu.PC++;
        }
        else if (instr.opcode == "STA") {
            DATA[instr.operand] = cpu.ACC;
            cpu.PC++;
        }
        else if (instr.opcode == "BRZ") {
            if (cpu.ACC == 0) cpu.PC = instr.operand;
            else cpu.PC++;
        }
        else if (instr.opcode == "BRA") {
            cpu.PC = instr.operand;
        }
        else if (instr.opcode == "HLT") {
            cpu.halted = true;
        }
        else {
            // Example: instr.opcode == "GGG";
            cerr << "Unknown opcode: " << instr.opcode << endl;
            break;
        }
        cout << "done.\n";
        printState(cpu);
    }
}

int main() {
    cout << "=== CPU - RAM Simulation ===\n";

    // Testcase #1: original program
    cout << "\n--- Testcase 1 ---\n";
    CPU cpu1;
    loadProgram();
    execute(cpu1);

    // Testcase #2: different initial value
    cout << "\n--- Testcase 2 ---\n";
    CPU cpu2;
    loadProgram();
    DATA[80] = 20;  // different starting value
    execute(cpu2);

    // Testcase #3: zero start
    cout << "\n--- Testcase 3 ---\n";
    CPU cpu3;
    loadProgram();
    DATA[80] = 10; // value equal to subtractor
    execute(cpu3);

    cout << "\nFinal RAM state (DATA):\n";
    for (auto& x : DATA) {
        cout << setw(2) << x.first << " : " << x.second << endl;
    }
    return 0;
}

