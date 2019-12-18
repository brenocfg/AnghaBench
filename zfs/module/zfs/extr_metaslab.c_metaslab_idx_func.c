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
typedef  int /*<<< orphan*/  multilist_t ;
struct TYPE_2__ {unsigned int ms_id; } ;
typedef  TYPE_1__ metaslab_t ;

/* Variables and functions */
 unsigned int multilist_get_num_sublists (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int
metaslab_idx_func(multilist_t *ml, void *arg)
{
	metaslab_t *msp = arg;
	return (msp->ms_id % multilist_get_num_sublists(ml));
}