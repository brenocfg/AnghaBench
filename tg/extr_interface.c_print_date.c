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
struct tm {size_t tm_mon; scalar_t__ tm_year; int /*<<< orphan*/  tm_mday; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; } ;
struct in_ev {int dummy; } ;

/* Variables and functions */
 struct tm* localtime (void*) ; 
 int /*<<< orphan*/ * monthes ; 
 int /*<<< orphan*/  mprintf (struct in_ev*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 long time (int /*<<< orphan*/ ) ; 

void print_date (struct in_ev *ev, long t) {
  struct tm *tm = localtime ((void *)&t);
  if (time (0) - t < 12 * 60 * 60) {
    mprintf (ev, "[%02d:%02d] ", tm->tm_hour, tm->tm_min);
  } else if (time (0) - t < 24 * 60 * 60 * 180) {
    mprintf (ev, "[%02d %s]", tm->tm_mday, monthes[tm->tm_mon]);
  } else {
    mprintf (ev, "[%02d %s %d]", tm->tm_mday, monthes[tm->tm_mon], tm->tm_year + 1900);
  }
}