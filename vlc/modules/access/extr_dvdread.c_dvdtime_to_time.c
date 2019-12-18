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
typedef  scalar_t__ vlc_tick_t ;
typedef  int int64_t ;
struct TYPE_3__ {int hour; int minute; int second; int frame_u; } ;
typedef  TYPE_1__ dvd_time_t ;

/* Variables and functions */
 double BCD2D (int) ; 
 scalar_t__ VLC_TICK_FROM_MS (double) ; 
 scalar_t__ vlc_tick_from_sec (int) ; 

__attribute__((used)) static vlc_tick_t dvdtime_to_time( dvd_time_t *dtime )
{
/* Macro to convert Binary Coded Decimal to Decimal */
#define BCD2D(__x__) (((__x__ & 0xf0) >> 4) * 10 + (__x__ & 0x0f))

    double f_fps, f_ms;

    int64_t sec = (int64_t)(BCD2D(dtime->hour)) * 60 * 60;
    sec += (int64_t)(BCD2D(dtime->minute)) * 60;
    sec += (int64_t)(BCD2D(dtime->second));

    switch((dtime->frame_u & 0xc0) >> 6)
    {
    case 1:
        f_fps = 25.0;
        break;
    case 3:
        f_fps = 29.97;
        break;
    default:
        f_fps = 2500.0;
        break;
    }
    f_ms = BCD2D(dtime->frame_u&0x3f) * 1000.0 / f_fps;
    return vlc_tick_from_sec(sec) + VLC_TICK_FROM_MS(f_ms);
}