#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ robj ;
struct TYPE_9__ {int argc; int /*<<< orphan*/ * cmd; TYPE_1__** argv; } ;
typedef  TYPE_2__ client ;

/* Variables and functions */
 int /*<<< orphan*/  freeClientArgv (TYPE_2__*) ; 
 int /*<<< orphan*/ * lookupCommandOrOriginal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serverAssertWithInfo (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (TYPE_1__**) ; 

void replaceClientCommandVector(client *c, int argc, robj **argv) {
    freeClientArgv(c);
    zfree(c->argv);
    c->argv = argv;
    c->argc = argc;
    c->cmd = lookupCommandOrOriginal(c->argv[0]->ptr);
    serverAssertWithInfo(c,NULL,c->cmd != NULL);
}