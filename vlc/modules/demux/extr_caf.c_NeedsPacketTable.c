#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  i_frame_length; int /*<<< orphan*/  i_bytes_per_frame; } ;
struct TYPE_6__ {TYPE_1__ audio; } ;
struct TYPE_7__ {TYPE_2__ fmt; } ;
typedef  TYPE_3__ demux_sys_t ;

/* Variables and functions */

__attribute__((used)) static inline bool NeedsPacketTable( demux_sys_t *p_sys )
{
    return ( !p_sys->fmt.audio.i_bytes_per_frame || !p_sys->fmt.audio.i_frame_length );
}