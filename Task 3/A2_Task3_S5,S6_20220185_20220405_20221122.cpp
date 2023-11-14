// File: A2_Task3_S5,S6_20220185_20220405_20221122.cpp
// Author 1: Abdallah Mohamed / 20220185
// Author 2: Yousef Mohamed / 20220405
// Author 3: Mohamed Sabry / 20221122
// Section: S5/S6
// TA: Nardeen/Maya



#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <bitset>

using namespace std;

class MachineSimulator {

private:
    // Data members to store the state of the machine
    vector<unsigned int> registers, memory;
    vector<unsigned int> instruction;

    unsigned int reg, address, instruct, operand, pc,
    screen = 0;
    // Function to execute the instruction at the given program counter
    int executeInstruct(unsigned int pc) {
        // Extract opcode and register from memory
        instruct = (memory[pc] >> 4) & 0xF;
        reg = (memory[pc] & 0xF);

        // Populate the instruction vector with opcode, register, and operand
        instruction.clear();
        instruction.push_back(instruct);
        instruction.push_back(reg);
        instruction.push_back(memory[pc + 1]);

        // Execute the instruction based on the opcode
        switch (instruct) {
        default:
            cout << "invalid operation!\n";
            break;
        case 1:
            loadRegister();
            break;
        case 2:
            loadPattern();
            break;
        case 3:
            storeMemory();
            break;
        case 4:
            move();
            break;
        case 5:
            Add_twos();
            break;
        case 11:
            Jump();
            break;
        case 12:
            return 0;
            break;
        }

        return 1;
    }

    // Function to load a register with the content of a memory cell
    void loadRegister() {
        address = memory[pc + 1];
        registers[reg] = memory[address];
    }

    // Function to load a register with a bit pattern
    void loadPattern() {
        registers[reg] = memory[pc + 1];
    }

    // Function to store the content of a register in a memory cell
    void storeMemory() {

        address = memory[pc + 1];
        unsigned int pattern = registers[reg];
        memory[address] = pattern;


        if (address == 0) {
         
            screen = pattern;
        }
    
    }

    // Function to move the content of one register to another
    void move() {
        reg = (memory[pc + 1] >> 4) & 0xF;
        unsigned int reg2 = memory[pc + 1] & 0xF;

        registers[reg2] = registers[reg];
    }

    // Function to add two binary numbers stored in registers
    void Add_twos() {
        unsigned int reg_1 = (memory[pc + 1] >> 4) & 0xF;
        unsigned int reg_2 = memory[pc + 1] & 0xF;

        unsigned int hex_num1 = registers[reg_1];
        unsigned int hex_num2 = registers[reg_2];

        // Convert to binary and perform binary addition
        bitset<8> binaryNum1(hex_num1);
        bitset<8> binaryNum2(hex_num2);
        bitset<8> sum = binaryNum1.to_ulong() + binaryNum2.to_ulong();

        // Convert back to hex and store the result in a register
        unsigned int hexSum = sum.to_ulong();
        registers[reg] = hexSum;
    }

    // Function to jump to an instruction based on a condition
    void Jump() {
        if (registers[0] == registers[reg]) {
            address = memory[pc + 1];
            pc = address;
        }
    }

    // Function to print a human-readable description of the instruction
    void Decode() {
        unsigned int r1 = (instruction[2] >> 4) & 0xF;
        unsigned int r2 = (instruction[2]) & 0xF;

        switch (instruction[0]) {
        case 1:
            cout << "load the register " << instruction[1]
                 << " with the bit pattern in memory address " << instruction[2];
            cout << endl;
            break;
        case 2:
            cout << "load the register " << instruction[1] << " with the bit pattern " << instruction[2];
            cout << endl;
            break;
        case 3:
            cout << "store the bit pattern found in register " << instruction[1]
                 << " in the memory cell whose address is " << instruction[2];
            cout << endl;
            break;
        case 4:
            cout << "move the bit pattern found in register " << r1;
            cout << " to register " << r2;
            cout << endl;
            break;
        case 5:
            cout << "add the bit patterns in register " << r1 << " and " << r2
                 << " and store the result in register " << instruction[1];
            cout << endl;
            break;
        case 11:
            cout << "jump to instruction at memory address " << instruction[2]
                 << " if the bit pattern in register " << instruction[1]
                 << " equal to the bit pattern in register 0\n";
            break;
        case 12:
            cout << "end program\n";
            break;
        }
    }

  // Function to validate the content of the input file
bool validateFileContent(const string& file) {
    ifstream inputFile(file + ".txt");
    if (!inputFile) {
        cerr << "Error opening file!" << endl;
        return false;
    }

    int lineCount = 0;
    string line;

    while (getline(inputFile, line)) {
        lineCount++;

        istringstream iss(line);
        string hexNum;

        // Check if each line has three hex numbers separated by space
        for (int i = 0; i < 3; ++i) {
            if (!(iss >> hexNum) || hexNum.substr(0, 2) != "0x") {
                cerr << "Error in line " << lineCount << ": Invalid hex format!" << endl;
                return false;
            }

            // Check if the third hex number has valid length (2 or 4 characters)
            if (i == 2 && hexNum.length() != 4 && hexNum.length() != 3) {
                cerr << "Error in line " << lineCount << ": Third hex number must be 2 bytes (e.g., 0xAA) or 1 byte (e.g., 0xA)!" << endl;
                return false;
            }

            try {
                stoul(hexNum, nullptr, 16);  // Try to convert hexNum to an unsigned int
            } catch (const invalid_argument& e) {
                cerr << "Error in line " << lineCount << ": Invalid hex number!" << endl;
                return false;
            } catch (const out_of_range& e) {
                cerr << "Error in line " << lineCount << ": Hex number out of range!" << endl;
                return false;
            }
        }
    }

    inputFile.close();
    return true;
}

public:

    // Constructor to initialize the machine state
    MachineSimulator() {
        registers.resize(16, 0);
        memory.resize(256, 0);
        pc = 0; // Program counter
    }

    // Function to run the machine with instructions from a file
    bool runProgram(string file) {
        // Validate the content of the input file
        if (!validateFileContent(file)) {
            cerr << "Invalid file content!" << endl;
            return false;
        }

        // Open the input file
        ifstream inputFile;
        inputFile.open(file + ".txt");

        unsigned int h;
        address = 0;
        int byte_count = 1;
        unsigned int num = 0x0;
        int instruct_count = 1;

        if (!inputFile) {
            cerr << "Error opening file!" << endl;
            return false;
        }

        // Clear existing instructions
        instruction.clear();

        // Read instructions from the file
        while (inputFile >> hex >> h) {
            if (h > 0xF && h <= 0xFF || instruct_count % 3 == 0) {
                // If the instruction is complete, store it in memory
                memory[address] = h;
                address++;
                byte_count = 1;
                num = 0x0;
            } else {
                // If the instruction is not complete, combine it with the next hex number
                memory[address] = (num << 4) | h;
                if (byte_count == 2) {
                    byte_count = 1;
                    num = 0x0;
                    address++;
                } else {
                    num = h;
                    byte_count++;
                }
            }
            // Populate the instruction vector
            instruct_count++;
        }

        inputFile.close();

        // Reset the program counter
        pc = 0;

        return true;
    }

    // Function to display a menu for user interaction
    void Menu() {
        bool state = true;
        string filename;
        int operation;

        cout << "type file name to run the program: ";
        cin >> filename;

        // Run the program with the specified file
        state = runProgram(filename);

        cout << endl;

        while (state) {
            // Display menu options
            cout << "1. Fetch and execute\n"
                 << "2. decode\n"
                 << "3. display status\n"
                 << "4. load a new File\n"
                 << "5. exit\n";

            cin >> operation;

            switch (operation) {
            case 1:
                // Execute the next instruction and increment the program counter
                executeInstruct(pc);
                pc += 2;
                break;
            case 2:
                // Decode and print the current instruction
                Decode();
                break;
            case 3:
                // Display the current status of the machine
                print_status();
                break;
            case 4:
                // Clear memory and registers, and load a new file
                memory.clear();
                registers.clear();
                registers.resize(16, 0);
                memory.resize(256, 0);
                pc = 0; // Program counter
                Menu();
                state = false;
                break;
            case 5:
                // Exit the program
                state = false;
                break;
            default:
                cout << "invalid number please choose again!";
                break;
            }
        }
    }

    // Function to display the current status of the machine
    void print_status() {
        // Display program counter and instruction register
        cout << "program counter: " << setw(2) << setfill('0') << hex << pc
             << "           " << "Instruction Register :  ";
        for (auto it : instruction) {

            cout << hex << it;
        
        }

        cout << "           " << "Screen: " << hex << screen;

        cout << endl;

        // Display register contents
        unsigned int add = 0;
        cout << "Registers : \n"
             << "-----------------------------------------------\n";
        for (auto it : registers) {
            cout << "address: " << hex << add;
            cout << " content: " << setw(2) << setfill('0') << hex << it;
            cout << endl;
            add++;
        }

        cout << endl;

        // Display memory contents
        add = 0;
        cout << "Main memory\n"
             << "-----------------------------------------------\n";
        for (auto it : memory) {
            cout << "address: " << setw(2) << setfill('0') << hex << add;
            cout << " content: " << setw(2) << setfill('0') << hex << it;
            cout << endl;
            add++;
        }
    }
};

int main() {
    // Create an instance of the MachineSimulator and run the menu
    MachineSimulator m;
    m.Menu();
    return 0;
}
