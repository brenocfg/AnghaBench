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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {TYPE_1__* p_si; } ;
struct TYPE_7__ {scalar_t__ type; TYPE_2__ u; } ;
typedef  TYPE_3__ ts_pid_t ;
struct TYPE_5__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 scalar_t__ TYPE_SI ; 
 scalar_t__ dvbpsi_decoder_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvbpsi_packet_push (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 

void ts_si_Packet_Push( ts_pid_t *p_pid, const uint8_t *p_pktbuffer )
{
    if( likely(p_pid->type == TYPE_SI) &&
        dvbpsi_decoder_present( p_pid->u.p_si->handle ) )
        dvbpsi_packet_push( p_pid->u.p_si->handle, (uint8_t *) p_pktbuffer );
}