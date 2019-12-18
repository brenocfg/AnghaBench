#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint64_t ;
struct TYPE_4__ {size_t i_bytes_per_frame; size_t i_frame_length; } ;
struct TYPE_5__ {TYPE_1__ fmt; } ;
typedef  TYPE_2__ aout_sys_t ;

/* Variables and functions */

__attribute__((used)) static inline size_t
frames_to_bytes( aout_sys_t *p_sys, uint64_t i_frames )
{
    return i_frames * p_sys->fmt.i_bytes_per_frame / p_sys->fmt.i_frame_length;
}