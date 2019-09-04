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
 char* stb_malloc_string (void*,size_t) ; 
 int /*<<< orphan*/  stb_p_strcpy_s (char*,size_t,char*) ; 
 size_t strlen (char*) ; 

char *stb_strdup(char *str, void *pool)
{
   size_t len = strlen(str);
   char *p = stb_malloc_string(pool, len+1);
   stb_p_strcpy_s(p, len+1, str);
   return p;
}