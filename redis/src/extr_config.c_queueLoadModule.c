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
struct moduleLoadQueueEntry {int argc; int /*<<< orphan*/ * argv; int /*<<< orphan*/  path; } ;
typedef  int /*<<< orphan*/  sds ;
typedef  int /*<<< orphan*/  robj ;
struct TYPE_2__ {int /*<<< orphan*/  loadmodule_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  createRawStringObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listAddNodeTail (int /*<<< orphan*/ ,struct moduleLoadQueueEntry*) ; 
 int /*<<< orphan*/  sdslen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsnew (int /*<<< orphan*/ ) ; 
 TYPE_1__ server ; 
 void* zmalloc (int) ; 

void queueLoadModule(sds path, sds *argv, int argc) {
    int i;
    struct moduleLoadQueueEntry *loadmod;

    loadmod = zmalloc(sizeof(struct moduleLoadQueueEntry));
    loadmod->argv = zmalloc(sizeof(robj*)*argc);
    loadmod->path = sdsnew(path);
    loadmod->argc = argc;
    for (i = 0; i < argc; i++) {
        loadmod->argv[i] = createRawStringObject(argv[i],sdslen(argv[i]));
    }
    listAddNodeTail(server.loadmodule_queue,loadmod);
}