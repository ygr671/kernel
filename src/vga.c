#include "vga.h"
#include "types.h"

volatile u16 *vga_buffer = (u16 *)0xB8000;

void
print (const char *s, u8 colour)
{
  int index = 0;
   for (int i = 0; s[index] != '\0'; i++)
      {
         switch (s[index])
            {
            case '\t':
               vga_buffer[index] = 0 << 8 | 9;
               break;
            case '\n':
               for (int j = i; j % 79 != 0; j++)
                  {
                     vga_buffer[j] = 0 << 8 | 10;
		     i++;
                  }
	       break;
            default:
               vga_buffer[i] = (u16)colour << 8 | s[index];
            }
	 index++;
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
