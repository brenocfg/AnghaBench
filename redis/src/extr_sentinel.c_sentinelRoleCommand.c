#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ sentinelRedisInstance ;
typedef  int /*<<< orphan*/  dictIterator ;
typedef  int /*<<< orphan*/  dictEntry ;
typedef  int /*<<< orphan*/  client ;
struct TYPE_5__ {int /*<<< orphan*/  masters; } ;

/* Variables and functions */
 int /*<<< orphan*/  addReplyArrayLen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  addReplyBulkCBuffer (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  addReplyBulkCString (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dictGetIterator (int /*<<< orphan*/ ) ; 
 TYPE_1__* dictGetVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictReleaseIterator (int /*<<< orphan*/ *) ; 
 int dictSize (int /*<<< orphan*/ ) ; 
 TYPE_2__ sentinel ; 

void sentinelRoleCommand(client *c) {
    dictIterator *di;
    dictEntry *de;

    addReplyArrayLen(c,2);
    addReplyBulkCBuffer(c,"sentinel",8);
    addReplyArrayLen(c,dictSize(sentinel.masters));

    di = dictGetIterator(sentinel.masters);
    while((de = dictNext(di)) != NULL) {
        sentinelRedisInstance *ri = dictGetVal(de);

        addReplyBulkCString(c,ri->name);
    }
    dictReleaseIterator(di);
}