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
typedef  int /*<<< orphan*/  listNode ;
typedef  int /*<<< orphan*/  listIter ;
typedef  int /*<<< orphan*/  client ;
struct TYPE_2__ {scalar_t__ aof_state; int /*<<< orphan*/  aof_buf; int /*<<< orphan*/  slaves; } ;

/* Variables and functions */
 scalar_t__ AOF_OFF ; 
 scalar_t__ aofRewriteBufferSize () ; 
 scalar_t__ getClientOutputBufferMemoryUsage (int /*<<< orphan*/ *) ; 
 int listLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * listNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * listNodeValue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ sdsalloc (int /*<<< orphan*/ ) ; 
 TYPE_1__ server ; 

size_t freeMemoryGetNotCountedMemory(void) {
    size_t overhead = 0;
    int slaves = listLength(server.slaves);

    if (slaves) {
        listIter li;
        listNode *ln;

        listRewind(server.slaves,&li);
        while((ln = listNext(&li))) {
            client *slave = listNodeValue(ln);
            overhead += getClientOutputBufferMemoryUsage(slave);
        }
    }
    if (server.aof_state != AOF_OFF) {
        overhead += sdsalloc(server.aof_buf)+aofRewriteBufferSize();
    }
    return overhead;
}