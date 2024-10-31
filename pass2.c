#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void main() {
    // Variable declarations
    char opcode[20], operand[20], symbol[20], label[20], code[20], mnemonic[25], character, add[20], objectcode[20];
    int flag, flag1, locctr, location, loc;
    FILE *fp1, *fp2, *fp3, *fp4;

    // Open the necessary files
    fp1 = fopen("out3.txt", "r");   // Intermediate file from Pass One
    fp2 = fopen("twoout.txt", "w"); // Output file for object code
    fp3 = fopen("opcode.txt", "r"); // Opcode table
    fp4 = fopen("sym1.txt", "r");   // Symbol table

    // Read the first line from the intermediate file
    fscanf(fp1, "%s%s%s", label, opcode, operand);
    
    // If the first opcode is START, write it to the output file
    if (strcmp(opcode, "START") == 0) {
        fprintf(fp2, "%s\t%s\t%s\n", label, opcode, operand);
        fscanf(fp1, "%d%s%s%s", &locctr, label, opcode, operand); // Get the starting address
    }

    // Loop until the opcode is END
    while (strcmp(opcode, "END") != 0) {
        flag = 0; // Initialize flag to check opcode existence
        fscanf(fp3, "%s%s", code, mnemonic); // Read opcode from opcode table

        // Check if the opcode exists in the opcode table
        while (strcmp(code, "END") != 0) {
            if ((strcmp(opcode, code) == 0) && (strcmp(mnemonic, "*") != 0)) {
                flag = 1; // Opcode found
                break;
            }
            fscanf(fp3, "%s%s", code, mnemonic); // Read next opcode
        }

        // If the opcode was found
        if (flag == 1) {
            flag1 = 0; // Initialize flag for symbol existence
            rewind(fp4); // Rewind symbol table file

            // Check if the operand exists in the symbol table
            while (!feof(fp4)) {
                fscanf(fp4, "%s%d", symbol, &loc); // Read symbol and its location
                if (strcmp(symbol, operand) == 0) {
                    flag1 = 1; // Symbol found
                    break;
                }
            }

            // If symbol was found, create the object code
            if (flag1 == 1) {
                sprintf(add, "%d", loc); // Convert location to string
                strcpy(objectcode, strcat(mnemonic, add)); // Concatenate mnemonic and address
            }
        } 
        // Handle BYTE and WORD opcodes
        else if (strcmp(opcode, "BYTE") == 0 || strcmp(opcode, "WORD") == 0) {
            if ((operand[0] == 'C') || (operand[0] == 'X')) { // Check for character or hexadecimal
                character = operand[2]; // Get the character value
                sprintf(add, "%d", character); // Convert character to string
                strcpy(objectcode, add); // Assign to object code
            } else {
                strcpy(objectcode, add); // Handle other operand types
            }
        } else {
            strcpy(objectcode, "\0"); // No object code generated
        }

        // Write the label, opcode, operand, locctr, and object code to the output file
        fprintf(fp2, "%s\t%s\t%s\t%d\t%s\n", label, opcode, operand, locctr, objectcode);
        fscanf(fp1, "%d%s%s%s", &locctr, label, opcode, operand); // Read next instruction
    }

    // Write the last line (END) to the output file
    fprintf(fp2, "%s\t%s\t%s\t%d\n", label, opcode, operand, locctr);
    
    // Close all opened files
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
}
