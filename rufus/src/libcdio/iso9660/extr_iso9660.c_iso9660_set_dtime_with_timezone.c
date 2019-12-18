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
struct tm {int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_mday; scalar_t__ tm_mon; int /*<<< orphan*/  tm_year; } ;
struct TYPE_4__ {int dt_gmtoff; int /*<<< orphan*/  dt_second; int /*<<< orphan*/  dt_minute; int /*<<< orphan*/  dt_hour; int /*<<< orphan*/  dt_day; scalar_t__ dt_month; int /*<<< orphan*/  dt_year; } ;
typedef  TYPE_1__ iso9660_dtime_t ;

/* Variables and functions */
 int /*<<< orphan*/  cdio_warn (char*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void
iso9660_set_dtime_with_timezone (const struct tm *p_tm,
                                 int time_zone,
                                 /*out*/ iso9660_dtime_t *p_idr_date)
{
  memset (p_idr_date, 0, 7);

  if (!p_tm) return;

  p_idr_date->dt_year   = p_tm->tm_year;
  p_idr_date->dt_month  = p_tm->tm_mon + 1;
  p_idr_date->dt_day    = p_tm->tm_mday;
  p_idr_date->dt_hour   = p_tm->tm_hour;
  p_idr_date->dt_minute = p_tm->tm_min;
  p_idr_date->dt_second = p_tm->tm_sec;

  /* The ISO 9660 timezone is in the range -48..+52 and each unit
     represents a 15-minute interval. */
  p_idr_date->dt_gmtoff = time_zone / 15;

  if (p_idr_date->dt_gmtoff < -48 ) {

    cdio_warn ("Converted ISO 9660 timezone %d is less than -48. Adjusted",
               p_idr_date->dt_gmtoff);
    p_idr_date->dt_gmtoff = -48;
  } else if (p_idr_date->dt_gmtoff > 52) {
    cdio_warn ("Converted ISO 9660 timezone %d is over 52. Adjusted",
               p_idr_date->dt_gmtoff);
    p_idr_date->dt_gmtoff = 52;
  }
}