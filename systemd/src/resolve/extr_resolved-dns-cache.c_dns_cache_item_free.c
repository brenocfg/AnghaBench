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
struct TYPE_4__ {int /*<<< orphan*/  key; int /*<<< orphan*/  rr; } ;
typedef  TYPE_1__ DnsCacheItem ;

/* Variables and functions */
 int /*<<< orphan*/  dns_resource_key_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dns_resource_record_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void dns_cache_item_free(DnsCacheItem *i) {
        if (!i)
                return;

        dns_resource_record_unref(i->rr);
        dns_resource_key_unref(i->key);
        free(i);
}