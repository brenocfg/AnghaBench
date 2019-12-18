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
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  int /*<<< orphan*/  ULONGLONG ;

/* Variables and functions */
 int CLOCK_FREQ ; 
 int /*<<< orphan*/  GetTickCount64 () ; 
 int /*<<< orphan*/  VLC_TICK_FROM_MS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  static_assert (int,char*) ; 

__attribute__((used)) static vlc_tick_t mdate_tick (void)
{
    ULONGLONG ts = GetTickCount64 ();

    /* milliseconds */
    static_assert ((CLOCK_FREQ % 1000) == 0, "Broken frequencies ratio");
    return VLC_TICK_FROM_MS( ts );
}