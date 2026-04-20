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

# Instruction Binary Format

Instruction Length - 32 bits (4 bytes); Word Length - 16 bits (2 bytes)
Opcode - 3 bits for type + 5 bits for instruction (8 bits total)
- R-type: (opcode 8) (dest 4 | src1 4)   (src2 4 | unused 4) (unused 8)  
- I-type: (opcode 8) (dest 4 | src  4)   (imm high 8)        (imm low 8)  
- M-type: (opcode 8) (reg  4 | unused 4) (addr high 8)       (addr low 8)  
- J-type: (opcode 8) (unused 8)          (addr high 8)       (addr low 8)
- S-type: (opcode 8) (reg  4 | unused 4) (unused 8)          (unused 8)  
- N-type: (opcode 8) (unused 8)          (unused 8)          (unused 8)  

# Instruction Opcodes

## memory and registers
LOAD Rdst, ADRsrc  
SEND Rsrc, ADRdst  
SET  Rdst, Rsrc  

## bitwise
NOT  Rdst, Rax  
AND  Rdst, Rax, Rbx  
OR   Rdst, Rax, Rbx  
XOR  Rdst, Rax, Rbx  

## shift and rotation
STL  Rdst, Rax  
STR  Rdst, Rax  
RTL  Rdst, Rax  
RTR  Rdst, Rax  

## arithmetic
NEG  Rdst, Rax  
ADD  Rdst, Rax, Rbx  
SUB  Rdst, Rax, Rbx  
MUL  Rdst, Rax, Rbx  
DIV  Rdst, Rax, Rbx  
MOD  Rdst, Rax, Rbx  

## comparison and branching
CMP  Rax, Rbx  
GOTO @LBL  
WEQ  @LBL  
WGT  @LBL  
WLT  @LBL  
WCY  @LBL  
WOV  @LBL  
WDZ  @LBL  

## stacks and sub-routines
CAL  @LBL  
RET  
PUSH Rsrc
POP  Rdst

## i/o
PRINT  Rsrc
PRINTC Rsrc

## misc. and debugging
END  
CLR  