#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int linux_; } ;
typedef  TYPE_1__ dvb_int_map_t ;

/* Variables and functions */
 TYPE_1__* bsearch (int*,TYPE_1__ const*,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icmp ; 

__attribute__((used)) static int dvb_parse_int (int i, const dvb_int_map_t *map, size_t n, int def)
{
    const dvb_int_map_t *p = bsearch(&i, map, n, sizeof (*map), icmp);
    return (p != NULL) ? p->linux_ : def;
}