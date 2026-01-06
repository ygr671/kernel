#include "io.h"
#include "types.h"
#include "vga.h"

void
kmain ()
{
   clear_vga_buffer ();
   print ("Welcome to kernel!\n", 0x0F);

   print ("Enter name: ", 0x0F);

   char name[10];
   read_kbd (name, 10);

   print ("Hi, ", 0x0F);
   print (name, 0x0F);
   print ("!\n", 0x0F);

   char command[256] = {0};
   while (1)
      {
	print ("# ", 0x0F);

        read_kbd (command, 256);

        print ("Your command: ", 0x0F);
        print (command, 0x0F);
	print("\n", 0xF);
      }
}
