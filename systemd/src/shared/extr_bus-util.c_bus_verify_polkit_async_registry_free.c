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
typedef  int /*<<< orphan*/  Hashmap ;

/* Variables and functions */
 int /*<<< orphan*/  async_polkit_query_free ; 
 int /*<<< orphan*/  hashmap_free_with_destructor (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void bus_verify_polkit_async_registry_free(Hashmap *registry) {
#if ENABLE_POLKIT
        hashmap_free_with_destructor(registry, async_polkit_query_free);
#endif
}