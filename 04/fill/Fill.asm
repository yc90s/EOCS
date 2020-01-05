// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, the
// program clears the screen, i.e. writes "white" in every pixel.

// Put your code here.
(BEGIN)
@i
M=0
@KBD
D=M
@BLACK 
D;JGT
(SETSCREEN)
@SCREEN
D=A
@j 
M=D             // 0x4000
(LOOP)
@i
D=M
@j 
A=M
M=D
@j 
M=M+1           // j = j+1
D=M 
@KBD 
D=A-D
@LOOP
D;JGT 
@BEGIN
0;JMP

(BLACK)
@i 
M=0
M=!M
@SETSCREEN 
0;JMP
