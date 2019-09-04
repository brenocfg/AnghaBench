#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ family; } ;
typedef  TYPE_1__ IP ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 scalar_t__ TOX_AF_INET ; 
 scalar_t__ TOX_AF_INET6 ; 

int to_host_family(IP *ip)
{
    if (ip->family == TOX_AF_INET) {
        ip->family = AF_INET;
        return 0;
    } else if (ip->family == TOX_AF_INET6) {
        ip->family = AF_INET6;
        return 0;
    } else {
        return -1;
    }
}