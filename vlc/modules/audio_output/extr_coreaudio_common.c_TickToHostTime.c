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
typedef  int vlc_tick_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {int denom; int numer; } ;

/* Variables and functions */
 int /*<<< orphan*/  NS_FROM_VLC_TICK (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__ tinfo ; 

__attribute__((used)) static inline uint64_t
TickToHostTime(vlc_tick_t i_us)
{
    assert(tinfo.denom != 0);
    return NS_FROM_VLC_TICK(i_us * tinfo.denom / tinfo.numer);
}