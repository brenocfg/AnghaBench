#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* bits; } ;
struct TYPE_6__ {size_t classCount; struct TYPE_6__* classList; TYPE_1__ u; scalar_t__ converted; } ;
typedef  TYPE_2__ regexp_t ;
typedef  size_t UINT ;

/* Variables and functions */
 int /*<<< orphan*/  heap_free (TYPE_2__*) ; 

void regexp_destroy(regexp_t *re)
{
    if (re->classList) {
        UINT i;
        for (i = 0; i < re->classCount; i++) {
            if (re->classList[i].converted)
                heap_free(re->classList[i].u.bits);
            re->classList[i].u.bits = NULL;
        }
        heap_free(re->classList);
    }
    heap_free(re);
}