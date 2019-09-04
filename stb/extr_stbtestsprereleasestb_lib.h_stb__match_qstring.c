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
 scalar_t__ tolower (char) ; 

__attribute__((used)) static int stb__match_qstring(char *candidate, char *qstring, int qlen, int insensitive)
{
   int i;
   if (insensitive) {
      for (i=0; i < qlen; ++i)
         if (qstring[i] == '?') {
            if (!candidate[i]) return 0;
         } else
            if (tolower(qstring[i]) != tolower(candidate[i]))
               return 0;
   } else {
      for (i=0; i < qlen; ++i)
         if (qstring[i] == '?') {
            if (!candidate[i]) return 0;
         } else
            if (qstring[i] != candidate[i])
               return 0;
   }
   return 1;
}