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
struct tm {int tm_year; int tm_mon; int tm_mday; int tm_hour; int tm_min; int /*<<< orphan*/  tm_sec; } ;
struct TYPE_3__ {int lt_gmtoff; } ;
typedef  TYPE_1__ iso9660_ltime_t ;
typedef  int iso712_t ;

/* Variables and functions */
 int /*<<< orphan*/  cdio_warn (char*,int) ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
iso9660_set_ltime_with_timezone(const struct tm *p_tm,
                                int time_zone,
                                /*out*/ iso9660_ltime_t *pvd_date)
{
  char *_pvd_date = (char *) pvd_date;

  memset (_pvd_date, (int) '0', 16);
  pvd_date->lt_gmtoff = (iso712_t) 0; /* Start out with time zone GMT. */

  if (!p_tm) return;

  snprintf(_pvd_date, 17,
           "%4.4d%2.2d%2.2d" "%2.2d%2.2d%2.2d" "%2.2d",
           p_tm->tm_year + 1900, p_tm->tm_mon + 1, p_tm->tm_mday,
           p_tm->tm_hour, p_tm->tm_min, p_tm->tm_sec,
           0 /* 1/100 secs */ );

  /* Set time zone in 15-minute interval encoding. */
  pvd_date->lt_gmtoff -= (time_zone / 15);
  if (pvd_date->lt_gmtoff < -48 ) {

    cdio_warn ("Converted ISO 9660 timezone %d is less than -48. Adjusted",
               (int) pvd_date->lt_gmtoff);
    pvd_date->lt_gmtoff = -48;
  } else if (pvd_date->lt_gmtoff > 52) {
    cdio_warn ("Converted ISO 9660 timezone %d is over 52. Adjusted",
               (int) pvd_date->lt_gmtoff);
    pvd_date->lt_gmtoff = 52;
  }
}