#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zskiplist ;
struct TYPE_9__ {int /*<<< orphan*/ * zsl; } ;
typedef  TYPE_2__ zset ;
typedef  int /*<<< orphan*/  zlexrangespec ;
struct TYPE_10__ {int zer; int /*<<< orphan*/ * zcurrent; TYPE_1__* value; int /*<<< orphan*/  ztype; int /*<<< orphan*/  zlrs; } ;
struct TYPE_8__ {scalar_t__ type; scalar_t__ encoding; TYPE_2__* ptr; } ;
typedef  int /*<<< orphan*/  RedisModuleString ;
typedef  TYPE_3__ RedisModuleKey ;

/* Variables and functions */
 scalar_t__ C_ERR ; 
 scalar_t__ OBJ_ENCODING_SKIPLIST ; 
 scalar_t__ OBJ_ENCODING_ZIPLIST ; 
 scalar_t__ OBJ_ZSET ; 
 int REDISMODULE_ERR ; 
 int REDISMODULE_OK ; 
 int /*<<< orphan*/  REDISMODULE_ZSET_RANGE_LEX ; 
 int /*<<< orphan*/  RM_ZsetRangeStop (TYPE_3__*) ; 
 int /*<<< orphan*/  serverPanic (char*) ; 
 int /*<<< orphan*/ * zslFirstInLexRange (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zslLastInLexRange (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ zslParseLexRange (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zzlFirstInLexRange (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zzlLastInLexRange (TYPE_2__*,int /*<<< orphan*/ *) ; 

int zsetInitLexRange(RedisModuleKey *key, RedisModuleString *min, RedisModuleString *max, int first) {
    if (!key->value || key->value->type != OBJ_ZSET) return REDISMODULE_ERR;

    RM_ZsetRangeStop(key);
    key->zer = 0;

    /* Setup the range structure used by the sorted set core implementation
     * in order to seek at the specified element. */
    zlexrangespec *zlrs = &key->zlrs;
    if (zslParseLexRange(min, max, zlrs) == C_ERR) return REDISMODULE_ERR;

    /* Set the range type to lex only after successfully parsing the range,
     * otherwise we don't want the zlexrangespec to be freed. */
    key->ztype = REDISMODULE_ZSET_RANGE_LEX;

    if (key->value->encoding == OBJ_ENCODING_ZIPLIST) {
        key->zcurrent = first ? zzlFirstInLexRange(key->value->ptr,zlrs) :
                                zzlLastInLexRange(key->value->ptr,zlrs);
    } else if (key->value->encoding == OBJ_ENCODING_SKIPLIST) {
        zset *zs = key->value->ptr;
        zskiplist *zsl = zs->zsl;
        key->zcurrent = first ? zslFirstInLexRange(zsl,zlrs) :
                                zslLastInLexRange(zsl,zlrs);
    } else {
        serverPanic("Unsupported zset encoding");
    }
    if (key->zcurrent == NULL) key->zer = 1;

    return REDISMODULE_OK;
}