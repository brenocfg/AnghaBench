#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32b ;
struct TYPE_8__ {int /*<<< orphan*/  siaddr; int /*<<< orphan*/  lease; int /*<<< orphan*/  mask; int /*<<< orphan*/  router; int /*<<< orphan*/  ip; } ;
struct TYPE_6__ {int /*<<< orphan*/  lease; int /*<<< orphan*/  siaddr; int /*<<< orphan*/  mask; int /*<<< orphan*/  router; int /*<<< orphan*/  ip; } ;
struct TYPE_7__ {scalar_t__ xid; TYPE_1__ data; int /*<<< orphan*/  ltime; int /*<<< orphan*/  available; struct TYPE_7__* next; } ;
typedef  TYPE_2__ DHCPLIST ;
typedef  TYPE_3__ DHCPLEASE ;

/* Variables and functions */
 int /*<<< orphan*/  BUSY ; 
 TYPE_2__* list ; 

int confirm_lease( DHCPLEASE *dhcpl, u32b xid )
{
  int result = -1;
  DHCPLIST *temp;

  for( temp = list; temp; temp=temp->next )
    if( temp->xid == xid )
      {
	dhcpl->ip = temp->data.ip;
	dhcpl->router = temp->data.router;
	dhcpl->mask = temp->data.mask;
	dhcpl->lease = temp->data.lease;
	dhcpl->siaddr = temp->data.siaddr;
	temp->available = BUSY;
	temp->ltime = temp->data.lease;
	result = 0;
	return result;
      }
  return result;
}