#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sds ;
typedef  int /*<<< orphan*/  listNode ;
struct TYPE_2__ {scalar_t__ repl_scriptcache_size; int /*<<< orphan*/  repl_scriptcache_fifo; int /*<<< orphan*/  repl_scriptcache_dict; } ;

/* Variables and functions */
 int DICT_OK ; 
 int dictAdd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int dictDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listAddNodeHead (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listDelNode (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * listLast (int /*<<< orphan*/ ) ; 
 scalar_t__ listLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listNodeValue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdsdup (int /*<<< orphan*/ ) ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  serverAssert (int) ; 

void replicationScriptCacheAdd(sds sha1) {
    int retval;
    sds key = sdsdup(sha1);

    /* Evict oldest. */
    if (listLength(server.repl_scriptcache_fifo) == server.repl_scriptcache_size)
    {
        listNode *ln = listLast(server.repl_scriptcache_fifo);
        sds oldest = listNodeValue(ln);

        retval = dictDelete(server.repl_scriptcache_dict,oldest);
        serverAssert(retval == DICT_OK);
        listDelNode(server.repl_scriptcache_fifo,ln);
    }

    /* Add current. */
    retval = dictAdd(server.repl_scriptcache_dict,key,NULL);
    listAddNodeHead(server.repl_scriptcache_fifo,key);
    serverAssert(retval == DICT_OK);
}