#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  spa_errlog_lock; int /*<<< orphan*/  spa_errlist_lock; int /*<<< orphan*/  spa_errlist_last; int /*<<< orphan*/  spa_errlist_scrub; int /*<<< orphan*/  spa_errlog_last; int /*<<< orphan*/  spa_scrub_finished; int /*<<< orphan*/  spa_errlog_scrub; } ;
typedef  TYPE_1__ spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int process_error_list (int /*<<< orphan*/ *,void*,size_t*) ; 
 int process_error_log (TYPE_1__*,int /*<<< orphan*/ ,void*,size_t*) ; 

int
spa_get_errlog(spa_t *spa, void *uaddr, size_t *count)
{
	int ret = 0;

#ifdef _KERNEL
	mutex_enter(&spa->spa_errlog_lock);

	ret = process_error_log(spa, spa->spa_errlog_scrub, uaddr, count);

	if (!ret && !spa->spa_scrub_finished)
		ret = process_error_log(spa, spa->spa_errlog_last, uaddr,
		    count);

	mutex_enter(&spa->spa_errlist_lock);
	if (!ret)
		ret = process_error_list(&spa->spa_errlist_scrub, uaddr,
		    count);
	if (!ret)
		ret = process_error_list(&spa->spa_errlist_last, uaddr,
		    count);
	mutex_exit(&spa->spa_errlist_lock);

	mutex_exit(&spa->spa_errlog_lock);
#endif

	return (ret);
}