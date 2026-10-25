#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

int main()
{
    ifstream opcodeFile("Assignment2.txt");
    ifstream asmFile("program.asm");

    string opcode[50];
    string mnemonic[50];

    int n = 0;

    // Read opcode file
    while (opcodeFile >> opcode[n] >> mnemonic[n])
    {
        string temp;

        // Skip remaining columns of the line
        getline(opcodeFile, temp);

        n++;
    }

    opcodeFile.close();

    // Read assembly file
    string line;

    while (getline(asmFile, line))
    {
        if (line == "")
            continue;

        stringstream ss(line);

        string m, op1, op2;

        ss >> m;

        // Ignore SECTION
        if (m == "SECTION" || m == "section")
            continue;

        // Ignore label
        if (m[m.length() - 1] == ':')
            continue;

        // Remove comma from operands
        ss >> op1 >> op2;

        if (op1 != "")
        {
            if (op1[op1.length() - 1] == ',')
                op1 = op1.substr(0, op1.length() - 1);
        }

        // Check mnemonic
        bool found = true;

        for (int i = 0; i < n; i++)
        {
            if (m == mnemonic[i])
            {
                found = true;
                break;
            }
        }

        cout << "\nMnemonic: " << m;

        if (found)
            cout << "\nStatus: Found";
        else
            cout << "\nStatus: Not Found";

        // Operand 1
        if (op1 != "")
        {
            cout << "\nOperand: " << op1;

            if (op1 == "EAX" || op1 == "EBX" ||
                op1 == "ECX" || op1 == "EDX" ||
                op1 == "ESI" || op1 == "EDI" ||
                op1 == "EBP" || op1 == "ESP")
            {
                cout << "\nType: Register";
            }
            else if (op1[0] == '[')
            {
                cout << "\nType: Memory Operand";
            }
            else if (op1[0] >= '0' && op1[0] <= '9')
            {
                cout << "\nType: Constant";
            }
            else
            {
                cout << "\nType: Symbol";
            }
        }

        // Operand 2
        if (op2 != "")
        {
            cout << "\nOperand: " << op2;

            if (op2 == "EAX" || op2 == "EBX" ||
                op2 == "ECX" || op2 == "EDX" ||
                op2 == "ESI" || op2 == "EDI" ||
                op2 == "EBP" || op2 == "ESP")
            {
                cout << "\nType: Register";
            }
            else if (op2[0] == '[')
            {
                cout << "\nType: Memory Operand";
            }
            else if (op2[0] >= '0' && op2[0] <= '9')
            {
                cout << "\nType: Constant";
            }
            else
            {
                cout << "\nType: Symbol";
            }
        }

        cout << "\n-----------------------------"<<endl;
    }

    asmFile.close();

    return 0;
}
