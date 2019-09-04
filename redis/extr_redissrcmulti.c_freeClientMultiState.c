#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int argc; struct TYPE_8__* argv; } ;
typedef  TYPE_2__ multiCmd ;
struct TYPE_7__ {int count; TYPE_2__* commands; } ;
struct TYPE_9__ {TYPE_1__ mstate; } ;
typedef  TYPE_3__ client ;

/* Variables and functions */
 int /*<<< orphan*/  decrRefCount (TYPE_2__) ; 
 int /*<<< orphan*/  zfree (TYPE_2__*) ; 

void freeClientMultiState(client *c) {
    int j;

    for (j = 0; j < c->mstate.count; j++) {
        int i;
        multiCmd *mc = c->mstate.commands+j;

        for (i = 0; i < mc->argc; i++)
            decrRefCount(mc->argv[i]);
        zfree(mc->argv);
    }
    zfree(c->mstate.commands);
}