#include "io.h"
#include "types.h"
#include "vga.h"

#define KEYCODE_CHAR_LIST                                                     \
   X (2, '1')                                                                 \
   X (3, '2')                                                                 \
   X (4, '3')                                                                 \
   X (5, '4')                                                                 \
   X (6, '5')                                                                 \
   X (7, '6')                                                                 \
   X (8, '7')                                                                 \
   X (9, '8')                                                                 \
   X (10, '9')                                                                \
   X (11, '0')                                                                \
   X (12, '-')                                                                \
   X (13, '=')                                                                \
   X (15, '\t')                                                               \
   X (16, 'q')                                                                \
   X (17, 'w')                                                                \
   X (18, 'e')                                                                \
   X (19, 'r')                                                                \
   X (20, 't')                                                                \
   X (21, 'y')                                                                \
   X (22, 'u')                                                                \
   X (23, 'i')                                                                \
   X (24, 'o')                                                                \
   X (25, 'p')                                                                \
   X (26, '[')                                                                \
   X (27, ']')                                                                \
   X (30, 'a')                                                                \
   X (31, 's')                                                                \
   X (32, 'd')                                                                \
   X (33, 'f')                                                                \
   X (34, 'g')                                                                \
   X (35, 'h')                                                                \
   X (36, 'j')                                                                \
   X (37, 'k')                                                                \
   X (38, 'l')                                                                \
   X (39, ';')                                                                \
   X (40, '\'')                                                               \
   X (41, '`')                                                                \
   X (44, 'z')                                                                \
   X (45, 'x')                                                                \
   X (46, 'c')                                                                \
   X (47, 'v')                                                                \
   X (48, 'b')                                                                \
   X (49, 'n')                                                                \
   X (50, 'm')                                                                \
   X (51, ',')                                                                \
   X (52, '.')                                                                \
   X (53, '/')                                                                \
   X (57, ' ')

void
read_kbd (char *buffer, u32 buffer_size)
{
   int is_reading = 1;
   u8 i           = 0;
   u32 saved_vga_cursor_pos = vga_cursor;

   while (is_reading)
      {
         if ((inportb (0x64) & 0x1) == 1)
            {

#define X(code, c)                                                            \
   case code:                                                                 \
      {                                                                       \
         /* add the char only if we have room left in the buffer */           \
         if (i + 1 <= buffer_size)                                            \
            {                                                                 \
               buffer[i] = c;                                                 \
               print_char (c, 0x0F);                                          \
               i++;                                                           \
            }                                                                 \
      }                                                                       \
      break;

               switch (inportb (0x60))
                  {
                     KEYCODE_CHAR_LIST

                     /* backspace key */
                  case 14:
                     {

                        if (vga_cursor > 0 && vga_cursor != saved_vga_cursor_pos)
                           {
                              vga_cursor--;
                           }
                        vga_buffer[vga_cursor] = 0x0F;
                        if (i > 0)
                           {
                              i--;
                           }
                     }
                     break;

                     /* enter key */
                  case 28:
                     {
                        is_reading = 0;
                        i++;
                     }
                     break;

                  default:
                     {
                     }
                     break;
                  }
#undef X
            }
      }

   buffer[i] = '\0';
   print_char ('\n', 0x0F);
}
