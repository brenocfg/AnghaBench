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
typedef  scalar_t__ time_t ;
struct tm {int tm_isdst; } ;

/* Variables and functions */
 scalar_t__ _dstbias ; 
 scalar_t__ _isdstime (scalar_t__) ; 
 scalar_t__ _timezone ; 
 int /*<<< orphan*/  _tz_is_set ; 
 int /*<<< orphan*/  _tzset () ; 
 struct tm* gmtime (scalar_t__*) ; 

struct tm *
localtime(const time_t *ptime)
{
    time_t time = *ptime;
    struct tm * ptm;

    /* Check for invalid time value */
    if (time < 0)
    {
        return 0;
    }

    /* Never without */
    if (!_tz_is_set)
        _tzset();

    /* Check for overflow */

    /* Correct for timezone */
    time -= _timezone;
#if 0
    /* Correct for daylight saving */
    if (_isdstime(time))
    {
        ptm->tm_isdst = 1;
        time -= _dstbias;
    }
#endif
    ptm = gmtime(&time);

    return ptm;
}