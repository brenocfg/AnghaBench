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
typedef  int /*<<< orphan*/  wcdb_logfunc_t ;

/* Variables and functions */
 int /*<<< orphan*/  g_logfunc ; 

wcdb_logfunc_t wcdb_get_log_function()
{
    return g_logfunc;
}