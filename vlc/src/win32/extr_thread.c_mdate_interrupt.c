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
typedef  int vlc_tick_t ;
typedef  int ULONGLONG ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int CLOCK_FREQ ; 
 int /*<<< orphan*/  QueryUnbiasedInterruptTime (int*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  static_assert (int,char*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static vlc_tick_t mdate_interrupt (void)
{
    ULONGLONG ts;
    BOOL ret;

    ret = QueryUnbiasedInterruptTime (&ts);
    if (unlikely(!ret))
        abort ();

    /* hundreds of nanoseconds */
    static_assert ((10000000 % CLOCK_FREQ) == 0, "Broken frequencies ratio");
    return ts / (10000000 / CLOCK_FREQ);
}