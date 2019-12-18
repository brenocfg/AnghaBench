#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tick_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* timeGetTime ) () ;} ;
struct TYPE_4__ {TYPE_1__ multimedia; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int CLOCK_FREQ ; 
 int /*<<< orphan*/  VLC_TICK_FROM_MS (int /*<<< orphan*/ ) ; 
 TYPE_2__ clk ; 
 int /*<<< orphan*/  static_assert (int,char*) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static vlc_tick_t mdate_multimedia (void)
{
    DWORD ts = clk.multimedia.timeGetTime ();

    /* milliseconds */
    static_assert ((CLOCK_FREQ % 1000) == 0, "Broken frequencies ratio");
    return VLC_TICK_FROM_MS( ts );
}