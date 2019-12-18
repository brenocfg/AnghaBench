#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hashmap_type_info {int entry_size; int n_direct_buckets; } ;
typedef  int /*<<< orphan*/  dib_raw_t ;
struct TYPE_4__ {int /*<<< orphan*/  storage; } ;
struct TYPE_5__ {size_t type; TYPE_1__ direct; int /*<<< orphan*/  has_indirect; } ;
typedef  TYPE_2__ HashmapBase ;

/* Variables and functions */
 int /*<<< orphan*/  DIB_RAW_INIT ; 
 int /*<<< orphan*/  assert (int) ; 
 struct hashmap_type_info* hashmap_type_info ; 
 void* mempset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void reset_direct_storage(HashmapBase *h) {
        const struct hashmap_type_info *hi = &hashmap_type_info[h->type];
        void *p;

        assert(!h->has_indirect);

        p = mempset(h->direct.storage, 0, hi->entry_size * hi->n_direct_buckets);
        memset(p, DIB_RAW_INIT, sizeof(dib_raw_t) * hi->n_direct_buckets);
}