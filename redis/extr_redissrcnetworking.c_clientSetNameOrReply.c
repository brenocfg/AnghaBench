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
struct TYPE_10__ {char* ptr; } ;
typedef  TYPE_1__ robj ;
struct TYPE_11__ {TYPE_1__* name; } ;
typedef  TYPE_2__ client ;
struct TYPE_12__ {int /*<<< orphan*/  ok; } ;

/* Variables and functions */
 int C_ERR ; 
 int C_OK ; 
 int /*<<< orphan*/  addReply (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyError (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  decrRefCount (TYPE_1__*) ; 
 int /*<<< orphan*/  incrRefCount (TYPE_1__*) ; 
 int sdslen (char*) ; 
 TYPE_3__ shared ; 

int clientSetNameOrReply(client *c, robj *name) {
    int len = sdslen(name->ptr);
    char *p = name->ptr;

    /* Setting the client name to an empty string actually removes
     * the current name. */
    if (len == 0) {
        if (c->name) decrRefCount(c->name);
        c->name = NULL;
        addReply(c,shared.ok);
        return C_OK;
    }

    /* Otherwise check if the charset is ok. We need to do this otherwise
     * CLIENT LIST format will break. You should always be able to
     * split by space to get the different fields. */
    for (int j = 0; j < len; j++) {
        if (p[j] < '!' || p[j] > '~') { /* ASCII is assumed. */
            addReplyError(c,
                "Client names cannot contain spaces, "
                "newlines or special characters.");
            return C_ERR;
        }
    }
    if (c->name) decrRefCount(c->name);
    c->name = name;
    incrRefCount(name);
    return C_OK;
}