#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__** argv; } ;
typedef  TYPE_2__ client ;
struct TYPE_6__ {int /*<<< orphan*/  ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  SENTINEL_HELLO_CHANNEL ; 
 int /*<<< orphan*/  addReplyError (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  addReplyLongLong (TYPE_2__*,int) ; 
 int /*<<< orphan*/  sdslen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sentinelProcessHelloMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void sentinelPublishCommand(client *c) {
    if (strcmp(c->argv[1]->ptr,SENTINEL_HELLO_CHANNEL)) {
        addReplyError(c, "Only HELLO messages are accepted by Sentinel instances.");
        return;
    }
    sentinelProcessHelloMessage(c->argv[2]->ptr,sdslen(c->argv[2]->ptr));
    addReplyLongLong(c,1);
}