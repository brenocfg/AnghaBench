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

/* Variables and functions */

__attribute__((used)) static int stb__clex_parse_char(char *p, char **q)
{
   if (*p == '\\') {
      *q = p+2; // tentatively guess we'll parse two characters
      switch(p[1]) {
         case '\\': return '\\';
         case '\'': return '\'';
         case '"': return '"';
         case 't': return '\t';
         case 'f': return '\f';
         case 'n': return '\n';
         case 'r': return '\r';
         case '0': return '\0'; // @TODO ocatal constants
         case 'x': case 'X': return -1; // @TODO hex constants
         case 'u': return -1; // @TODO unicode constants
      }
   }
   *q = p+1;
   return (unsigned char) *p;
}