#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sds ;
typedef  int /*<<< orphan*/  robj ;
struct TYPE_5__ {int /*<<< orphan*/  expires; int /*<<< orphan*/  dict; } ;
typedef  TYPE_1__ redisDb ;
typedef  int /*<<< orphan*/  dictEntry ;
struct TYPE_6__ {scalar_t__ masterhost; } ;

/* Variables and functions */
 int /*<<< orphan*/ * createStringObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decrRefCount (int /*<<< orphan*/ *) ; 
 scalar_t__ dictFind (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dictGetFairRandomKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dictGetKey (int /*<<< orphan*/ *) ; 
 scalar_t__ dictSize (int /*<<< orphan*/ ) ; 
 scalar_t__ expireIfNeeded (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdslen (int /*<<< orphan*/ ) ; 
 TYPE_2__ server ; 

robj *dbRandomKey(redisDb *db) {
    dictEntry *de;
    int maxtries = 100;
    int allvolatile = dictSize(db->dict) == dictSize(db->expires);

    while(1) {
        sds key;
        robj *keyobj;

        de = dictGetFairRandomKey(db->dict);
        if (de == NULL) return NULL;

        key = dictGetKey(de);
        keyobj = createStringObject(key,sdslen(key));
        if (dictFind(db->expires,key)) {
            if (allvolatile && server.masterhost && --maxtries == 0) {
                /* If the DB is composed only of keys with an expire set,
                 * it could happen that all the keys are already logically
                 * expired in the slave, so the function cannot stop because
                 * expireIfNeeded() is false, nor it can stop because
                 * dictGetRandomKey() returns NULL (there are keys to return).
                 * To prevent the infinite loop we do some tries, but if there
                 * are the conditions for an infinite loop, eventually we
                 * return a key name that may be already expired. */
                return keyobj;
            }
            if (expireIfNeeded(db,keyobj)) {
                decrRefCount(keyobj);
                continue; /* search for another key. This expired. */
            }
        }
        return keyobj;
    }
}