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
typedef  scalar_t__ LPWSTR ;
typedef  char const* LPCWSTR ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ parser_alloc (void*,int) ; 
 int /*<<< orphan*/  strcatW (scalar_t__,char const*) ; 
 int /*<<< orphan*/  strcpyW (scalar_t__,char const*) ; 
 int strlenW (char const*) ; 

__attribute__((used)) static LPWSTR parser_add_table( void *info, LPCWSTR list, LPCWSTR table )
{
    static const WCHAR space[] = {' ',0};
    DWORD len = strlenW( list ) + strlenW( table ) + 2;
    LPWSTR ret;

    ret = parser_alloc( info, len * sizeof(WCHAR) );
    if( ret )
    {
        strcpyW( ret, list );
        strcatW( ret, space );
        strcatW( ret, table );
    }
    return ret;
}