#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sentinelRedisInstance ;
struct TYPE_4__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ robj ;
typedef  int /*<<< orphan*/  client ;
struct TYPE_5__ {int /*<<< orphan*/  masters; } ;

/* Variables and functions */
 int /*<<< orphan*/  addReplyError (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * dictFetchValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ sentinel ; 

sentinelRedisInstance *sentinelGetMasterByNameOrReplyError(client *c,
                        robj *name)
{
    sentinelRedisInstance *ri;

    ri = dictFetchValue(sentinel.masters,name->ptr);
    if (!ri) {
        addReplyError(c,"No such master with that name");
        return NULL;
    }
    return ri;
}