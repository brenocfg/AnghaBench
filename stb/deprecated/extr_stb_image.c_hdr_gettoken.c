#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  stbi ;

/* Variables and functions */
 int HDR_BUFLEN ; 
 int /*<<< orphan*/  at_eof (int /*<<< orphan*/ *) ; 
 char get8 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *hdr_gettoken(stbi *z, char *buffer)
{
   int len=0;
   char c = '\0';

   c = (char) get8(z);

   while (!at_eof(z) && c != '\n') {
      buffer[len++] = c;
      if (len == HDR_BUFLEN-1) {
         // flush to end of line
         while (!at_eof(z) && get8(z) != '\n')
            ;
         break;
      }
      c = (char) get8(z);
   }

   buffer[len] = 0;
   return buffer;
}