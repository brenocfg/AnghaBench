#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char const* (* dbgstr_an ) (char const*,int) ;} ;

/* Variables and functions */
 TYPE_1__ funcs ; 
 char const* stub1 (char const*,int) ; 

const char *wine_dbgstr_an( const char * s, int n )
{
    return funcs.dbgstr_an(s, n);
}