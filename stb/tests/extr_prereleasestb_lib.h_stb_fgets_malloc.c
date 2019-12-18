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
typedef  int /*<<< orphan*/  quick_buffer ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ realloc (char*,int) ; 
 char* strdup (char*) ; 
 int strlen (char*) ; 

char * stb_fgets_malloc(FILE *f)
{
   // avoid reallocing for small strings
   char quick_buffer[800];
   quick_buffer[sizeof(quick_buffer)-2] = 0;
   if (!fgets(quick_buffer, sizeof(quick_buffer), f))
      return NULL;

   if (quick_buffer[sizeof(quick_buffer)-2] == 0) {
      int n = strlen(quick_buffer);
      if (n > 0 && quick_buffer[n-1] == '\n')
         quick_buffer[n-1] = 0;
      return strdup(quick_buffer);
   } else {
      char *p;
      char *a = strdup(quick_buffer);
      int len = sizeof(quick_buffer)-1;

      while (!feof(f)) {
         if (a[len-1] == '\n') break;
         a = (char *) realloc(a, len*2);
         p = &a[len];
         p[len-2] = 0;
         if (!fgets(p, len, f))
            break;
         if (p[len-2] == 0) {
            len += strlen(p);
            break;
         }
         len = len + (len-1);
      }
      if (a[len-1] == '\n')
         a[len-1] = 0;
      return a;
   }
}