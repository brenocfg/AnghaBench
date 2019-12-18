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
struct TYPE_3__ {int /*<<< orphan*/  no_address; void* by_name; void* by_address; } ;
typedef  TYPE_1__ EtcHosts ;

/* Variables and functions */
 int /*<<< orphan*/  etc_hosts_item_by_name_free ; 
 int /*<<< orphan*/  etc_hosts_item_free ; 
 void* hashmap_free_with_destructor (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_free_free (int /*<<< orphan*/ ) ; 

void etc_hosts_free(EtcHosts *hosts) {
        hosts->by_address = hashmap_free_with_destructor(hosts->by_address, etc_hosts_item_free);
        hosts->by_name = hashmap_free_with_destructor(hosts->by_name, etc_hosts_item_by_name_free);
        hosts->no_address = set_free_free(hosts->no_address);
}