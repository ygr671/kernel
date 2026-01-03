#include "types.h"
#include "vga.h"

void
kmain ()
{
   clear_vga_buffer ();
   print ("Hello, kernel!", 0x0F);
   
   while (1)
      {
      }
}
