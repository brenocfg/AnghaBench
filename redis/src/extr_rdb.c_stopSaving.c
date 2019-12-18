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
 int /*<<< orphan*/  REDISMODULE_EVENT_PERSISTENCE ; 
 int /*<<< orphan*/  REDISMODULE_SUBEVENT_PERSISTENCE_ENDED ; 
 int /*<<< orphan*/  REDISMODULE_SUBEVENT_PERSISTENCE_FAILED ; 
 int /*<<< orphan*/  moduleFireServerEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void stopSaving(int success) {
    /* Fire the persistence modules end event. */
    moduleFireServerEvent(REDISMODULE_EVENT_PERSISTENCE,
                          success?
                            REDISMODULE_SUBEVENT_PERSISTENCE_ENDED:
                            REDISMODULE_SUBEVENT_PERSISTENCE_FAILED,
                          NULL);
}