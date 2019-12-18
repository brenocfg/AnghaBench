#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  call; int /*<<< orphan*/  name; int /*<<< orphan*/  nuid; } ;
typedef  TYPE_4__ vbi_network ;
struct TYPE_12__ {int /*<<< orphan*/  pgno; } ;
struct TYPE_11__ {int subno; scalar_t__ header_update; scalar_t__ clock_update; int /*<<< orphan*/  pgno; } ;
struct TYPE_13__ {TYPE_4__ network; TYPE_2__ caption; TYPE_1__ ttx_page; } ;
struct TYPE_15__ {scalar_t__ type; TYPE_3__ ev; } ;
typedef  TYPE_5__ vbi_event ;
struct TYPE_16__ {TYPE_7__* p_sys; } ;
typedef  TYPE_6__ decoder_t ;
struct TYPE_17__ {scalar_t__ i_last_page; int b_update; } ;
typedef  TYPE_7__ decoder_sys_t ;

/* Variables and functions */
 scalar_t__ VBI_EVENT_ASPECT ; 
 scalar_t__ VBI_EVENT_CAPTION ; 
 scalar_t__ VBI_EVENT_CLOSE ; 
 scalar_t__ VBI_EVENT_NETWORK ; 
 scalar_t__ VBI_EVENT_NETWORK_ID ; 
 scalar_t__ VBI_EVENT_PROG_INFO ; 
 scalar_t__ VBI_EVENT_TRIGGER ; 
 scalar_t__ VBI_EVENT_TTX_PAGE ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_6__*,char*,...) ; 
 int /*<<< orphan*/  msg_Info (TYPE_6__*,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ vbi_bcd2dec (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void EventHandler( vbi_event *ev, void *user_data )
{
    decoder_t *p_dec        = (decoder_t *)user_data;
    decoder_sys_t *p_sys    = p_dec->p_sys;

    if( ev->type == VBI_EVENT_TTX_PAGE )
    {
#ifdef ZVBI_DEBUG
        msg_Info( p_dec, "Page %03x.%02x ",
                    ev->ev.ttx_page.pgno,
                    ev->ev.ttx_page.subno & 0xFF);
#endif
        if( p_sys->i_last_page == vbi_bcd2dec( ev->ev.ttx_page.pgno ) )
            p_sys->b_update = true;
#ifdef ZVBI_DEBUG
        if( ev->ev.ttx_page.clock_update )
            msg_Dbg( p_dec, "clock" );
        if( ev->ev.ttx_page.header_update )
            msg_Dbg( p_dec, "header" );
#endif
    }
    else if( ev->type == VBI_EVENT_CLOSE )
        msg_Dbg( p_dec, "Close event" );
    else if( ev->type == VBI_EVENT_CAPTION )
        msg_Dbg( p_dec, "Caption line: %x", ev->ev.caption.pgno );
    else if( ev->type == VBI_EVENT_NETWORK )
    {
        msg_Dbg( p_dec, "Network change");
        vbi_network n = ev->ev.network;
        msg_Dbg( p_dec, "Network id:%d name: %s, call: %s ", n.nuid, n.name, n.call );
    }
    else if( ev->type == VBI_EVENT_TRIGGER )
        msg_Dbg( p_dec, "Trigger event" );
    else if( ev->type == VBI_EVENT_ASPECT )
        msg_Dbg( p_dec, "Aspect update" );
    else if( ev->type == VBI_EVENT_PROG_INFO )
        msg_Dbg( p_dec, "Program info received" );
    else if( ev->type == VBI_EVENT_NETWORK_ID )
        msg_Dbg( p_dec, "Network ID changed" );
}