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
typedef  size_t uint64_t ;
struct aout_sys_common {size_t i_bytes_per_frame; size_t i_frame_length; } ;

/* Variables and functions */

__attribute__((used)) static inline size_t
FramesToBytes(struct aout_sys_common *p_sys, uint64_t i_frames)
{
    return i_frames * p_sys->i_bytes_per_frame / p_sys->i_frame_length;
}