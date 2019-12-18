#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  numele; } ;
typedef  TYPE_2__ rax ;
struct TYPE_8__ {TYPE_1__* cluster; } ;
struct TYPE_6__ {int /*<<< orphan*/  slots_keys_count; TYPE_2__* slots_to_keys; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_LAZY_FREE ; 
 int /*<<< orphan*/  atomicIncr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bioCreateBackgroundJob (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  lazyfree_objects ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* raxNew () ; 
 TYPE_3__ server ; 

void slotToKeyFlushAsync(void) {
    rax *old = server.cluster->slots_to_keys;

    server.cluster->slots_to_keys = raxNew();
    memset(server.cluster->slots_keys_count,0,
           sizeof(server.cluster->slots_keys_count));
    atomicIncr(lazyfree_objects,old->numele);
    bioCreateBackgroundJob(BIO_LAZY_FREE,NULL,NULL,old);
}