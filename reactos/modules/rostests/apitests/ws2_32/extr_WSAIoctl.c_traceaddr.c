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
struct TYPE_5__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_6__ {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct TYPE_7__ {TYPE_2__ AddressIn; } ;
typedef  TYPE_3__ sockaddr_gen ;

/* Variables and functions */
 int /*<<< orphan*/  trace (char*,char*,int /*<<< orphan*/ ) ; 

void traceaddr(char* txt, sockaddr_gen a)
{
    trace("  %s.AddressIn.sin_family %x\n", txt, a.AddressIn.sin_family);
    trace("  %s.AddressIn.sin_port %x\n", txt, a.AddressIn.sin_port);
    trace("  %s.AddressIn.sin_addr.s_addr %lx\n", txt, a.AddressIn.sin_addr.s_addr);
}