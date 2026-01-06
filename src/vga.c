#include "vga.h"
#include "types.h"

volatile u16 *vga_buffer = (u16 *)0xB8000;

u32 cursor = 0;

void
print (const char *s, u8 colour)
{
   for (int i = 0; s[i] != '\0'; i++)
      {
         switch (s[i])
            {
            case '\t':
               {
                  cursor += 4;
               }
               break;
            case '\n':
               {
                  cursor = ((cursor / 80) + 1) * 80 - 1;
               }
               break;
            default:
               vga_buffer[cursor] = (u16)colour << 8 | s[i];
               break;
            }
         cursor++;
      }
}

void
clear_vga_buffer ()
{
   clear_vga_buffer_range (0, VGA_BUFFER_SIZE);
}

void
clear_vga_buffer_range (const int start, const int end)
{
   for (int i = start; i < end; i++)
      {
         vga_buffer[i] = CLEAR_CHAR;
      }
}
