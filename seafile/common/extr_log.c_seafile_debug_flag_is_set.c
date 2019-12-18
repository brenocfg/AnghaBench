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
typedef  int gboolean ;
typedef  int SeafileDebugFlags ;

/* Variables and functions */
 int debug_flags ; 

gboolean
seafile_debug_flag_is_set (SeafileDebugFlags flag)
{
    return (debug_flags & flag) != 0;
}