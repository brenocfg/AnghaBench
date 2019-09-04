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
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  stb_arr_push (char**,char*) ; 
 int /*<<< orphan*/  stb_getopt_free (char**) ; 
 int /*<<< orphan*/  stb_p_strcpy_s (char*,size_t,char*) ; 
 char* stb_p_strdup (char*) ; 
 scalar_t__ strchr (char*,char) ; 
 size_t strlen (char*) ; 

char **stb_getopt_param(int *argc, char **argv, char *param)
{
   char ** opts=NULL;
   int i,j=1;
   for (i=1; i < *argc; ++i) {
      if (argv[i][0] != '-') {
         argv[j++] = argv[i];
      } else {
         if (argv[i][1] == 0) { // plain - == don't parse further options
            ++i;
            while (i < *argc)
               argv[j++] = argv[i++];
            break;
         } else if (argv[i][1] == '-') {
            // copy argument through including initial '-' for clarity
            stb_arr_push(opts, stb_p_strdup(argv[i]));
         } else {
            int k;
            char *q = argv[i];  // traverse options list
            for (k=1; q[k]; ++k) {
               char *s;
               if (strchr(param, q[k])) {  // does it take a parameter?
                  char *t = &q[k+1], z = q[k];
                  size_t len=0;
                  if (*t == 0) {
                     if (i == *argc-1) { // takes a parameter, but none found
                        *argc = 0;
                        stb_getopt_free(opts);
                        return NULL;
                     }
                     t = argv[++i];
                  } else
                     k += (int) strlen(t);
                  len = strlen(t);
                  s = (char *) malloc(len+2);
                  if (!s) return NULL;
                  s[0] = z;
                  stb_p_strcpy_s(s+1, len+2, t);
               } else {
                  // no parameter
                  s = (char *) malloc(2);
                  if (!s) return NULL;
                  s[0] = q[k];
                  s[1] = 0;
               }
               stb_arr_push(opts, s);
            }
         }
      }
   }
   stb_arr_push(opts, NULL);
   *argc = j;
   return opts;
}