#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_8__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_10__ {TYPE_2__ values; TYPE_1__ keys; } ;
typedef  TYPE_3__ IteratedCache ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 TYPE_3__* mfree (TYPE_3__*) ; 

IteratedCache *iterated_cache_free(IteratedCache *cache) {
        if (cache) {
                free(cache->keys.ptr);
                free(cache->values.ptr);
        }

        return mfree(cache);
}