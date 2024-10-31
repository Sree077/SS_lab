#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *inputFile, *opcodeFile, *outputFile, *symbolTableFile;
    char label[30], opcode[30], operand[30];
    char opcodeFileOpcode[30], opcodeFileSize[30];
    int locctr = 0, foundOpcode, lineAddress;

    // Open all necessary files
    inputFile = fopen("input.txt", "r");
    opcodeFile = fopen("opcode.txt", "r");
    outputFile = fopen("out1.txt", "w");
    symbolTableFile = fopen("sym1.txt", "w");

    if (!inputFile || !opcodeFile || !outputFile || !symbolTableFile) {
        printf("Error opening one of the files.\n");
        return 1;
    }

    // Read input file line by line
    while (fscanf(inputFile, "%s %s %s", label, opcode, operand) != EOF) {
        // START directive
        if (strcmp(opcode, "START") == 0) {
            locctr = atoi(operand);  // Initialize locctr
            fprintf(outputFile, "%s %s %s\n", label, opcode, operand);  // Write START line
        } else if (strcmp(opcode, "END") == 0) {
            fprintf(outputFile, "%04X %s %s %s\n", locctr, label, opcode, operand);
            break;
        } else {
            foundOpcode = 0;
            rewind(opcodeFile);  // Rewind to start searching opcodes again

            // Search for opcode in opcode file
            while (fscanf(opcodeFile, "%s %s", opcodeFileOpcode, opcodeFileSize) != EOF) {
                if (strcmp(opcode, opcodeFileOpcode) == 0) {
                    foundOpcode = 1;
                    fprintf(outputFile, "%04X %s %s %s\n", locctr, label, opcode, operand);
                    locctr += atoi(opcodeFileSize);  // Increment locctr by opcode size
                    break;
                }
            }

            // If opcode not found, it's a storage directive
            if (!foundOpcode) {
                // Symbol definitions with memory allocation
                if (strcmp(opcode, "RESW") == 0) {
                    fprintf(outputFile, "%04X %s %s %s\n", locctr, label, opcode, operand);
                    fprintf(symbolTableFile, "%04X %s\n", locctr, label);
                    locctr += 3 * atoi(operand);  // Allocate words
                } else if (strcmp(opcode, "WORD") == 0) {
                    fprintf(outputFile, "%04X %s %s %s\n", locctr, label, opcode, operand);
                    fprintf(symbolTableFile, "%04X %s\n", locctr, label);
                    locctr += 3;  // Allocate 1 word
                } else if (strcmp(opcode, "BYTE") == 0) {
                    fprintf(outputFile, "%04X %s %s %s\n", locctr, label, opcode, operand);
                    fprintf(symbolTableFile, "%04X %s\n", locctr, label);
                    locctr += 1;  // Allocate 1 byte
                } else if (strcmp(opcode, "RESB") == 0) {
                    fprintf(outputFile, "%04X %s %s %s\n", locctr, label, opcode, operand);
                    fprintf(symbolTableFile, "%04X %s\n", locctr, label);
                    locctr += atoi(operand);  // Allocate bytes
                }
            }
        }
    }

    // Close all files
    fclose(inputFile);
    fclose(opcodeFile);
    fclose(outputFile);
    fclose(symbolTableFile);

    printf("Pass One completed. Output written to out1.txt and sym1.txt.\n");

    return 0;
}
