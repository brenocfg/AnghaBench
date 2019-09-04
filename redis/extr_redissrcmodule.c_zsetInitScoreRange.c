#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zskiplist ;
struct TYPE_14__ {int /*<<< orphan*/ * zsl; } ;
typedef  TYPE_2__ zset ;
struct TYPE_15__ {double min; double max; int minex; int maxex; } ;
typedef  TYPE_3__ zrangespec ;
struct TYPE_16__ {int zer; int /*<<< orphan*/ * zcurrent; TYPE_1__* value; TYPE_3__ zrs; int /*<<< orphan*/  ztype; } ;
struct TYPE_13__ {scalar_t__ type; scalar_t__ encoding; TYPE_2__* ptr; } ;
typedef  TYPE_4__ RedisModuleKey ;

/* Variables and functions */
 scalar_t__ OBJ_ENCODING_SKIPLIST ; 
 scalar_t__ OBJ_ENCODING_ZIPLIST ; 
 scalar_t__ OBJ_ZSET ; 
 int REDISMODULE_ERR ; 
 int REDISMODULE_OK ; 
 int /*<<< orphan*/  REDISMODULE_ZSET_RANGE_SCORE ; 
 int /*<<< orphan*/  RM_ZsetRangeStop (TYPE_4__*) ; 
 int /*<<< orphan*/  serverPanic (char*) ; 
 int /*<<< orphan*/ * zslFirstInRange (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/ * zslLastInRange (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/ * zzlFirstInRange (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/ * zzlLastInRange (TYPE_2__*,TYPE_3__*) ; 

int zsetInitScoreRange(RedisModuleKey *key, double min, double max, int minex, int maxex, int first) {
    if (!key->value || key->value->type != OBJ_ZSET) return REDISMODULE_ERR;

    RM_ZsetRangeStop(key);
    key->ztype = REDISMODULE_ZSET_RANGE_SCORE;
    key->zer = 0;

    /* Setup the range structure used by the sorted set core implementation
     * in order to seek at the specified element. */
    zrangespec *zrs = &key->zrs;
    zrs->min = min;
    zrs->max = max;
    zrs->minex = minex;
    zrs->maxex = maxex;

    if (key->value->encoding == OBJ_ENCODING_ZIPLIST) {
        key->zcurrent = first ? zzlFirstInRange(key->value->ptr,zrs) :
                                zzlLastInRange(key->value->ptr,zrs);
    } else if (key->value->encoding == OBJ_ENCODING_SKIPLIST) {
        zset *zs = key->value->ptr;
        zskiplist *zsl = zs->zsl;
        key->zcurrent = first ? zslFirstInRange(zsl,zrs) :
                                zslLastInRange(zsl,zrs);
    } else {
        serverPanic("Unsupported zset encoding");
    }
    if (key->zcurrent == NULL) key->zer = 1;
    return REDISMODULE_OK;
}