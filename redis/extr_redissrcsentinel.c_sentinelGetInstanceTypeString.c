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
struct TYPE_3__ {int flags; } ;
typedef  TYPE_1__ sentinelRedisInstance ;

/* Variables and functions */
 int SRI_MASTER ; 
 int SRI_SENTINEL ; 
 int SRI_SLAVE ; 

char *sentinelGetInstanceTypeString(sentinelRedisInstance *ri) {
    if (ri->flags & SRI_MASTER) return "master";
    else if (ri->flags & SRI_SLAVE) return "slave";
    else if (ri->flags & SRI_SENTINEL) return "sentinel";
    else return "unknown";
}