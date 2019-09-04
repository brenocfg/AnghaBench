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
struct TYPE_3__ {scalar_t__ daylightBias; scalar_t__ standardBias; int /*<<< orphan*/  daylightDate; int /*<<< orphan*/  standardDate; } ;
typedef  TYPE_1__ DateInstance ;
typedef  scalar_t__ DOUBLE ;

/* Variables and functions */
 scalar_t__ convert_time (int,int /*<<< orphan*/ ) ; 
 scalar_t__ isnan (scalar_t__) ; 
 int year_from_time (scalar_t__) ; 

__attribute__((used)) static inline DOUBLE daylight_saving_ta(DOUBLE time, DateInstance *date)
{
    int year = year_from_time(time);
    DOUBLE standardTime, daylightTime;

    if(isnan(time))
        return 0;

    standardTime = convert_time(year, date->standardDate);
    daylightTime = convert_time(year, date->daylightDate);

    if(isnan(standardTime) || isnan(daylightTime))
        return 0;
    else if(standardTime > daylightTime) {
        if(daylightTime <= time && time < standardTime)
            return date->daylightBias;

        return date->standardBias;
    }
    else {
        if(standardTime <= time && time < daylightTime)
            return date->standardBias;

        return date->daylightBias;
    }
}