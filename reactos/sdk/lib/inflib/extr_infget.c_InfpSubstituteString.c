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
typedef  scalar_t__* PWSTR ;
typedef  int /*<<< orphan*/  PINFCACHE ;
typedef  char* PCWSTR ;

/* Variables and functions */
 char* InfpGetSubstitutionString (int /*<<< orphan*/ ,char const*,size_t*,int) ; 
 int MAX_INF_STRING_LENGTH ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,char const*,size_t) ; 

__attribute__((used)) static size_t
InfpSubstituteString(PINFCACHE Inf,
                     PCWSTR text,
                     PWSTR buffer,
                     size_t size)
{
    const WCHAR *start, *subst, *p;
    size_t len, total = 0;
    int inside = 0;

    if (!buffer) size = MAX_INF_STRING_LENGTH + 1;
    for (p = start = text; *p; p++)
    {
        if (*p != '%') continue;
        inside = !inside;
        if (inside)  /* start of a %xx% string */
        {
            len = (p - start);
            if (len > size - 1) len = size - 1;
            if (buffer) memcpy( buffer + total, start, len * sizeof(WCHAR) );
            total += len;
            size -= len;
            start = p;
        }
        else /* end of the %xx% string, find substitution */
        {
            len = (p - start - 1);
            subst = InfpGetSubstitutionString( Inf, start + 1, &len, p[1] == '\\' );
            if (!subst)
            {
                subst = start;
                len = (p - start + 1);
            }
            if (len > size - 1) len = size - 1;
            if (buffer) memcpy( buffer + total, subst, len * sizeof(WCHAR) );
            total += len;
            size -= len;
            start = p + 1;
        }
    }

    if (start != p) /* unfinished string, copy it */
    {
        len = (unsigned int)(p - start);
        if (len > size - 1) len = size - 1;
        if (buffer) memcpy( buffer + total, start, len * sizeof(WCHAR) );
        total += len;
    }
    if (buffer && size) buffer[total] = 0;
    return total;
}