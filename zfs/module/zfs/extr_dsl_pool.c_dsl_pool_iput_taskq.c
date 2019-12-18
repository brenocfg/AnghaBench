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
typedef  int /*<<< orphan*/  taskq_t ;
struct TYPE_3__ {int /*<<< orphan*/ * dp_iput_taskq; } ;
typedef  TYPE_1__ dsl_pool_t ;

/* Variables and functions */

taskq_t *
dsl_pool_iput_taskq(dsl_pool_t *dp)
{
	return (dp->dp_iput_taskq);
}