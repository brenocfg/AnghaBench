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
struct vlc_memstream {int dummy; } ;
struct TYPE_3__ {long long rem; int /*<<< orphan*/  quot; } ;
typedef  TYPE_1__ lldiv_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_FREQ ; 
 TYPE_1__ lldiv (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vlc_memstream_printf (struct vlc_memstream*,char*,int /*<<< orphan*/ ,long long,long long) ; 

__attribute__((used)) static void write_duration(struct vlc_memstream *stream, vlc_tick_t duration)
{
    lldiv_t d;
    long long sec;

    duration /= CLOCK_FREQ;
    d = lldiv(duration, 60);
    sec = d.rem;
    d = lldiv(d.quot, 60);
    vlc_memstream_printf(stream, "%02lld:%02lld:%02lld", d.quot, d.rem, sec);
}