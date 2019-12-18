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

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MUTEX_DEFAULT ; 
 scalar_t__ kstat_id ; 
 int /*<<< orphan*/  kstat_module_list ; 
 int /*<<< orphan*/  kstat_module_lock ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
spl_kstat_init(void)
{
	mutex_init(&kstat_module_lock, NULL, MUTEX_DEFAULT, NULL);
	INIT_LIST_HEAD(&kstat_module_list);
	kstat_id = 0;
	return (0);
}