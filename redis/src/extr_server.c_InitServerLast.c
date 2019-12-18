#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  initial_memory_usage; int /*<<< orphan*/  jemalloc_bg_thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  bioInit () ; 
 int /*<<< orphan*/  initThreadedIO () ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  set_jemalloc_bg_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zmalloc_used_memory () ; 

void InitServerLast() {
    bioInit();
    initThreadedIO();
    set_jemalloc_bg_thread(server.jemalloc_bg_thread);
    server.initial_memory_usage = zmalloc_used_memory();
}