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
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ lstrcmpW (scalar_t__,scalar_t__) ; 

__attribute__((used)) static BOOL
REBAR_strdifW( LPCWSTR a, LPCWSTR b )
{
    return ( (a && !b) || (b && !a) || (a && b && lstrcmpW(a, b) ) );
}