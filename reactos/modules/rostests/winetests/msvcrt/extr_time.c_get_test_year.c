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
typedef  int time_t ;
struct tm {int tm_year; } ;

/* Variables and functions */
 int SECSPERDAY ; 
 struct tm* localtime (int*) ; 
 int time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_test_year(time_t *start)
{
    time_t now = time(NULL);
    struct tm *tm = localtime(&now);

    /* compute start of year in seconds */
    *start = SECSPERDAY * ((tm->tm_year - 70) * 365 +
                           (tm->tm_year - 69) / 4 -
                           (tm->tm_year - 1) / 100 +
                           (tm->tm_year + 299) / 400);
    return tm->tm_year;
}