#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * argv; } ;
typedef  TYPE_1__ client ;

/* Variables and functions */
 scalar_t__ C_OK ; 
 scalar_t__ getLongLongFromObjectOrReply (TYPE_1__*,int /*<<< orphan*/ ,long long*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  incrDecrCommand (TYPE_1__*,long long) ; 

void decrbyCommand(client *c) {
    long long incr;

    if (getLongLongFromObjectOrReply(c, c->argv[2], &incr, NULL) != C_OK) return;
    incrDecrCommand(c,-incr);
}