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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stb__fopen (char*,char*) ; 
 int stb_fcmp_core (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int stb_fcmp(char *s1, char *s2)
{
   FILE *f = stb__fopen(s1, "rb");
   FILE *g = stb__fopen(s2, "rb");

   if (f == NULL || g == NULL) {
      if (f) fclose(f);
      if (g) {
         fclose(g);
         return 1;
      }
      return f != NULL;
   }

   return stb_fcmp_core(f,g);
}