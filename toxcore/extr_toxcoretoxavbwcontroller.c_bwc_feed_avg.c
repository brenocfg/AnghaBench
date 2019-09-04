#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  rb; } ;
struct TYPE_5__ {TYPE_1__ rcvpkt; } ;
typedef  TYPE_2__ BWController ;

/* Variables and functions */
 int /*<<< orphan*/  rb_read (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  rb_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void bwc_feed_avg(BWController *bwc, uint32_t bytes)
{
    uint32_t *p;

    rb_read(bwc->rcvpkt.rb, (void **) &p);
    rb_write(bwc->rcvpkt.rb, p);

    *p = bytes;
}