#ifndef __K_VGA_H
#define __K_VGA_H

#include "types.h"

/* 80x25 = 2000 */
#define VGA_BUFFER_SIZE 2000
#define CLEAR_CHAR 127   

extern volatile u16 *vga_buffer;

void print (const char *s, u8 colour);
void clear_vga_buffer ();
void clear_vga_buffer_range (const int start, const int end);

#endif /* __K_VGA_H */
