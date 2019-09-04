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
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 char* realloc (char*,size_t) ; 
 int vsnprintf (char*,size_t,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *vstrfmtmake (size_t *lenp, const char *fmt, va_list ap)
{
    size_t size = 1000;
    char *p, *q;
    int n;

    p = malloc (size);
    if (!p) return NULL;
    while (1) {
        n = vsnprintf (p, size, fmt, ap);
        if (n < 0) size *= 2;   /* Windows */
        else if ((unsigned)n >= size) size = n+1; /* glibc */
        else break;
        q = realloc (p, size);
        if (!q) {
          free (p);
          return NULL;
       }
       p = q;
    }
    if (lenp) *lenp = n;
    return p;
}