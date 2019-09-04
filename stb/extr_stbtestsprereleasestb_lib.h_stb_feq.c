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
 int /*<<< orphan*/  stb_fcmp_core (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ stb_filelen (int /*<<< orphan*/ *) ; 

int stb_feq(char *s1, char *s2)
{
   FILE *f = stb__fopen(s1, "rb");
   FILE *g = stb__fopen(s2, "rb");

   if (f == NULL || g == NULL) {
      if (f) fclose(f);
      if (g) fclose(g);
      return f == g;
   }

   // feq is faster because it shortcuts if they're different length
   if (stb_filelen(f) != stb_filelen(g)) {
      fclose(f);
      fclose(g);
      return 0;
   }

   return !stb_fcmp_core(f,g);
}