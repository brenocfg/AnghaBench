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
typedef  char WCHAR ;

/* Variables and functions */
 char* msi_alloc (int) ; 
 int strlenW (char const*) ; 

WCHAR *msi_normalize_path( const WCHAR *in )
{
    const WCHAR *p = in;
    WCHAR *q, *ret;
    int n, len = strlenW( in ) + 2;

    if (!(q = ret = msi_alloc( len * sizeof(WCHAR) ))) return NULL;

    len = 0;
    while (1)
    {
        /* copy until the end of the string or a space */
        while (*p != ' ' && (*q = *p))
        {
            p++, len++;
            /* reduce many backslashes to one */
            if (*p != '\\' || *q != '\\')
                q++;
        }

        /* quit at the end of the string */
        if (!*p)
            break;

        /* count the number of spaces */
        n = 0;
        while (p[n] == ' ')
            n++;

        /* if it's leading or trailing space, skip it */
        if ( len == 0 || p[-1] == '\\' || p[n] == '\\' )
            p += n;
        else  /* copy n spaces */
            while (n && (*q++ = *p++)) n--;
    }
    while (q - ret > 0 && q[-1] == ' ') q--;
    if (q - ret > 0 && q[-1] != '\\')
    {
        q[0] = '\\';
        q[1] = 0;
    }
    return ret;
}