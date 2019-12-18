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
struct TYPE_3__ {int /*<<< orphan*/  rem; int /*<<< orphan*/  quot; } ;
typedef  TYPE_1__ lldiv_t ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  QWORD ;

/* Variables and functions */
 scalar_t__ DosTmrQueryFreq (int /*<<< orphan*/ *) ; 
 scalar_t__ DosTmrQueryTime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Q2LL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort () ; 
 TYPE_1__ lldiv (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_tick_from_samples (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_tick_from_sec (int /*<<< orphan*/ ) ; 

vlc_tick_t vlc_tick_now (void)
{
    /* We don't need the real date, just the value of a high precision timer */
    QWORD counter;
    ULONG freq;
    if (DosTmrQueryTime(&counter) || DosTmrQueryFreq(&freq))
        abort();

    /* Convert to from (1/freq) to microsecond resolution */
    /* We need to split the division to avoid 63-bits overflow */
    lldiv_t d = lldiv (Q2LL(counter), freq);

    return vlc_tick_from_sec( d.quot ) + vlc_tick_from_samples(d.rem, freq);
}