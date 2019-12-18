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

/* Variables and functions */
 void* CreateEventW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int num_synced ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * start_event ; 
 int /*<<< orphan*/ * stop_event ; 

__attribute__((used)) static void init_thread_sync_helpers(void)
{
  start_event = CreateEventW(NULL, TRUE, FALSE, NULL);
  ok(start_event != NULL, "CreateEvent failed\n");
  stop_event = CreateEventW(NULL, TRUE, FALSE, NULL);
  ok(stop_event != NULL, "CreateEvent failed\n");
  num_synced = -1;
}