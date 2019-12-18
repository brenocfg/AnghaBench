#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mempool {int /*<<< orphan*/  tile_size; } ;

/* Variables and functions */
 void* mempool_alloc_tile (struct mempool*) ; 
 int /*<<< orphan*/  memzero (void*,int /*<<< orphan*/ ) ; 

void* mempool_alloc0_tile(struct mempool *mp) {
        void *p;

        p = mempool_alloc_tile(mp);
        if (p)
                memzero(p, mp->tile_size);
        return p;
}