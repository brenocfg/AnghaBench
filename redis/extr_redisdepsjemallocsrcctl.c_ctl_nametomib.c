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
typedef  int /*<<< orphan*/  tsd_t ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ ctl_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctl_initialized ; 
 int ctl_lookup (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,size_t*,size_t*) ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 

int
ctl_nametomib(tsd_t *tsd, const char *name, size_t *mibp, size_t *miblenp) {
	int ret;

	if (!ctl_initialized && ctl_init(tsd)) {
		ret = EAGAIN;
		goto label_return;
	}

	ret = ctl_lookup(tsd_tsdn(tsd), name, NULL, mibp, miblenp);
label_return:
	return(ret);
}