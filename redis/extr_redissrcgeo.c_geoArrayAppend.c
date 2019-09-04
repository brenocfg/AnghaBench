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
typedef  int /*<<< orphan*/  geoPoint ;
struct TYPE_3__ {int used; int buckets; int /*<<< orphan*/ * array; } ;
typedef  TYPE_1__ geoArray ;

/* Variables and functions */
 int /*<<< orphan*/ * zrealloc (int /*<<< orphan*/ *,int) ; 

geoPoint *geoArrayAppend(geoArray *ga) {
    if (ga->used == ga->buckets) {
        ga->buckets = (ga->buckets == 0) ? 8 : ga->buckets*2;
        ga->array = zrealloc(ga->array,sizeof(geoPoint)*ga->buckets);
    }
    geoPoint *gp = ga->array+ga->used;
    ga->used++;
    return gp;
}