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
struct TYPE_6__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ robj ;
struct TYPE_7__ {int /*<<< orphan*/  dict; int /*<<< orphan*/  expires; } ;
typedef  TYPE_2__ redisDb ;
typedef  int /*<<< orphan*/  dictEntry ;

/* Variables and functions */
 int /*<<< orphan*/ * dictFind (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long long dictGetSignedIntegerVal (int /*<<< orphan*/ *) ; 
 scalar_t__ dictSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serverAssertWithInfo (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 

long long getExpire(redisDb *db, robj *key) {
    dictEntry *de;

    /* No expire? return ASAP */
    if (dictSize(db->expires) == 0 ||
       (de = dictFind(db->expires,key->ptr)) == NULL) return -1;

    /* The entry was found in the expire dict, this means it should also
     * be present in the main dict (safety check). */
    serverAssertWithInfo(NULL,key,dictFind(db->dict,key->ptr) != NULL);
    return dictGetSignedIntegerVal(de);
}