#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int flags; } ;
typedef  TYPE_2__ redisContext ;
typedef  int /*<<< orphan*/  redisCallback ;
struct TYPE_10__ {int /*<<< orphan*/  patterns; int /*<<< orphan*/  channels; int /*<<< orphan*/  invalid; } ;
struct TYPE_12__ {scalar_t__ err; int /*<<< orphan*/  (* onDisconnect ) (TYPE_3__*,scalar_t__) ;TYPE_1__ sub; int /*<<< orphan*/  replies; TYPE_2__ c; } ;
typedef  TYPE_3__ redisAsyncContext ;
typedef  int /*<<< orphan*/  dictIterator ;
typedef  int /*<<< orphan*/  dictEntry ;

/* Variables and functions */
 int REDIS_CONNECTED ; 
 scalar_t__ REDIS_ERR ; 
 int REDIS_FREEING ; 
 scalar_t__ REDIS_OK ; 
 int /*<<< orphan*/  _EL_CLEANUP (TYPE_3__*) ; 
 int /*<<< orphan*/  __redisRunCallback (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ __redisShiftCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictGetEntryVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictGetIterator (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dictNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dictReleaseIterator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  redisFree (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,scalar_t__) ; 

__attribute__((used)) static void __redisAsyncFree(redisAsyncContext *ac) {
    redisContext *c = &(ac->c);
    redisCallback cb;
    dictIterator *it;
    dictEntry *de;

    /* Execute pending callbacks with NULL reply. */
    while (__redisShiftCallback(&ac->replies,&cb) == REDIS_OK)
        __redisRunCallback(ac,&cb,NULL);

    /* Execute callbacks for invalid commands */
    while (__redisShiftCallback(&ac->sub.invalid,&cb) == REDIS_OK)
        __redisRunCallback(ac,&cb,NULL);

    /* Run subscription callbacks callbacks with NULL reply */
    it = dictGetIterator(ac->sub.channels);
    while ((de = dictNext(it)) != NULL)
        __redisRunCallback(ac,dictGetEntryVal(de),NULL);
    dictReleaseIterator(it);
    dictRelease(ac->sub.channels);

    it = dictGetIterator(ac->sub.patterns);
    while ((de = dictNext(it)) != NULL)
        __redisRunCallback(ac,dictGetEntryVal(de),NULL);
    dictReleaseIterator(it);
    dictRelease(ac->sub.patterns);

    /* Signal event lib to clean up */
    _EL_CLEANUP(ac);

    /* Execute disconnect callback. When redisAsyncFree() initiated destroying
     * this context, the status will always be REDIS_OK. */
    if (ac->onDisconnect && (c->flags & REDIS_CONNECTED)) {
        if (c->flags & REDIS_FREEING) {
            ac->onDisconnect(ac,REDIS_OK);
        } else {
            ac->onDisconnect(ac,(ac->err == 0) ? REDIS_OK : REDIS_ERR);
        }
    }

    /* Cleanup self */
    redisFree(c);
}