#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_3__* module_blocked_handle; } ;
struct TYPE_6__ {TYPE_1__ bpop; } ;
typedef  TYPE_2__ client ;
struct TYPE_7__ {int blocked_on_keys; } ;
typedef  TYPE_3__ RedisModuleBlockedClient ;

/* Variables and functions */

int moduleClientIsBlockedOnKeys(client *c) {
    RedisModuleBlockedClient *bc = c->bpop.module_blocked_handle;
    return bc->blocked_on_keys;
}