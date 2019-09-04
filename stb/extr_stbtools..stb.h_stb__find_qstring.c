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
 scalar_t__ stb__match_qstring (char*,char*,int,int) ; 
 char tolower (char) ; 

__attribute__((used)) static int stb__find_qstring(char *candidate, char *qstring, int qlen, int insensitive)
{
   char c;

   int offset=0;
   while (*qstring == '?') {
      ++qstring;
      --qlen;
      ++candidate;
      if (qlen == 0) return 0;
      if (*candidate == 0) return -1;
   }

   c = *qstring++;
   --qlen;
   if (insensitive) c = tolower(c);

   while (candidate[offset]) {
      if (c == (insensitive ? tolower(candidate[offset]) : candidate[offset]))
         if (stb__match_qstring(candidate+offset+1, qstring, qlen, insensitive))
            return offset;
      ++offset;
   }

   return -1;
}