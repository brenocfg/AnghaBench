#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_4__ {int limit; int /*<<< orphan*/  min; } ;
typedef  TYPE_1__ stats ;

/* Variables and functions */
 int /*<<< orphan*/  UINT64_MAX ; 
 TYPE_1__* zcalloc (int) ; 

stats *stats_alloc(uint64_t max) {
    uint64_t limit = max + 1;
    stats *s = zcalloc(sizeof(stats) + sizeof(uint64_t) * limit);
    s->limit = limit;
    s->min   = UINT64_MAX;
    return s;
}