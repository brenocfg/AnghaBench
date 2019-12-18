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
struct TYPE_5__ {int s_b1; int s_b2; int s_b3; int s_b4; } ;
struct TYPE_6__ {int S_addr; TYPE_1__ S_un_b; } ;
struct TYPE_7__ {TYPE_2__ S_un; } ;
typedef  TYPE_3__ IN_ADDR ;

/* Variables and functions */

__attribute__((used)) static void init_ip4(IN_ADDR* addr, const int src[4])
{
    if (!src || src[0] == -1)
    {
        addr->S_un.S_addr = 0xabababab;
    }
    else
    {
        addr->S_un.S_un_b.s_b1 = src[0];
        addr->S_un.S_un_b.s_b2 = src[1];
        addr->S_un.S_un_b.s_b3 = src[2];
        addr->S_un.S_un_b.s_b4 = src[3];
    }
}