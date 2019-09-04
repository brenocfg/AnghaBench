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
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 char* heap_alloc (unsigned int) ; 
 int /*<<< orphan*/  heap_free (char*) ; 

__attribute__((used)) static WCHAR *parse_value( const WCHAR *str, unsigned int len )
{
    WCHAR *ret;
    const WCHAR *p = str;
    BOOL quoted = FALSE;
    unsigned int i = 0;

    if (!(ret = heap_alloc( (len + 1) * sizeof(WCHAR) ))) return NULL;
    if (*p == '\"')
    {
        quoted = TRUE;
        p++;
    }
    while (*p && *p != '\"') ret[i++] = *p++;
    if ((quoted && *p != '\"') || (!quoted && *p == '\"'))
    {
        heap_free( ret );
        return NULL;
    }
    ret[i] = 0;
    return ret;
}