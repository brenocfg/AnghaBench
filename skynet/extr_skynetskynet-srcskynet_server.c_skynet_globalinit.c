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
struct TYPE_2__ {int init; int /*<<< orphan*/  handle_key; scalar_t__ monitor_exit; scalar_t__ total; } ;

/* Variables and functions */
 TYPE_1__ G_NODE ; 
 int /*<<< orphan*/  THREAD_MAIN ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pthread_key_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skynet_initthread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

void 
skynet_globalinit(void) {
	G_NODE.total = 0;
	G_NODE.monitor_exit = 0;
	G_NODE.init = 1;
	if (pthread_key_create(&G_NODE.handle_key, NULL)) {
		fprintf(stderr, "pthread_key_create failed");
		exit(1);
	}
	// set mainthread's key
	skynet_initthread(THREAD_MAIN);
}