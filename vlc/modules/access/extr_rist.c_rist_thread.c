#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_13__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ stream_t ;
struct TYPE_14__ {int nack_type; TYPE_1__* flow; int /*<<< orphan*/  p_fifo; } ;
typedef  TYPE_3__ stream_sys_t ;
struct TYPE_15__ {scalar_t__ i_buffer; } ;
typedef  TYPE_4__ block_t ;
struct TYPE_12__ {int /*<<< orphan*/  fd_nack; } ;

/* Variables and functions */
#define  NACK_FMT_BITMASK 128 
 TYPE_4__* block_FifoGet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  block_Release (TYPE_4__*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  send_bbnack (TYPE_2__*,int /*<<< orphan*/ ,TYPE_4__*,int) ; 
 int /*<<< orphan*/  send_rbnack (TYPE_2__*,int /*<<< orphan*/ ,TYPE_4__*,int) ; 
 int /*<<< orphan*/  vlc_restorecancel (int) ; 
 int vlc_savecancel () ; 

__attribute__((used)) static void *rist_thread(void *data)
{
    stream_t *p_access = data;
    stream_sys_t *p_sys = p_access->p_sys;

    /* Process nacks every 5ms */
    /* We only ask for the relevant ones */
    for (;;) {
        block_t *pkt_nacks = block_FifoGet(p_sys->p_fifo);

        int canc = vlc_savecancel();

        /* there are two bytes per nack */
        uint16_t nack_count = (uint16_t)pkt_nacks->i_buffer/2;
        switch(p_sys->nack_type) {
            case NACK_FMT_BITMASK:
                send_bbnack(p_access, p_sys->flow->fd_nack, pkt_nacks, nack_count);
                break;

            default:
                send_rbnack(p_access, p_sys->flow->fd_nack, pkt_nacks, nack_count);
        }

        if (nack_count > 1)
            msg_Dbg(p_access, "Sent %u NACKs !!!", nack_count);
        block_Release(pkt_nacks);

        vlc_restorecancel (canc);
    }

    return NULL;
}