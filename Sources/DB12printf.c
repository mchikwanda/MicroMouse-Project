// DB12printf.c
// May 25, 2011: Paul Michaud
// Assembly glue to allow D-Bug12 builtin printf function to be used in Code Warrior.
// Use this together with DBug12.h which gives access to the other user available 
// builtin functions in D-Bug12.

/* printf() is different because CW arguments are passed right to left on the stack
   and the calling routine cleans up the stack. The DB12 printf assumes that the
   arguments are passed right to left on the stack except for the first one which
   is passed in accumulator D.
 */
 
int DB12printfGlue(char *, ...);
int saveReturn; 
 
int DB12printfGlue(char * format, ...){
   asm("pulx");              // pull return address and save
   asm("stx saveReturn");
   asm("puld");              // pull 1st argument into D
 
   asm("jsr [0xEE88,pcr]");  // BD12printf
   asm("ldx saveReturn");    //restore stack and return address
   asm("pshx"); 
   asm("pshx");
  
}