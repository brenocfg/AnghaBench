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
typedef  int /*<<< orphan*/  buf2 ;
typedef  int /*<<< orphan*/  buf1 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int memcmp (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stb_min (int,int) ; 

__attribute__((used)) static int stb_fcmp_core(FILE *f, FILE *g)
{
   char buf1[1024],buf2[1024];
   int n1,n2, res=0;

   while (1) {
      n1 = (int) fread(buf1, 1, sizeof(buf1), f);
      n2 = (int) fread(buf2, 1, sizeof(buf2), g);
      res = memcmp(buf1,buf2,stb_min(n1,n2));
      if (res)
         break;
      if (n1 != n2) {
         res = n1 < n2 ? -1 : 1;
         break;
      }
      if (n1 == 0)
         break;
   }

   fclose(f);
   fclose(g);
   return res;
}