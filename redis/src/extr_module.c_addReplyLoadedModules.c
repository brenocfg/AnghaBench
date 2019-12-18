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
struct RedisModule {int /*<<< orphan*/  ver; } ;
typedef  int /*<<< orphan*/  sds ;
typedef  int /*<<< orphan*/  dictIterator ;
typedef  int /*<<< orphan*/  dictEntry ;
typedef  int /*<<< orphan*/  client ;

/* Variables and functions */
 int /*<<< orphan*/  addReplyArrayLen (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyBulkCBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyBulkCString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  addReplyLongLong (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyMapLen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * dictGetIterator (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dictGetKey (int /*<<< orphan*/ *) ; 
 struct RedisModule* dictGetVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictReleaseIterator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  modules ; 
 int /*<<< orphan*/  sdslen (int /*<<< orphan*/ ) ; 

void addReplyLoadedModules(client *c) {
    dictIterator *di = dictGetIterator(modules);
    dictEntry *de;

    addReplyArrayLen(c,dictSize(modules));
    while ((de = dictNext(di)) != NULL) {
        sds name = dictGetKey(de);
        struct RedisModule *module = dictGetVal(de);
        addReplyMapLen(c,2);
        addReplyBulkCString(c,"name");
        addReplyBulkCBuffer(c,name,sdslen(name));
        addReplyBulkCString(c,"ver");
        addReplyLongLong(c,module->ver);
    }
    dictReleaseIterator(di);
}