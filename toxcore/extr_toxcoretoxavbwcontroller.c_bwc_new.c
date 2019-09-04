#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct BWController_s {int dummy; } ;
struct TYPE_9__ {scalar_t__ rb_s; int /*<<< orphan*/  rb; } ;
struct TYPE_8__ {int /*<<< orphan*/  lfu; int /*<<< orphan*/  lsu; } ;
struct TYPE_10__ {void (* mcb ) (TYPE_3__*,int /*<<< orphan*/ ,float,void*) ;TYPE_2__ rcvpkt; TYPE_1__ cycle; int /*<<< orphan*/  friend_number; int /*<<< orphan*/ * m; void* mcb_data; } ;
typedef  int /*<<< orphan*/  Messenger ;
typedef  TYPE_3__ BWController ;

/* Variables and functions */
 int BWC_AVG_PKT_COUNT ; 
 int /*<<< orphan*/  BWC_PACKET_ID ; 
 int /*<<< orphan*/  bwc_handle_data ; 
 TYPE_3__* calloc (int,int) ; 
 int /*<<< orphan*/  current_time_monotonic () ; 
 int /*<<< orphan*/  m_callback_rtp_packet (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  rb_new (int) ; 
 int /*<<< orphan*/  rb_write (int /*<<< orphan*/ ,scalar_t__) ; 

BWController *bwc_new(Messenger *m, uint32_t friendnumber,
                      void (*mcb) (BWController *, uint32_t, float, void *),
                      void *udata)
{
    BWController *retu = calloc(sizeof(struct BWController_s), 1);

    retu->mcb = mcb;
    retu->mcb_data = udata;
    retu->m = m;
    retu->friend_number = friendnumber;
    retu->cycle.lsu = retu->cycle.lfu = current_time_monotonic();
    retu->rcvpkt.rb = rb_new(BWC_AVG_PKT_COUNT);

    /* Fill with zeros */
    int i = 0;

    for (; i < BWC_AVG_PKT_COUNT; i ++)
        rb_write(retu->rcvpkt.rb, retu->rcvpkt.rb_s + i);

    m_callback_rtp_packet(m, friendnumber, BWC_PACKET_ID, bwc_handle_data, retu);

    return retu;
}