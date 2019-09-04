#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int argc; TYPE_1__** argv; } ;
typedef  TYPE_2__ client ;
struct TYPE_8__ {int /*<<< orphan*/  syntaxerr; } ;
struct TYPE_6__ {int /*<<< orphan*/  ptr; } ;

/* Variables and functions */
 int C_ERR ; 
 int C_OK ; 
 int EMPTYDB_ASYNC ; 
 int EMPTYDB_NO_FLAGS ; 
 int /*<<< orphan*/  addReply (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_3__ shared ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char*) ; 

int getFlushCommandFlags(client *c, int *flags) {
    /* Parse the optional ASYNC option. */
    if (c->argc > 1) {
        if (c->argc > 2 || strcasecmp(c->argv[1]->ptr,"async")) {
            addReply(c,shared.syntaxerr);
            return C_ERR;
        }
        *flags = EMPTYDB_ASYNC;
    } else {
        *flags = EMPTYDB_NO_FLAGS;
    }
    return C_OK;
}