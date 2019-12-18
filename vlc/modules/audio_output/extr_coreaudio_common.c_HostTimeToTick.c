#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  int uint64_t ;
struct TYPE_2__ {int denom; int numer; } ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_TICK_FROM_NS (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__ tinfo ; 

__attribute__((used)) static inline vlc_tick_t
HostTimeToTick(uint64_t i_host_time)
{
    assert(tinfo.denom != 0);
    return VLC_TICK_FROM_NS(i_host_time * tinfo.numer / tinfo.denom);
}