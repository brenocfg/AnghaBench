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
 double stb__clex_pow (int,unsigned int) ; 

__attribute__((used)) static double stb__clex_parse_float(char *p, char **q)
{
   char *s = p;
   double value=0;
   int base=10;
   int exponent=0;

#ifdef STB__clex_hex_floats
   if (*p == '0') {
      if (p[1] == 'x' || p[1] == 'X') {
         base=16;
         p += 2;
      }
   }
#endif

   for (;;) {
      if (*p >= '0' && *p <= '9')
         value = value*base + (*p++ - '0');
#ifdef STB__clex_hex_floats
      else if (base == 16 && *p >= 'a' && *p <= 'f')
         value = value*base + 10 + (*p++ - 'a');
      else if (base == 16 && *p >= 'A' && *p <= 'F')
         value = value*base + 10 + (*p++ - 'A');
#endif
      else
         break;
   }

   if (*p == '.') {
      double pow, addend = 0;
      ++p;
      for (pow=1; ; pow*=base) {
         if (*p >= '0' && *p <= '9')
            addend = addend*base + (*p++ - '0');
#ifdef STB__clex_hex_floats
         else if (base == 16 && *p >= 'a' && *p <= 'f')
            addend = addend*base + 10 + (*p++ - 'a');
         else if (base == 16 && *p >= 'A' && *p <= 'F')
            addend = addend*base + 10 + (*p++ - 'A');
#endif
         else
            break;
      }
      value += addend / pow;
   }
#ifdef STB__clex_hex_floats
   if (base == 16) {
      // exponent required for hex float literal
      if (*p != 'p' && *p != 'P') {
         *q = s;
         return 0;
      }
      exponent = 1;
   } else
#endif
      exponent = (*p == 'e' || *p == 'E');

   if (exponent) {
      int sign = p[1] == '-';
      unsigned int exponent=0;
      double power=1;
      ++p;
      if (*p == '-' || *p == '+')
         ++p;
      while (*p >= '0' && *p <= '9')
         exponent = exponent*10 + (*p++ - '0');

#ifdef STB__clex_hex_floats
      if (base == 16)
         power = stb__clex_pow(2, exponent);
      else
#endif
         power = stb__clex_pow(10, exponent);
      if (sign)
         value /= power;
      else
         value *= power;
   }
   *q = p;
   return value;
}