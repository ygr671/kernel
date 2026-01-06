#include "vga.h"
#include "types.h"

void
kmain ()
{
   clear_vga_buffer ();
   print ("Hello, kernel!\ttest\nand here goes a new line!", 0x0F);
   
   while (1)
      {
      }
}
