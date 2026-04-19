# Instruction Types

## R-instruction
- Register only  
- OPCODE REG REG (REG)  
- SET, NOT, AND, OR, XOR, STL, STR, RTL, RTR, ADD, SUB, MUL, DIV, MOD, CMP  

## I-instruction
- Register + Immediate  
- OPCODE REG (REG) IMM  
- SET, NOT, AND, OR, XOR, STL, STR, RTL, RTR, ADD, SUB, MUL, DIV, MOD, CMP

## M-instruction
- Memory Management  
- OPCODE REG/ADR ADR/REG  
- LOAD, SEND  

## J-instruction
- Jumping and Branching  
- OPCODE @LABEL
- WEQ, WGT, WLT, WCY, WOV, WDZ, GOTO, CAL  

## S-instruction
- Single Register Operation  
- OPCODE REG  
- PUSH, POP, PRINT(VM only), PRINTC(VM only)  

## N-instruction
- No Operands  
- OPCODE  
- RET, END, CLR  


# Instruction Opcodes

## memory and registers
LOAD  
SEND  
SET  

## bitwise
NOT  
AND  
OR  
XOR  

## shift and rotation
STL  
STR  
RTL  
RTR  

## arithmetic
NEG  
ADD  
SUB  
MUL  
DIV  
MOD  

## comparison and branching
CMP  
GOTO  
WEQ  
WGT  
WLT  
WCY  
WOV  
WDZ  

## stacks and sub-routines
CAL  
RET  
PUSH  
POP  

## i/o
PRINT  
PRINTC  

## misc. and debugging
END  
CLR  