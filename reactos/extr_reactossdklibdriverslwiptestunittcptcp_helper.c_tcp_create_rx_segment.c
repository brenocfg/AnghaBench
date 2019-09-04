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
typedef  int /*<<< orphan*/  u8_t ;
typedef  scalar_t__ u32_t ;
struct tcp_pcb {scalar_t__ lastack; scalar_t__ rcv_nxt; int /*<<< orphan*/  local_port; int /*<<< orphan*/  remote_port; int /*<<< orphan*/  local_ip; int /*<<< orphan*/  remote_ip; } ;
struct pbuf {int dummy; } ;

/* Variables and functions */
 struct pbuf* tcp_create_segment (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

struct pbuf*
tcp_create_rx_segment(struct tcp_pcb* pcb, void* data, size_t data_len, u32_t seqno_offset,
                      u32_t ackno_offset, u8_t headerflags)
{
  return tcp_create_segment(&pcb->remote_ip, &pcb->local_ip, pcb->remote_port, pcb->local_port,
    data, data_len, pcb->rcv_nxt + seqno_offset, pcb->lastack + ackno_offset, headerflags);
}