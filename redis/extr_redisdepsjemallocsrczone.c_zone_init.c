#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* zone_name; int version; int /*<<< orphan*/  pressure_relief; int /*<<< orphan*/  free_definite_size; int /*<<< orphan*/  memalign; TYPE_1__* introspect; int /*<<< orphan*/  batch_free; int /*<<< orphan*/  batch_malloc; int /*<<< orphan*/  destroy; int /*<<< orphan*/  realloc; int /*<<< orphan*/  free; int /*<<< orphan*/  valloc; int /*<<< orphan*/  calloc; int /*<<< orphan*/  malloc; int /*<<< orphan*/  size; } ;
struct TYPE_3__ {int /*<<< orphan*/  reinit_lock; int /*<<< orphan*/ * enumerate_unavailable_without_blocks; int /*<<< orphan*/ * discharge; int /*<<< orphan*/ * disable_discharge_checking; int /*<<< orphan*/ * enable_discharge_checking; int /*<<< orphan*/  zone_locked; int /*<<< orphan*/  statistics; int /*<<< orphan*/  force_unlock; int /*<<< orphan*/  force_lock; int /*<<< orphan*/  log; int /*<<< orphan*/  print; int /*<<< orphan*/  check; int /*<<< orphan*/  good_size; int /*<<< orphan*/  enumerator; } ;

/* Variables and functions */
 TYPE_2__ jemalloc_zone ; 
 TYPE_1__ jemalloc_zone_introspect ; 
 int /*<<< orphan*/  zone_batch_free ; 
 int /*<<< orphan*/  zone_batch_malloc ; 
 int /*<<< orphan*/  zone_calloc ; 
 int /*<<< orphan*/  zone_check ; 
 int /*<<< orphan*/  zone_destroy ; 
 int /*<<< orphan*/  zone_enumerator ; 
 int /*<<< orphan*/  zone_force_lock ; 
 int /*<<< orphan*/  zone_force_unlock ; 
 int /*<<< orphan*/  zone_free ; 
 int /*<<< orphan*/  zone_free_definite_size ; 
 int /*<<< orphan*/  zone_good_size ; 
 int /*<<< orphan*/  zone_locked ; 
 int /*<<< orphan*/  zone_log ; 
 int /*<<< orphan*/  zone_malloc ; 
 int /*<<< orphan*/  zone_memalign ; 
 int /*<<< orphan*/  zone_pressure_relief ; 
 int /*<<< orphan*/  zone_print ; 
 int /*<<< orphan*/  zone_realloc ; 
 int /*<<< orphan*/  zone_reinit_lock ; 
 int /*<<< orphan*/  zone_size ; 
 int /*<<< orphan*/  zone_statistics ; 
 int /*<<< orphan*/  zone_valloc ; 

__attribute__((used)) static void
zone_init(void) {
	jemalloc_zone.size = zone_size;
	jemalloc_zone.malloc = zone_malloc;
	jemalloc_zone.calloc = zone_calloc;
	jemalloc_zone.valloc = zone_valloc;
	jemalloc_zone.free = zone_free;
	jemalloc_zone.realloc = zone_realloc;
	jemalloc_zone.destroy = zone_destroy;
	jemalloc_zone.zone_name = "jemalloc_zone";
	jemalloc_zone.batch_malloc = zone_batch_malloc;
	jemalloc_zone.batch_free = zone_batch_free;
	jemalloc_zone.introspect = &jemalloc_zone_introspect;
	jemalloc_zone.version = 9;
	jemalloc_zone.memalign = zone_memalign;
	jemalloc_zone.free_definite_size = zone_free_definite_size;
	jemalloc_zone.pressure_relief = zone_pressure_relief;

	jemalloc_zone_introspect.enumerator = zone_enumerator;
	jemalloc_zone_introspect.good_size = zone_good_size;
	jemalloc_zone_introspect.check = zone_check;
	jemalloc_zone_introspect.print = zone_print;
	jemalloc_zone_introspect.log = zone_log;
	jemalloc_zone_introspect.force_lock = zone_force_lock;
	jemalloc_zone_introspect.force_unlock = zone_force_unlock;
	jemalloc_zone_introspect.statistics = zone_statistics;
	jemalloc_zone_introspect.zone_locked = zone_locked;
	jemalloc_zone_introspect.enable_discharge_checking = NULL;
	jemalloc_zone_introspect.disable_discharge_checking = NULL;
	jemalloc_zone_introspect.discharge = NULL;
#ifdef __BLOCKS__
	jemalloc_zone_introspect.enumerate_discharged_pointers = NULL;
#else
	jemalloc_zone_introspect.enumerate_unavailable_without_blocks = NULL;
#endif
	jemalloc_zone_introspect.reinit_lock = zone_reinit_lock;
}