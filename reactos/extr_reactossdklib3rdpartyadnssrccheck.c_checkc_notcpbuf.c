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
typedef  TYPE_3__* adns_state ;
struct TYPE_6__ {int /*<<< orphan*/  used; } ;
struct TYPE_5__ {int /*<<< orphan*/  used; } ;
struct TYPE_7__ {int /*<<< orphan*/  tcprecv_skip; TYPE_2__ tcprecv; TYPE_1__ tcpsend; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void checkc_notcpbuf(adns_state ads) {
  assert(!ads->tcpsend.used);
  assert(!ads->tcprecv.used);
  assert(!ads->tcprecv_skip);
}