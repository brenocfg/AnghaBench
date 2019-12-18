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
typedef  int /*<<< orphan*/  zbuf ;
struct TYPE_3__ {int vs_trim_state; int vs_trim_bytes_done; int vs_trim_bytes_est; scalar_t__ vs_trim_notsup; int /*<<< orphan*/  vs_trim_action_time; int /*<<< orphan*/  vs_scan_removing; } ;
typedef  TYPE_1__ vdev_stat_t ;
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  tbuf ;
struct tm {int dummy; } ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
#define  VDEV_TRIM_ACTIVE 130 
#define  VDEV_TRIM_COMPLETE 129 
#define  VDEV_TRIM_SUSPENDED 128 
 char* gettext (char*) ; 
 int /*<<< orphan*/  localtime_r (int /*<<< orphan*/ *,struct tm*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,struct tm*) ; 

__attribute__((used)) static void
print_status_trim(vdev_stat_t *vs, boolean_t verbose)
{
	if (verbose) {
		if ((vs->vs_trim_state == VDEV_TRIM_ACTIVE ||
		    vs->vs_trim_state == VDEV_TRIM_SUSPENDED ||
		    vs->vs_trim_state == VDEV_TRIM_COMPLETE) &&
		    !vs->vs_scan_removing) {
			char zbuf[1024];
			char tbuf[256];
			struct tm zaction_ts;

			time_t t = vs->vs_trim_action_time;
			int trim_pct = 100;
			if (vs->vs_trim_state != VDEV_TRIM_COMPLETE) {
				trim_pct = (vs->vs_trim_bytes_done *
				    100 / (vs->vs_trim_bytes_est + 1));
			}

			(void) localtime_r(&t, &zaction_ts);
			(void) strftime(tbuf, sizeof (tbuf), "%c", &zaction_ts);

			switch (vs->vs_trim_state) {
			case VDEV_TRIM_SUSPENDED:
				(void) snprintf(zbuf, sizeof (zbuf), ", %s %s",
				    gettext("suspended, started at"), tbuf);
				break;
			case VDEV_TRIM_ACTIVE:
				(void) snprintf(zbuf, sizeof (zbuf), ", %s %s",
				    gettext("started at"), tbuf);
				break;
			case VDEV_TRIM_COMPLETE:
				(void) snprintf(zbuf, sizeof (zbuf), ", %s %s",
				    gettext("completed at"), tbuf);
				break;
			}

			(void) printf(gettext("  (%d%% trimmed%s)"),
			    trim_pct, zbuf);
		} else if (vs->vs_trim_notsup) {
			(void) printf(gettext("  (trim unsupported)"));
		} else {
			(void) printf(gettext("  (untrimmed)"));
		}
	} else if (vs->vs_trim_state == VDEV_TRIM_ACTIVE) {
		(void) printf(gettext("  (trimming)"));
	}
}