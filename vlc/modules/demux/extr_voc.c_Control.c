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
typedef  int /*<<< orphan*/  va_list ;
struct TYPE_8__ {int /*<<< orphan*/  s; TYPE_4__* p_sys; } ;
typedef  TYPE_3__ demux_t ;
struct TYPE_6__ {int /*<<< orphan*/  i_blockalign; } ;
struct TYPE_7__ {TYPE_1__ audio; int /*<<< orphan*/  i_bitrate; } ;
struct TYPE_9__ {TYPE_2__ fmt; int /*<<< orphan*/  i_block_end; int /*<<< orphan*/  i_block_start; } ;
typedef  TYPE_4__ demux_sys_t ;

/* Variables and functions */
 int demux_vaControlHelper (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int Control( demux_t *p_demux, int i_query, va_list args )
{
    demux_sys_t *p_sys  = p_demux->p_sys;

    return demux_vaControlHelper( p_demux->s, p_sys->i_block_start,
                                   p_sys->i_block_end,
                                   p_sys->fmt.i_bitrate,
                                   p_sys->fmt.audio.i_blockalign,
                                   i_query, args );
}