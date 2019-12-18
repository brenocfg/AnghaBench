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
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  int uint32_t ;
struct TYPE_3__ {int quot; int rem; } ;
typedef  TYPE_1__ lldiv_t ;
typedef  int int64_t ;

/* Variables and functions */
 int CLOCK_FREQ ; 
 TYPE_1__ lldiv (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline uint32_t rtp_get_ts( vlc_tick_t i_pts )
{
    unsigned i_clock_rate = 90000;
    /* This is an overflow-proof way of doing:
     * return i_pts * (int64_t)i_clock_rate / CLOCK_FREQ;
     *
     * NOTE: this plays nice with offsets because the (equivalent)
     * calculations are linear. */
    lldiv_t q = lldiv(i_pts, CLOCK_FREQ);
    return q.quot * (int64_t)i_clock_rate
          + q.rem * (int64_t)i_clock_rate / CLOCK_FREQ;
}