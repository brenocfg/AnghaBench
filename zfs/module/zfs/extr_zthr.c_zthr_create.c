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
typedef  int /*<<< orphan*/  zthr_t ;
typedef  int /*<<< orphan*/  zthr_func_t ;
typedef  int /*<<< orphan*/  zthr_checkfunc_t ;
typedef  int /*<<< orphan*/  hrtime_t ;

/* Variables and functions */
 int /*<<< orphan*/ * zthr_create_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 

zthr_t *
zthr_create(zthr_checkfunc_t *checkfunc, zthr_func_t *func, void *arg)
{
	return (zthr_create_timer(checkfunc, func, arg, (hrtime_t)0));
}