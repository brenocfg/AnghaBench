#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_5__* p_demux; } ;
typedef  TYPE_6__ vlcrdp_context_t ;
struct TYPE_17__ {TYPE_4__* primary; } ;
typedef  TYPE_7__ rdpGdi ;
struct TYPE_18__ {TYPE_7__* gdi; } ;
typedef  TYPE_8__ rdpContext ;
struct TYPE_19__ {scalar_t__ i_framebuffersize; scalar_t__ p_block; } ;
typedef  TYPE_9__ demux_sys_t ;
struct TYPE_15__ {TYPE_9__* p_sys; } ;
struct TYPE_14__ {TYPE_3__* hdc; } ;
struct TYPE_13__ {TYPE_2__* hwnd; } ;
struct TYPE_12__ {scalar_t__ ninvalid; TYPE_1__* invalid; } ;
struct TYPE_11__ {int null; } ;

/* Variables and functions */
 scalar_t__ block_Alloc (scalar_t__) ; 

__attribute__((used)) static void beginPaintHandler( rdpContext *p_context )
{
    vlcrdp_context_t * p_vlccontext = (vlcrdp_context_t *) p_context;
    demux_sys_t *p_sys = p_vlccontext->p_demux->p_sys;
    rdpGdi *p_gdi = p_context->gdi;
    p_gdi->primary->hdc->hwnd->invalid->null = 1;
    p_gdi->primary->hdc->hwnd->ninvalid = 0;
    if ( ! p_sys->p_block && p_sys->i_framebuffersize )
        p_sys->p_block = block_Alloc( p_sys->i_framebuffersize );
}