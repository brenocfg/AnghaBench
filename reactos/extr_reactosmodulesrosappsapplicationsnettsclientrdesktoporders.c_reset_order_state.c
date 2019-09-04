#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  order_type; } ;
struct TYPE_5__ {TYPE_4__ order_state; } ;
struct TYPE_6__ {TYPE_1__ orders; } ;
typedef  TYPE_2__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  RDP_ORDER_PATBLT ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 

void
reset_order_state(RDPCLIENT * This)
{
	memset(&This->orders.order_state, 0, sizeof(This->orders.order_state));
	This->orders.order_state.order_type = RDP_ORDER_PATBLT;
}