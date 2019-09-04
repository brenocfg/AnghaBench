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
typedef  scalar_t__ LPCWSTR ;

/* Variables and functions */
 scalar_t__ IS_INTRESOURCE (scalar_t__) ; 
 int lstrcmpW (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int resource_strcmp( LPCWSTR a, LPCWSTR b )
{
    if ( a == b )
        return 0;
    if (!IS_INTRESOURCE( a ) && !IS_INTRESOURCE( b ) )
        return lstrcmpW( a, b );
    /* strings come before ids */
    if (!IS_INTRESOURCE( a ) && IS_INTRESOURCE( b ))
        return -1;
    if (!IS_INTRESOURCE( b ) && IS_INTRESOURCE( a ))
        return 1;
    return ( a < b ) ? -1 : 1;
}