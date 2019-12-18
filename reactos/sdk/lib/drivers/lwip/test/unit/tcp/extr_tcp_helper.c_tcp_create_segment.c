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
typedef  int /*<<< orphan*/  u32_t ;
typedef  int /*<<< orphan*/  u16_t ;
struct pbuf {int dummy; } ;
typedef  int /*<<< orphan*/  ip_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  TCP_WND ; 
 struct pbuf* tcp_create_segment_wnd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct pbuf*
tcp_create_segment(ip_addr_t* src_ip, ip_addr_t* dst_ip,
                   u16_t src_port, u16_t dst_port, void* data, size_t data_len,
                   u32_t seqno, u32_t ackno, u8_t headerflags)
{
  return tcp_create_segment_wnd(src_ip, dst_ip, src_port, dst_port, data,
    data_len, seqno, ackno, headerflags, TCP_WND);
}