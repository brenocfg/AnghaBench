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
typedef  int /*<<< orphan*/  time_t ;
struct tm {scalar_t__ tm_year; scalar_t__ tm_mon; scalar_t__ tm_mday; scalar_t__ tm_hour; scalar_t__ tm_min; scalar_t__ tm_sec; int tm_isdst; scalar_t__ tm_zone; } ;
struct TYPE_3__ {scalar_t__ dt_year; scalar_t__ dt_month; scalar_t__ dt_day; scalar_t__ dt_hour; scalar_t__ dt_minute; scalar_t__ dt_second; int dt_gmtoff; } ;
typedef  TYPE_1__ iso9660_dtime_t ;

/* Variables and functions */
 int /*<<< orphan*/  gmtime_r (int /*<<< orphan*/ *,struct tm*) ; 
 int /*<<< orphan*/  localtime_r (int /*<<< orphan*/ *,struct tm*) ; 
 int /*<<< orphan*/  memcpy (struct tm*,struct tm*,int) ; 
 int /*<<< orphan*/  memset (struct tm*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  timegm (struct tm*) ; 

bool
iso9660_get_dtime (const iso9660_dtime_t *idr_date, bool b_localtime,
                   /*out*/ struct tm *p_tm)
{
  if (!idr_date) return false;

  /*
     Section 9.1.5 of ECMA 119 says:
     If all seven numbers are zero, it shall mean that the date and
     time are not specified.

     HACK: However we've seen it happen that everything except gmtoff
     is zero and the expected date is the beginning of the epoch. So
     we accept 6 numbers being zero. I'm also not sure if using the
     beginning of the Epoch is also the right thing to do either.
  */

  if ( 0 == idr_date->dt_year   && 0 == idr_date->dt_month &&
       0 == idr_date->dt_day    && 0 == idr_date->dt_hour  &&
       0 == idr_date->dt_minute && 0 == idr_date->dt_second ) {
    time_t t = 0;
    struct tm temp_tm;
    localtime_r(&t, &temp_tm);

    memcpy(p_tm, &temp_tm, sizeof(struct tm));
    return true;
  }

  memset(p_tm, 0, sizeof(struct tm));

  p_tm->tm_year   = idr_date->dt_year;
  p_tm->tm_mon    = idr_date->dt_month - 1;
  p_tm->tm_mday   = idr_date->dt_day;
  p_tm->tm_hour   = idr_date->dt_hour;
  p_tm->tm_min    = idr_date->dt_minute;
  p_tm->tm_sec    = idr_date->dt_second - idr_date->dt_gmtoff * (15 * 60);
  p_tm->tm_isdst  = -1; /* information not available */

#ifdef HAVE_STRUCT_TM_TM_ZONE
  /* Initialize everything */
  p_tm->tm_zone   = 0;
#endif

  /* Recompute tm_wday and tm_yday via mktime. mktime will also renormalize
     date values to account for the timezone offset. */
  {
    time_t t = 0;
    struct tm temp_tm;

    t = timegm(p_tm);

    if (b_localtime)
      localtime_r(&t, &temp_tm);
    else
      gmtime_r(&t, &temp_tm);

    memcpy(p_tm, &temp_tm, sizeof(struct tm));
  }


  return true;
}