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
struct TYPE_4__ {size_t used; struct TYPE_4__* array; int /*<<< orphan*/  member; } ;
typedef  TYPE_1__ geoArray ;

/* Variables and functions */
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (TYPE_1__*) ; 

void geoArrayFree(geoArray *ga) {
    size_t i;
    for (i = 0; i < ga->used; i++) sdsfree(ga->array[i].member);
    zfree(ga->array);
    zfree(ga);
}