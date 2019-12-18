#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_13__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_14__ {int autodetect; int /*<<< orphan*/  session; int /*<<< orphan*/ * srtp; } ;
typedef  TYPE_2__ demux_sys_t ;
struct TYPE_15__ {int i_buffer; int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_3__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  block_Release (TYPE_3__*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  rtp_autodetect (TYPE_1__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int rtp_ptype (TYPE_3__*) ; 
 int /*<<< orphan*/  rtp_queue (TYPE_1__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ srtp_recv (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void rtp_process (demux_t *demux, block_t *block)
{
    demux_sys_t *sys = demux->p_sys;

    if (block->i_buffer < 2)
        goto drop;
    const uint8_t ptype = rtp_ptype (block);
    if (ptype >= 72 && ptype <= 76)
        goto drop; /* Muxed RTCP, ignore for now FIXME */

#ifdef HAVE_SRTP
    if (sys->srtp != NULL)
    {
        size_t len = block->i_buffer;
        if (srtp_recv (sys->srtp, block->p_buffer, &len))
        {
            msg_Dbg (demux, "SRTP authentication/decryption failed");
            goto drop;
        }
        block->i_buffer = len;
    }
#endif

    /* TODO: use SDP and get rid of this hack */
    if (unlikely(sys->autodetect))
    {   /* Autodetect payload type, _before_ rtp_queue() */
        rtp_autodetect (demux, sys->session, block);
        sys->autodetect = false;
    }

    rtp_queue (demux, sys->session, block);
    return;
drop:
    block_Release (block);
}