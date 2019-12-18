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
struct TYPE_4__ {int /*<<< orphan*/ * disconnect_callback; int /*<<< orphan*/ * reply_callback; } ;
typedef  TYPE_1__ RedisModuleBlockedClient ;

/* Variables and functions */
 int RM_UnblockClient (TYPE_1__*,int /*<<< orphan*/ *) ; 

int RM_AbortBlock(RedisModuleBlockedClient *bc) {
    bc->reply_callback = NULL;
    bc->disconnect_callback = NULL;
    return RM_UnblockClient(bc,NULL);
}