#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* psz_string; } ;
typedef  TYPE_1__ vlc_value_t ;

/* Variables and functions */
 char* strdup (char*) ; 

__attribute__((used)) static void DupString( vlc_value_t *p_val )
{
    p_val->psz_string = strdup( p_val->psz_string ? p_val->psz_string :  "" );
}