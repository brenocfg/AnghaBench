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
typedef  scalar_t__ WCHAR ;
typedef  unsigned int DWORD ;

/* Variables and functions */
 scalar_t__* msi_alloc (unsigned int) ; 
 int /*<<< orphan*/  strcpyW (scalar_t__*,scalar_t__*) ; 
 int strlenW (scalar_t__*) ; 

__attribute__((used)) static WCHAR *flatten_multi_string_values( WCHAR **left, DWORD left_count,
                                           WCHAR **right, DWORD right_count, DWORD *size )
{
    WCHAR *ret, *p;
    unsigned int i;

    *size = sizeof(WCHAR);
    for (i = 0; i < left_count; i++) *size += (strlenW( left[i] ) + 1) * sizeof(WCHAR);
    for (i = 0; i < right_count; i++) *size += (strlenW( right[i] ) + 1) * sizeof(WCHAR);

    if (!(ret = p = msi_alloc( *size ))) return NULL;

    for (i = 0; i < left_count; i++)
    {
        strcpyW( p, left[i] );
        p += strlenW( p ) + 1;
    }
    for (i = 0; i < right_count; i++)
    {
        strcpyW( p, right[i] );
        p += strlenW( p ) + 1;
    }
    *p = 0;
    return ret;
}