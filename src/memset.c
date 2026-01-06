#include "memset.h"

void
memset (void *buf, int c, int size)
{
   char *tmp = (char*)buf;
   for (int i = 0; i < size; i++)
      {
         tmp[i] = c; 
      }
}
