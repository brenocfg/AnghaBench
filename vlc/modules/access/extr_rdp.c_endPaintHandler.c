#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* p_demux; } ;
typedef  TYPE_3__ vlcrdp_context_t ;
struct TYPE_11__ {int /*<<< orphan*/  primary_buffer; } ;
typedef  TYPE_4__ rdpGdi ;
struct TYPE_12__ {TYPE_4__* gdi; } ;
typedef  TYPE_5__ rdpContext ;
struct TYPE_13__ {TYPE_2__* p_block; int /*<<< orphan*/  i_framebuffersize; } ;
typedef  TYPE_6__ demux_sys_t ;
struct TYPE_9__ {int /*<<< orphan*/  i_buffer; int /*<<< orphan*/  p_buffer; } ;
struct TYPE_8__ {TYPE_6__* p_sys; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void endPaintHandler( rdpContext *p_context )
{
    vlcrdp_context_t * p_vlccontext = (vlcrdp_context_t *) p_context;
    demux_sys_t *p_sys = p_vlccontext->p_demux->p_sys;
    rdpGdi *p_gdi = p_context->gdi;

    if ( p_sys->p_block )
    {
        p_sys->p_block->i_buffer = p_sys->i_framebuffersize;
        memcpy( p_sys->p_block->p_buffer, p_gdi->primary_buffer, p_sys->p_block->i_buffer );
    }
}