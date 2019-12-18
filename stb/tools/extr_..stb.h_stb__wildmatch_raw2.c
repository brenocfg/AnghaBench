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
 int /*<<< orphan*/  assert (int) ; 
 int stb__find_qstring (char*,char*,int,int) ; 
 scalar_t__ stb__match_qstring (char*,char*,int,int) ; 
 scalar_t__ tolower (char) ; 

int stb__wildmatch_raw2(char *expr, char *candidate, int search, int insensitive)
{
   int where=0;
   int start = -1;
   
   if (!search) {
      // parse to first '*'
      if (*expr != '*')
         start = 0;
      while (*expr != '*') {
         if (!*expr)
            return *candidate == 0 ? 0 : -1;
         if (*expr == '?') {
            if (!*candidate) return -1;
         } else {
            if (insensitive) {
               if (tolower(*candidate) != tolower(*expr))
                  return -1;
            } else 
               if (*candidate != *expr)
                  return -1;
         }
         ++candidate, ++expr, ++where;
      }
   } else {
      // 0-length search string
      if (!*expr)
         return 0;
   }

   assert(search || *expr == '*');
   if (!search)
      ++expr;

   // implicit '*' at this point
      
   while (*expr) {
      int o=0;
      // combine redundant * characters
      while (expr[0] == '*') ++expr;

      // ok, at this point, expr[-1] == '*',
      // and expr[0] != '*'

      if (!expr[0]) return start >= 0 ? start : 0;

      // now find next '*'
      o = 0;
      while (expr[o] != '*') {
         if (expr[o] == 0)
            break;
         ++o;
      }
      // if no '*', scan to end, then match at end
      if (expr[o] == 0 && !search) {
         int z;
         for (z=0; z < o; ++z)
            if (candidate[z] == 0)
               return -1;
         while (candidate[z])
            ++z;
         // ok, now check if they match
         if (stb__match_qstring(candidate+z-o, expr, o, insensitive))
            return start >= 0 ? start : 0;
         return -1; 
      } else {
         // if yes '*', then do stb__find_qmatch on the intervening chars
         int n = stb__find_qstring(candidate, expr, o, insensitive);
         if (n < 0)
            return -1;
         if (start < 0)
            start = where + n;
         expr += o;
         candidate += n+o;
      }

      if (*expr == 0) {
         assert(search);
         return start;
      }

      assert(*expr == '*');
      ++expr;
   }

   return start >= 0 ? start : 0;
}