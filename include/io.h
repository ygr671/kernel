#ifndef K_IO_H
#define K_IO_H

#include "types.h"

/* these two are implemented in boot.asm */
u8 inportb (u16 port);
void outportb (u16 port, u8 value);

void read_kbd(char *buffer);
   
#endif /* K_IO_H */
