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
struct timespec {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_3__ {int /*<<< orphan*/  rem; int /*<<< orphan*/  quot; } ;
typedef  TYPE_1__ lldiv_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_FREQ ; 
 int /*<<< orphan*/  NS_FROM_VLC_TICK (int /*<<< orphan*/ ) ; 
 TYPE_1__ lldiv (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct timespec timespec_from_vlc_tick (vlc_tick_t date)
{
    lldiv_t d = lldiv (date, CLOCK_FREQ);
    struct timespec ts = { d.quot, NS_FROM_VLC_TICK( d.rem ) };

    return ts;
}