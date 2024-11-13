#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    
    FILE *input,*output;

    input = fopen(argv[1],"r");
    output = fopen("out.hex","w");

    if( input == NULL || output == NULL ) {
        fprintf(stderr,"Couldn't access file\n");
        return -1;
    }

    char buffer[100], instruction[100];
    uint32_t hex, opcode, rd, rs1, rs2, funct3, funct7,imm, imm12, imm31_12, imm11_5, imm10_5, imm11,  imm4_1, imm4_0,imm10_1, imm19_12, imm20; 

    while(fgets(buffer,100,input) !=NULL){
        sscanf(buffer,"%s",instruction);

        if(!strcmp(instruction, "addi")){
            opcode=19;
            funct3=0;
            sscanf(buffer,"%*s x%d, x%d, %d", &rd, &rs1, &imm12);

            hex= opcode |(rd << 7)|(funct3 << 12)|(rs1 << 15)|(imm12 << 20);

        }

        // ADD 
        else if (!strcmp(instruction, "add")) {
            opcode = 0x33; 
            funct3 = 0x0;
            funct7 = 0x00; 
            sscanf(buffer, "%*s x%d, x%d, x%d", &rd, &rs1, &rs2);
            hex = (opcode) | (rd << 7) | (funct3 << 12) | (rs1 << 15) | (rs2 << 20) | (funct7 << 25);
        }

        // SUB
        else if (!strcmp(instruction, "sub")) {
            opcode = 0x33;
            funct3 = 0x0; 
            funct7 = 0x20; 
            sscanf(buffer, "%*s x%d, x%d, x%d", &rd, &rs1, &rs2);
            hex = (opcode) | (rd << 7) | (funct3 << 12) | (rs1 << 15) | (rs2 << 20) | (funct7 << 25);
        }

        // LUI
        else if (!strcmp(instruction, "lui")) {
            opcode = 0x37; // LUI için opcode
            sscanf(buffer, "%*s x%d, %x", &rd, &imm31_12); 
            hex = opcode | (rd << 7) | (imm31_12 << 12); 
        }
            
        // AND
        else if (!strcmp(instruction, "and")) {
            opcode = 0x33; 
            funct3 = 0x7;  
            funct7 = 0x00; 
            sscanf(buffer, "%*s x%d, x%d, x%d", &rd, &rs1, &rs2);
            hex = (opcode) | (rd << 7) | (funct3 << 12) | (rs1 << 15) | (rs2 << 20) | (funct7 << 25);
        }

        // ANDI
        else if (!strcmp(instruction, "andi")) {
            opcode = 0x13; 
            funct3 = 0x7;  
            sscanf(buffer, "%*s x%d, x%d, %d", &rd, &rs1, &imm12);
            if (imm12 & 0x800) { // If bit 12 of imm12 is 1 (negative number)
                imm12 |= 0xfffff000; // Fill upper bits with 1
            } else {
                imm12 &= 0xfff; // Fill upper bits with 0 (needed for positive number)
            }
            hex = (opcode) | (rd << 7) | (funct3 << 12) | (rs1 << 15) | (imm12 << 20);
        }

        // OR
        else if (!strcmp(instruction, "or")) {
            opcode = 0x33; 
            funct3 = 0x6;  
            funct7 = 0x00; 
            sscanf(buffer, "%*s x%d, x%d, x%d", &rd, &rs1, &rs2);
            hex = (opcode) | (rd << 7) | (funct3 << 12) | (rs1 << 15) | (rs2 << 20) | (funct7 << 25);
        }

        //ORI
        else if (!strcmp(instruction, "ori")) {
            opcode = 0x13; 
            funct3 = 0x6;  
            sscanf(buffer, "%*s x%d, x%d, %d", &rd, &rs1, &imm12);
            hex = (opcode) | (rd << 7) | (funct3 << 12) | (rs1 << 15) | (imm12 << 20);
        }

        //XOR 
        else if (!strcmp(instruction, "xor")) {
            opcode = 0x33; 
            funct3 = 0x4;  
            funct7 = 0x00; 
            sscanf(buffer, "%*s x%d, x%d, x%d", &rd, &rs1, &rs2);
            hex = (opcode) | (rd << 7) | (funct3 << 12) | (rs1 << 15) | (rs2 << 20) | (funct7 << 25);
        }

        //XORI
        else if (!strcmp(instruction, "xori")) {
            opcode = 0x13; 
            funct3 = 0x4;  
            sscanf(buffer, "%*s x%d, x%d, %d", &rd, &rs1, &imm12);
            hex = (opcode) | (rd << 7) | (funct3 << 12) | (rs1 << 15) | (imm12 << 20);
        }

        //SLL
        else if (!strcmp(instruction, "sll")) {
            opcode = 0x33; 
            funct3 = 0x1;  
            funct7 = 0x00; 
            sscanf(buffer, "%*s x%d, x%d, x%d", &rd, &rs1, &rs2);
            hex = (opcode) | (rd << 7) | (funct3 << 12) | (rs1 << 15) | (rs2 << 20) | (funct7 << 25);
        }

        //SLLI
        else if (!strcmp(instruction, "slli")) {
            opcode = 0x13; 
            funct3 = 0x1;  
            sscanf(buffer, "%*s x%d, x%d, %d", &rd, &rs1, &imm12);
            //Limit the imm12 value since the shift amount is 5 bits
            imm12 &= 0x1F; // Maximum shift amount for 32-bit
            hex = (opcode) | (rd << 7) | (funct3 << 12) | (rs1 << 15) | (imm12 << 20);
        }

        //SRL
        else if (!strcmp(instruction, "srl")) {
            opcode = 0x33; 
            funct3 = 0x5;  
            funct7 = 0x00; 
            sscanf(buffer, "%*s x%d, x%d, x%d", &rd, &rs1, &rs2);
            hex = (opcode) | (rd << 7) | (funct3 << 12) | (rs1 << 15) | (rs2 << 20) | (funct7 << 25);
        }

        //SRLI
        else if (!strcmp(instruction, "srli")) {
            opcode = 0x13; 
            funct3 = 0x5;  
            sscanf(buffer, "%*s x%d, x%d, %d", &rd, &rs1, &imm12);
            imm12 &= 0x1F; 
            hex = (opcode) | (rd << 7) | (funct3 << 12) | (rs1 << 15) | (imm12 << 20);
        }

        //SLT
        else if (!strcmp(instruction, "slt")) {
            opcode = 0x33; 
            funct3 = 0x2;  
            funct7 = 0x00; 
            sscanf(buffer, "%*s x%d, x%d, x%d", &rd, &rs1, &rs2);
            hex = (opcode) | (rd << 7) | (funct3 << 12) | (rs1 << 15) | (rs2 << 20) | (funct7 << 25);
        }

        //SLTI
        else if (!strcmp(instruction, "slti")) {
            opcode = 0x13; 
            funct3 = 0x2;  
            sscanf(buffer, "%*s x%d, x%d, %d", &rd, &rs1, &imm12);
            hex = (opcode) | (rd << 7) | (funct3 << 12) | (rs1 << 15) | (imm12 << 20);
        }

        //LW
        else if (!strcmp(instruction, "lw")) {
            opcode = 0x03; 
            funct3 = 0x2;  
            sscanf(buffer, "%*s x%d, x%d ,%d", &rd, &rs1, &imm12);
            hex = (opcode) | (rd << 7) | (funct3 << 12) | (rs1 << 15) | (imm12 << 20);
        }

        //LB
        else if (!strcmp(instruction, "lb")) {
            opcode = 0x03; 
            funct3 = 0x0;  
            sscanf(buffer, "%*s x%d, x%d, %d", &rd, &rs1, &imm12);
            hex = (opcode) | (rd << 7) | (funct3 << 12) | (rs1 << 15) | (imm12 << 20);
        }

        // LH
        else if (!strcmp(instruction, "lh")) {
            opcode = 0x03; 
            funct3 = 0x1;  
            sscanf(buffer, "%*s x%d, x%d, %d", &rd, &rs1, &imm12);
            // Do sign expansion for imm12 value
            hex = (opcode) | (rd << 7) | (funct3 << 12) | (rs1 << 15) | (imm12 << 20);
        }

        // SW
        else if (!strcmp(instruction, "sw")) {
            opcode = 0x23; 
            funct3 = 0x2;  
            sscanf(buffer, "%*s x%d, x%d, %d", &rs2, &rs1, &imm);
            imm11_5 = (imm >> 5) & 0x7F;
            imm4_0 = imm & 0x1F;
            hex = opcode | (imm4_0 << 7) | (funct3 << 12) | (rs1 << 15) | (rs2 << 20) | (imm11_5 << 25);
        }

        // SB
        else if (!strcmp(instruction, "sb")) {
            opcode = 0x23; 
            funct3 = 0x0;  
            sscanf(buffer, "%*s x%d, x%d, %d", &rs2, &rs1, &imm);
            imm11_5 = (imm >> 5) & 0x7F;
            imm4_0 = imm & 0x1F;
            hex = opcode | (imm4_0 << 7) | (funct3 << 12) | (rs1 << 15) | (rs2 << 20) | (imm11_5 << 25);
        }

        // SH
        else if (!strcmp(instruction, "sh")) {
            opcode = 0x23; 
            funct3 = 0x1;  
            sscanf(buffer, "%*s x%d, x%d, %d", &rs2, &rs1, &imm);
            imm11_5 = (imm >> 5) & 0x7F;
            imm4_0 = imm & 0x1F;
            hex = opcode | (imm4_0 << 7) | (funct3 << 12) | (rs1 << 15) | (rs2 << 20) | (imm11_5 << 25);
        }

        // BEQ
        else if (!strcmp(instruction, "beq")) {
            opcode = 0x63; 
            funct3 = 0x0;  
            sscanf(buffer, "%*s x%d, x%d, %d", &rs1, &rs2, &imm);
            imm12 = (imm >> 12) & 0x1;
            imm10_5 = (imm >> 5) & 0x3F;
            imm4_1 = (imm >> 1) & 0xF;
            imm11 = (imm >> 11) & 0x1;
            hex = opcode | (funct3 << 12) | (rs1 << 15) | (rs2 << 20) | (imm4_1 << 8) | (imm10_5 << 25) | (imm11 << 7) | (imm12 << 31);
        }

        // BNE
        else if (!strcmp(instruction, "bne")) {
            opcode = 0x63; 
            funct3 = 0x1;  
            sscanf(buffer, "%*s x%d, x%d, %d", &rs1, &rs2, &imm);
            imm12 = (imm >> 12) & 0x1;
            imm10_5 = (imm >> 5) & 0x3F;
            imm4_1 = (imm >> 1) & 0xF;
            imm11 = (imm >> 11) & 0x1;
            hex = opcode | (funct3 << 12) | (rs1 << 15) | (rs2 << 20) | (imm4_1 << 8) | (imm10_5 << 25) | (imm11 << 7) | (imm12 << 31);
        }

        // BLT
        else if (!strcmp(instruction, "blt")) {
            opcode = 0x63; 
            funct3 = 0x4;  
            sscanf(buffer, "%*s x%d, x%d, %d", &rs1, &rs2, &imm);
            imm12 = (imm >> 12) & 0x1;
            imm10_5 = (imm >> 5) & 0x3F;
            imm4_1 = (imm >> 1) & 0xF;
            imm11 = (imm >> 11) & 0x1;
            hex = opcode | (funct3 << 12) | (rs1 << 15) | (rs2 << 20) | (imm4_1 << 8) | (imm10_5 << 25) | (imm11 << 7) | (imm12 << 31);
        }

        // BGE
        else if (!strcmp(instruction, "bge")) {
            opcode = 0x63; 
            funct3 = 0x5;  
            sscanf(buffer, "%*s x%d, x%d, %d", &rs1, &rs2, &imm);
            imm12 = (imm >> 12) & 0x1;
            imm10_5 = (imm >> 5) & 0x3F;
            imm4_1 = (imm >> 1) & 0xF;
            imm11 = (imm >> 11) & 0x1;
            hex = opcode | (funct3 << 12) | (rs1 << 15) | (rs2 << 20) | (imm4_1 << 8) | (imm10_5 << 25) | (imm11 << 7) | (imm12 << 31);
        }

        // JAL
        else if (!strcmp(instruction, "jal")) {
            opcode = 0x6F; 
            sscanf(buffer, "%*s x%d, %d", &rd, &imm);
            imm20 = (imm >> 20) & 0x1;
            imm10_1 = (imm >> 1) & 0x3FF;
            imm11 = (imm >> 11) & 0x1;
            imm19_12 = (imm >> 12) & 0xFF;
            hex = opcode |(rd << 7) | (imm10_1 << 21) | (imm11 << 20) |  (imm19_12 << 12) | (imm20 << 31);            
        }

        // ECALL
        else if (!strcmp(instruction, "ecall")) {
            opcode = 0x73; 
            hex = opcode; 
        }

        fprintf(output, "%08x\n", hex);

    }

    //you need to implement a function that reads and parses the content of the input file.
    //each line of the input file would have a RISC-V assembly instruction, and you should
    //convert it to machine code encoded in HEX.
    //Then, you should add each HEX into an output file.

    fclose(input);
    fclose(output);

    return 0;

}
