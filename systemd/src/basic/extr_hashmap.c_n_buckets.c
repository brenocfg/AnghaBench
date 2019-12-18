#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int n_direct_buckets; } ;
struct TYPE_5__ {int n_buckets; } ;
struct TYPE_6__ {size_t type; TYPE_1__ indirect; scalar_t__ has_indirect; } ;
typedef  TYPE_2__ HashmapBase ;

/* Variables and functions */
 TYPE_4__* hashmap_type_info ; 

__attribute__((used)) static unsigned n_buckets(HashmapBase *h) {
        return h->has_indirect ? h->indirect.n_buckets
                               : hashmap_type_info[h->type].n_direct_buckets;
}