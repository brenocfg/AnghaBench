#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ psz_scanlist_file; } ;
typedef  TYPE_1__ scan_parameter_t ;

/* Variables and functions */
 int /*<<< orphan*/  scan_parameter_Clean (TYPE_1__*) ; 
 scalar_t__ strdup (scalar_t__) ; 

__attribute__((used)) static void scan_parameter_Copy( const scan_parameter_t *p_src, scan_parameter_t *p_dst )
{
    scan_parameter_Clean( p_dst );
    *p_dst = *p_src;
    if( p_src->psz_scanlist_file )
        p_dst->psz_scanlist_file = strdup( p_src->psz_scanlist_file );
}