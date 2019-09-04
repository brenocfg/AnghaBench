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
struct TYPE_2__ {int /*<<< orphan*/  repl_scriptcache_fifo; int /*<<< orphan*/  repl_scriptcache_dict; } ;

/* Variables and functions */
 int /*<<< orphan*/  dictEmpty (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listCreate () ; 
 int /*<<< orphan*/  listRelease (int /*<<< orphan*/ ) ; 
 TYPE_1__ server ; 

void replicationScriptCacheFlush(void) {
    dictEmpty(server.repl_scriptcache_dict,NULL);
    listRelease(server.repl_scriptcache_fifo);
    server.repl_scriptcache_fifo = listCreate();
}