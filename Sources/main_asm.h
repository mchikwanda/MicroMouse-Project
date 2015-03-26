#ifndef _MAIN_ASM_H
#define _MAIN_ASM_H

#ifdef __cplusplus
    extern "C" { /* our assembly functions have C calling convention */
#endif

/* interface to my assembly main function */
void asm_main(void);
void delay(unsigned int);
void delay20us(void);

#ifdef __cplusplus
    }
#endif

#endif /* _MAIN_ASM_H */
