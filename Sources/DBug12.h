/* DBug12.h
   based on "http://www.coe.montana.edu/ee/rmaher/ee475_FL04/dbug12.h"
   modified by Paul Michaud, May 25, 2011
   Use with BD12printf.c */

/* This file may be included with any C file that uses the D-Bug12 user callable
   routines. It provides a simple, portable way to access the routines from C 
   with a minimum of assembly language "glue code" */
  
/* Documentation for each of these functions can be found in Appendix C 
   of the Reference Guide For D-Bug12 Version 4.x.x */  
  
int DB12printfGlue(char *, ...);

/* typedefs used by D-Bug12 */
typedef  void * Address;
typedef  int Boolean;
typedef  unsigned char Byte;

/* Structure that defines the functions in D-Bug12's user accessible 
   function table. Also provides a function prototype for each function.
   
   NOTES: 
    1. The filler bytes are required because a far pointer is 3 bytes
       but the table had 4 bytes reserved for each far pointer.

    2. The parameter passing order for CodeWarrior is different
       than assumed by DB12. CodeWarrior pushes the parameters from left 
       to right, rather than the customary C language right to left, EXCEPT 
       for functions with a variable number of arguments (eg., printf()),
       which are passed using the right to left pushes.
       
    3. The CWBD12 versions are added to allow CodeWarrior to do type checking
       of arguments and to avoid warning and error messages.
*/
typedef struct {
                void    (*far DB12main)(void); Byte filler1;
                int     (*DB12getchar)(void);
                int     (*DB12putchar)(int);
                int     (*DB12printf)(const char *,...);
//                int     (*far DB12GetCmdLine)(char *CmdLineStr, int CmdLineLen); Byte filler2;
                int     (*far CWDB12GetCmdLine)(int CmdLineLen, char *CmdLineStr); Byte filler2;
                
//                char *  (*far DB12sscanhex)(char *HexStr, unsigned int *BinNum); Byte filler3;
                char *  (*far CWDB12sscanhex)(unsigned int *BinNum, char *HexStr); Byte filler3;
                
                int     (*DB12isxdigit)(int c);
                int     (*DB12toupper)(int c);
                int     (*DB12isalpha)(int c);
                unsigned int (*DB12strlen)(const char *cs);
                char *  (*DB12strcpy)(char *s1, char *s2);
                void    (*far DB12out2hex)(unsigned int num); Byte filler4;
                void    (*far DB12out4hex)(unsigned int num); Byte filler5;
//                int     (*DB12SetUserVector)(int VectNum, Address UserAddress);
                int     (*CWDB12SetUserVector)(Address UserAddress, int VectNum);

//                Boolean (*far DB12WriteEEByte)(Address EEAddress, Byte EEData); Byte filler6;
                Boolean (*far CWDB12WriteEEByte)(Byte EEData, Address EEAddress); Byte filler6;

                int     (*far DB12EraseEE)(void); Byte filler7;
//                int     (*far DB12ReadMem)(Address StartAddress, Byte *MemDataP, unsigned int NumBytes); Byte filler8;
                int     (*far CWDB12ReadMem)(unsigned int NumBytes, Byte *MemDataP, Address StartAddress ); Byte filler8;
                     
//                int     (*far DB12WriteMem)(Address StartAddress, Byte *MemDataP, unsigned int NumBytes); Byte filler9;
                int     (*far CWDB12WriteMem)(unsigned int NumBytes, Byte *MemDataP, Address StartAddress); Byte filler9;
                
            }UserFN, *UserFNP;

/* define a pointer to the start of D-Bug12's user accessible function table which
   in version 4.x.x begins at $ee80 */
#define DB12FNP ((UserFNP)0xee80) 

/* The following #defines are used to provide for portability and avoid linker
   conflicts with the standard library functions of the same name. No #define is
   included for DB12main() since all C programs contain a main() function. */
#define getchar  DB12FNP->DB12getchar
#define putchar  DB12FNP->DB12putchar
#define isxdigit DB12FNP->DB12isxdigit
#define toupper  DB12FNP->DB12toupper
#define isalpha  DB12FNP->DB12isalpha
#define strlen   DB12FNP->DB12strlen
#define out2hex  DB12FNP->DB12out2hex
#define out4hex  DB12FNP->DB12out4hex
#define EraseEE  DB12FNP->DB12EraseEE 

/* defines to exchange parameter order (CodeWarrior calling convention) */
#define SetUserVector(b,a) DB12FNP->CWDB12SetUserVector(a,b)
#define GetCmdLine(b,a)    DB12FNP->CWDB12GetCmdLine(a,b)
#define sscanhex(b,a)      DB12FNP->CWDB12sscanhex(a,b)
#define strcpy(b,a)        DB12FNP->DB12strcpy(a,b)
#define WriteEEByte(b,a)   DB12FNP->CWDB12WriteEEByte(a,b)
#define ReadMem(c,b,a)     DB12FNP->CWDB12ReadMem(a,b,c)
#define WriteMem(c,b,a)    DB12FNP->CWDB12WriteMem(a,b,c)

/* define for printf is different because arguments are passed right to left on the stack
   and accumulator D is not used for first argument */
#define printf   DB12printfGlue
 