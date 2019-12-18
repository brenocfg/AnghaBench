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
struct TYPE_3__ {scalar_t__ zc_history; } ;
typedef  TYPE_1__ zfs_cmd_t ;

/* Variables and functions */
 int HIS_MAX_RECORD_LEN ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 scalar_t__ copyinstr (void*,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  history_str_free (char*) ; 
 char* kmem_alloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
history_str_get(zfs_cmd_t *zc)
{
	char *buf;

	if (zc->zc_history == 0)
		return (NULL);

	buf = kmem_alloc(HIS_MAX_RECORD_LEN, KM_SLEEP);
	if (copyinstr((void *)(uintptr_t)zc->zc_history,
	    buf, HIS_MAX_RECORD_LEN, NULL) != 0) {
		history_str_free(buf);
		return (NULL);
	}

	buf[HIS_MAX_RECORD_LEN -1] = '\0';

	return (buf);
}