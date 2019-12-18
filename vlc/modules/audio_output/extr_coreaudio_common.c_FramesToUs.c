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
typedef  int /*<<< orphan*/  uint64_t ;
struct aout_sys_common {int /*<<< orphan*/  i_rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_tick_from_samples (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline vlc_tick_t
FramesToUs(struct aout_sys_common *p_sys, uint64_t i_nb_frames)
{
    return vlc_tick_from_samples(i_nb_frames, p_sys->i_rate);
}