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
typedef  int /*<<< orphan*/  robj ;
typedef  int /*<<< orphan*/  client ;

/* Variables and functions */
 long long CLUSTER_SLOTS ; 
 scalar_t__ C_OK ; 
 int /*<<< orphan*/  addReplyError (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ getLongLongFromObject (int /*<<< orphan*/ *,long long*) ; 

int getSlotOrReply(client *c, robj *o) {
    long long slot;

    if (getLongLongFromObject(o,&slot) != C_OK ||
        slot < 0 || slot >= CLUSTER_SLOTS)
    {
        addReplyError(c,"Invalid or out of range slot");
        return -1;
    }
    return (int) slot;
}