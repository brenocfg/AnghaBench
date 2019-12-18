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
typedef  scalar_t__ wcdb_logfunc_t ;

/* Variables and functions */
 scalar_t__ dummy_log ; 
 scalar_t__ g_logfunc ; 

void wcdb_set_log_function(wcdb_logfunc_t func)
{
    if (!func)
        func = dummy_log;
    g_logfunc = func;
}