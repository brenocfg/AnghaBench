#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tick_t ;
struct TYPE_6__ {int /*<<< orphan*/  QuadPart; } ;
struct TYPE_7__ {TYPE_1__ freq; } ;
struct TYPE_9__ {TYPE_2__ perf; } ;
struct TYPE_8__ {int /*<<< orphan*/  QuadPart; } ;
typedef  TYPE_3__ LARGE_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  QueryPerformanceCounter (TYPE_3__*) ; 
 int /*<<< orphan*/  abort () ; 
 TYPE_4__ clk ; 
 int /*<<< orphan*/  vlc_tick_from_frac (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static vlc_tick_t mdate_perf (void)
{
    /* We don't need the real date, just the value of a high precision timer */
    LARGE_INTEGER counter;
    if (!QueryPerformanceCounter (&counter))
        abort ();

    /* Convert to from (1/freq) to microsecond resolution */
    /* We need to split the division to avoid 63-bits overflow */
    return vlc_tick_from_frac(counter.QuadPart, clk.perf.freq.QuadPart);
}