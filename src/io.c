#include "io.h"
#include "types.h"
#include "vga.h"

void
read_kbd (char *buffer)
{
   int is_reading = 1;
   u8 i           = 0;

   while (is_reading)
      {
         if ((inportb (0x64) & 0x1) == 1)
            {
               switch (inportb (0x60))
                  {
                  case 2:
                     {
                        buffer[i] = '1';
                        print ("1", 0x0F);
                     }
                     break;
                  case 28:
                     {
                        buffer[i] = '\n';
                        print ("\n", buffer[i]);
                        is_reading = 0;
                     }
                  default:
                     {
                     }
                     break;
                  }
               i++;
            }
      }

   buffer[i] = '\0';
}
