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

/* Variables and functions */
 scalar_t__ GPS_UTC_EPOCH_OFFSET ; 

__attribute__((used)) static inline time_t atsc_a65_GPSTimeToEpoch( time_t i_seconds, time_t i_gpstoepoch_leaptime_offset )
{
    return i_seconds + GPS_UTC_EPOCH_OFFSET - i_gpstoepoch_leaptime_offset;
}