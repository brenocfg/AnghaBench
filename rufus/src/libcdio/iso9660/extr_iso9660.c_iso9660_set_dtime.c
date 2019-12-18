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
struct tm {int tm_gmtoff; scalar_t__ tm_isdst; } ;
typedef  int /*<<< orphan*/  iso9660_dtime_t ;

/* Variables and functions */
 int /*<<< orphan*/  iso9660_set_dtime_with_timezone (struct tm const*,int,int /*<<< orphan*/ *) ; 

void
iso9660_set_dtime(const struct tm *p_tm, /*out*/ iso9660_dtime_t *p_idr_date)
{
  int time_zone = 0;
  if (p_tm) {
#ifdef HAVE_TM_GMTOFF
    /* Convert seconds to minutes */
    time_zone = p_tm->tm_gmtoff / 60;
#else
    time_zone = (p_tm->tm_isdst > 0) ? -60 : 0;
#endif
  }
  iso9660_set_dtime_with_timezone (p_tm, time_zone, p_idr_date);
}